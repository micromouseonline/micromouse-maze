/**
 *  \file maze.h
 *  \brief The Maze class stores wall and flooding data
 * *
 *  \version
 *  \date 15 Apr 2017
 *  \author peterharrison
 *  \bug No known bugs.
 */


#include "floodinfo.h"
#include "maze.h"
#include "mazeconstants.h"
#include "priorityqueue.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

/*
 * The runlength flood calculates costs based on the length of straights
 */
const uint16_t orthoCostTable[] =
    // low speed costs ( vturn = 1.5m/s/s, acc = 13000 mm/s/s)
    {0, 98, 75, 63, 55, 50, 46, 43, 40, 38, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
        36, 36,};

const uint16_t diagCostTable[] =
    // low speed costs ( vturn = 1.5m/s/s, acc = 13000 mm/s/s)
    {0, 73, 58, 50, 44, 40, 37, 35, 33, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
        31, 31};

// high speed costs (vturn = 2000 mm/s, acc = 16667 mm/s/s)
//{0,56,47,41,37,34,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31};

uint16_t turnCostTable[] = {
    75,  // 45 degree
    149,  // 90 degree
    225,  // 135 degree
    318,  // 180 degree
};

Maze::Maze(uint16_t width) :
    mWidth(width),
    mIsSolved(false),
    mFloodType(RUNLENGTH_FLOOD),
    mCornerWeight(3) {
  resetToEmptyMaze();
  setGoal(DEFAULT_GOAL);
};

uint16_t Maze::width() const {
  return mWidth;
}

uint16_t Maze::numCells() {
  return mWidth * mWidth;
}

void Maze::clearData() {
  for (uint16_t i = 0; i < numCells(); i++) {
    mCost[i] = MAX_COST;
    mDirection[i] = NORTH;
    mWalls[i] = 0;
  }
}

void Maze::resetToEmptyMaze() {
  clearData();
  for (int i = 0; i < width(); i++) {
    setWall(i, WEST);
    setWall(width() * (width() - 1) + i, EAST);
    setWall(i * width(), SOUTH);
    setWall(width() * i + width() - 1, NORTH);
  }
  setWall(0, EAST);
  clearWall(0, NORTH);
}

/*
 * This will take a full set of wall data for a cell
 * in the format used in .maz files and update that cell
 * as well as its neighbors with data for all four walls
 * whether or not they are present
 * Effectively, it will also mark the current cell as
 * completely visited
 * Note that this will clear any walls that are already set.
 * DO NOT USE THIS WHEN EXPLORING.
 * INSTEAD, USE updateMap()
 */
void Maze::copyCellFromFileData(uint16_t cell, uint8_t wallData) {
  if (wallData & 0x01) {
    setWall(cell, NORTH);
  } else {
    clearWall(cell, NORTH);
  }
  if (wallData & 0x02) {
    setWall(cell, EAST);
  } else {
    clearWall(cell, EAST);
  }
  if (wallData & 0x04) {
    setWall(cell, SOUTH);
  } else {
    clearWall(cell, SOUTH);
  }
  if (wallData & 0x08) {
    setWall(cell, WEST);
  } else {
    clearWall(cell, WEST);
  }
}

/**
 * by laboriously seeting each wall in each cell, the maze will always
 * be left in a legal state where there can be no walls that are present
 * in a cell and absent when lookd at from the other side in the next cell.
 */
void Maze::copyMazeFromFileData(const uint8_t *wallData, uint16_t cellCount) {
  clearData();
  if (cellCount > numCells()) {
    return; // ERROR here
  }
  if (wallData) {
    for (uint16_t cell = 0; cell < cellCount; cell++) {
      copyCellFromFileData(cell, wallData[cell]);
    }
  }
}

uint16_t Maze::col(uint16_t cell) {
  return cell / mWidth;
}

uint16_t Maze::row(uint16_t cell) {
  return cell % mWidth;
}

uint8_t Maze::ahead(uint8_t direction) {
  return direction;
}

uint8_t Maze::rightOf(uint8_t direction) {
  return (uint8_t) ((direction + 1) % 4);
}

uint8_t Maze::leftOf(uint8_t direction) {
  return (uint8_t) ((direction + 3) % 4);
}

uint8_t Maze::behind(uint8_t direction) {
  return (uint8_t) ((direction + 2) % 4);
}

uint8_t Maze::opposite(uint8_t direction) {
  return behind(direction);
}

uint8_t Maze::differenceBetween(uint8_t oldDirection, uint8_t newDirection) {
  return (newDirection - oldDirection) % 4;
}



uint16_t Maze::cellNorth(uint16_t cell) {
  uint16_t nextCell = (cell + uint16_t(1)) % numCells();
  return nextCell;
}

uint16_t Maze::cellEast(uint16_t cell) {
  uint16_t nextCell = (cell + width()) % numCells();
  return nextCell;
}

uint16_t Maze::cellSouth(uint16_t cell) {
  uint16_t nextCell = (cell + numCells() - uint16_t(1)) % numCells();
  return nextCell;
}

uint16_t Maze::cellWest(uint16_t cell) {
  uint16_t nextCell = (cell + numCells() - width()) % numCells();
  return nextCell;
}

uint16_t Maze::neighbour(uint16_t cell, uint16_t direction) {
  uint16_t neighbour;
  switch (direction) {
    case NORTH:neighbour = cellNorth(cell);
      break;
    case EAST:neighbour = cellEast(cell);
      break;
    case SOUTH:neighbour = cellSouth(cell);
      break;
    case WEST:neighbour = cellWest(cell);
      break;
    default:neighbour = MAX_COST;
  }
  return neighbour;
}

uint16_t Maze::home() {
  return 0;
}

uint16_t Maze::goal() {
  return mGoal;
}

void Maze::setGoal(uint16_t goal) {
  mGoal = goal;
}

uint8_t Maze::walls(uint16_t cell) {
  uint8_t wallData = mWalls[cell];
  uint8_t result = 0;
  result |= (wallData >> 0) & 1;
  result |= (wallData >> 1) & 2;
  result |= (wallData >> 2) & 4;
  result |= (wallData >> 3) & 8;;
  return result;
}

bool Maze::isSeen(uint16_t cell, uint8_t direction) {
  return (walls(cell) & (0x10 << direction)) != 0;
}

bool Maze::hasExit(uint16_t cell, uint8_t direction) {
  return (walls(cell) & (0x01 << direction)) == 0;
}

bool Maze::hasRealExit(uint16_t cell, uint8_t direction) {
  return isSeen(cell, direction) && hasExit(cell, direction);
}

bool Maze::hasWall(uint16_t cell, uint8_t direction) {
  return (walls(cell) & (0x01 << direction)) != 0;
}

bool Maze::hasRealWall(uint16_t cell, uint8_t direction) {
  return isSeen(cell, direction) && hasWall(cell, direction);
}

uint8_t Maze::direction(uint16_t cell) {
  return mDirection[cell];
}

void Maze::setDirection(uint16_t cell, uint8_t direction) {
  assert(direction == NORTH || direction == EAST || direction == SOUTH || direction == WEST);
  mDirection[cell] = direction;
}

bool Maze::isVisited(uint16_t cell) {
  return ((mWalls[cell] & VISITED) == VISITED);
}

void Maze::setVisited(uint16_t cell) {
  mWalls[cell] |= VISITED;
}

void Maze::clearVisited(uint16_t cell) {
  mWalls[cell] &= ~VISITED;
}

/*
 * unconditionally adds a wall in the map.
 * over-writes whatever is there.
 * should only be used when setting up a maze.
 * To update the maze when running, use updateWalls(cell,wallData)
 */
void Maze::setWall(uint16_t cell, uint8_t direction) {
  switch (direction) {
    case NORTH:mWalls[cell] |= CHECKED_NORTH + WALL_NORTH;
      cell = cellNorth(cell);
      mWalls[cell] |= CHECKED_SOUTH + WALL_SOUTH;
      break;
    case EAST:mWalls[cell] |= CHECKED_EAST + WALL_EAST;
      cell = cellEast(cell);
      mWalls[cell] |= CHECKED_WEST + WALL_WEST;
      break;
    case SOUTH:mWalls[cell] |= CHECKED_SOUTH + WALL_SOUTH;
      cell = cellSouth(cell);
      mWalls[cell] |= CHECKED_NORTH + WALL_NORTH;
      break;
    case WEST:mWalls[cell] |= CHECKED_WEST + WALL_WEST;
      cell = cellWest(cell);
      mWalls[cell] |= CHECKED_EAST + WALL_EAST;
      break;
  }
}

/*
 * unconditionally clears a wall in the map.
 * over-writes whatever is there.
 * should only be used when setting up a maze.
 * To update the maze when running, use updateWalls(cell,wallData)
 */
void Maze::clearWall(uint16_t cell, uint8_t direction) {
  switch (direction) {
    case NORTH:mWalls[cell] &= ~WALL_NORTH;
      mWalls[cell] |= CHECKED_NORTH;
      cell = cellNorth(cell);
      mWalls[cell] &= ~WALL_SOUTH;
      mWalls[cell] |= CHECKED_SOUTH;
      break;
    case EAST:mWalls[cell] &= ~WALL_EAST;
      mWalls[cell] |= CHECKED_EAST;
      cell = cellEast(cell);
      mWalls[cell] &= ~WALL_WEST;
      mWalls[cell] |= CHECKED_WEST;
      break;
    case SOUTH:mWalls[cell] &= ~WALL_SOUTH;
      mWalls[cell] |= CHECKED_SOUTH;
      cell = cellSouth(cell);
      mWalls[cell] &= ~WALL_NORTH;
      mWalls[cell] |= CHECKED_NORTH;
      break;
    case WEST:mWalls[cell] &= ~WALL_WEST;
      mWalls[cell] |= CHECKED_WEST;
      cell = cellWest(cell);
      mWalls[cell] &= ~WALL_EAST;
      mWalls[cell] |= CHECKED_EAST;
      break;
  }
}

/*
 * Updates the map by adding walls
 * Used when exploring only.
 * Will not remove a wall
 */
void Maze::updateMap(uint16_t cell, uint8_t wallData) {
  if (wallData & 0x01) {
    setWall(cell, NORTH);
  }
  if (wallData & 0x02) {
    setWall(cell, EAST);
  }
  if (wallData & 0x04) {
    setWall(cell, SOUTH);
  }
  if (wallData & 0x08) {
    setWall(cell, WEST);
  }
}

void Maze::setUnknowns(void) {
  for (uint16_t i = 0; i < numCells(); i++) {
    mWalls[i] |= (((~mWalls[i]) & VISITED) >> 1);
  }
}

void Maze::clearUnknowns(void) {
  for (uint16_t i = 0; i < numCells(); i++) {
    mWalls[i] &= ~(((~mWalls[i]) & VISITED) >> 1);
  }
}

uint16_t Maze::cost(uint16_t cell) {
  return mCost[cell];
}

/*
 * Distance is returned based upon the setting of the wall flag.
 * No account is taken of the 'wall seen' flag.
 */
uint16_t Maze::costNorth(uint16_t cell) {
  if (hasWall(cell, NORTH)) {
    return MAX_COST;
  }
  cell = cellNorth(cell);
  return mCost[cell];
}

uint16_t Maze::costEast(uint16_t cell) {
  if (hasWall(cell, EAST)) {
    return MAX_COST;
  }
  cell = cellEast(cell);
  return mCost[cell];
}

uint16_t Maze::costSouth(uint16_t cell) {
  if (hasWall(cell, SOUTH)) {
    return MAX_COST;
  }
  cell = cellSouth(cell);
  return mCost[cell];
}

uint16_t Maze::costWest(uint16_t cell) {
  if (hasWall(cell, WEST)) {
    return MAX_COST;
  }
  cell = cellWest(cell);
  return mCost[cell];
}

uint16_t Maze::cost(uint16_t cell, uint16_t direction) {
  uint16_t result;
  switch (direction) {
    case NORTH:result = costNorth(cell);
      break;
    case EAST:result = costEast(cell);
      break;
    case SOUTH:result = costSouth(cell);
      break;
    case WEST:result = costWest(cell);
      break;
    default:result = MAX_COST;
  }
  return result;
}

void Maze::setCost(uint16_t cell, uint16_t cost) {
  mCost[cell] = cost;
}

uint8_t Maze::directionToSmallest(uint16_t cell) {
  uint8_t smallestDirection;
  uint16_t neighbourCost;
  uint16_t smallestCost = MAX_COST;
  neighbourCost = cost(cell, NORTH);
  if (neighbourCost < smallestCost) {
    smallestCost = neighbourCost;
    smallestDirection = NORTH;
  };
  neighbourCost = cost(cell, EAST);
  if (neighbourCost < smallestCost) {
    smallestCost = neighbourCost;
    smallestDirection = EAST;
  };
  neighbourCost = cost(cell, SOUTH);
  if (neighbourCost < smallestCost) {
    smallestCost = neighbourCost;
    smallestDirection = SOUTH;
  };
  neighbourCost = cost(cell, WEST);
  if (neighbourCost < smallestCost) {
    smallestCost = neighbourCost;
    smallestDirection = WEST;
  };
  if (smallestCost == MAX_COST) {
    smallestDirection = INVALID_DIRECTION;
  }
  return smallestDirection;
}

void Maze::updateDirections() {
  for (uint16_t i = 0; i < numCells(); i++) {
    mDirection[i] = directionToSmallest(i);
  }
}

bool Maze::testForSolution(void) { // takes less than 3ms
  setUnknowns();
  mPathCostClosed = flood(goal());
  clearUnknowns();
  mPathCostOpen = flood(goal());
  mIsSolved = mPathCostClosed == mPathCostOpen;
  return mIsSolved;
};

/*
 *  The default goal while searching a classic maze
 *  the cell 0x77. This may not be the best finish
 *  cell on a speed run. Generally, it is best to
 *  finish on the other side of the goal area to the
 *  entrance.
 *  This method tries to work out where that will be.
 *  It takes no account of the possibil ty of multiple
 *  entrances but it is better than nothing
 */
void Maze::recalculateGoal() {
  uint16_t newGoal = goal();
  // count the entrances
  int entranceCount = 0;

  if (hasExit(0x77, SOUTH)) {
    entranceCount++;
    newGoal = 0x78;
  };
  if (hasExit(0x77, WEST)) {
    entranceCount++;
    newGoal = 0x87;
  };
  if (hasExit(0x78, WEST)) {
    entranceCount++;
    newGoal = 0x88;
  };
  if (hasExit(0x78, NORTH)) {
    entranceCount++;
    newGoal = 0x77;
  };
  if (hasExit(0x88, NORTH)) {
    entranceCount++;
    newGoal = 0x87;
  };
  if (hasExit(0x88, EAST)) {
    entranceCount++;
    newGoal = 0x78;
  };
  if (hasExit(0x87, EAST)) {
    entranceCount++;
    newGoal = 0x77;
  };
  if (hasExit(0x87, SOUTH)) {
    entranceCount++;
    newGoal = 0x88;
  };
  switch (entranceCount) {
    case 0:break;
    case 1:
    case 2:
    case 3:setGoal(newGoal);
      setGoal(newGoal);
      break;
    default:break;
  }
  setGoal(newGoal);
}

int16_t Maze::costDifference(void) {
  return int16_t(mPathCostOpen) - int16_t(mPathCostClosed);
}

uint16_t Maze::openMazeCost() const {
  return mPathCostOpen;
}

uint16_t Maze::closedMazeCost() const {
  return mPathCostClosed;
}

uint16_t Maze::flood(uint16_t target) {
  uint16_t cost;
  switch (mFloodType) {
    case MANHATTAN_FLOOD:cost = manhattanFlood(target);
      break;
    case WEIGHTED_FLOOD:cost = weightedFlood(target);
      break;
    case RUNLENGTH_FLOOD:cost = runLengthFlood(target);
      break;
    case DIRECTION_FLOOD:break;
  }
  return cost;
}

static uint8_t getExitDirection[4][4] = {
    {255, 3, 4, 5,},
    {7, 255, 5, 6,},
    {0, 1, 255, 7,},
    {1, 2, 3, 255},
};

/*
 *  TODO: Initialising the queue needs to be more clever.
 * For each exit from the goal cell, seed the queue with the corresponding neighbour
 * Note that single-cell goals may have multiple exits and the centre region in the
 * classic contest will also have a number of possible exits
 * */
uint16_t Maze::runLengthFlood(uint16_t target) {
  PriorityQueue<FloodInfo> queue;
  initialiseFloodCosts(target);
  seedQueue(queue, target, orthoCostTable[1]);
  // each (accessible) cell will be processed only once
  while ((queue.size() > 0)) {
    FloodInfo info = queue.fetchSmallest();
    /*
     * test each wall for an exit. Skip any blocked, or already used exits
     */
    for (uint8_t exitWall = 0; exitWall < 4; exitWall++) {
      if (exitWall == info.entryWall) {
        continue;
      }
      if (hasWall(info.cell, exitWall)) {
        continue;
      }
      uint16_t nextCell = neighbour(info.cell, exitWall);
      if (mCost[nextCell] < MAX_COST) {
        continue;
      }
      uint8_t exitDir = getExitDirection[info.entryWall][exitWall];
      uint8_t newRunLength = info.runLength;
      uint16_t turnSize = abs(int(info.entryDir) - int(exitDir));
      if (turnSize > 4) {
        turnSize = 7 - turnSize;
      }
      uint16_t turnCost = 0;;
      if (info.entryDir == exitDir) {
        newRunLength++;
      } else {
        newRunLength = 1;
        turnCost = turnSize * 22; // MAGIC: empirical value for best-looking routes
      }
      uint16_t newCost = ((exitDir & 1) == 0) ? orthoCostTable[newRunLength] : diagCostTable[newRunLength];
      newCost += turnCost + mCost[info.cell];
      mCost[nextCell] = newCost;
      queue.add(FloodInfo(newCost, nextCell, newRunLength, exitDir, opposite(exitWall)));
    }
  }
  updateDirections();
  return mCost[0];
}

uint16_t Maze::manhattanFlood(uint16_t target) {
  PriorityQueue<uint16_t> queue;
  initialiseFloodCosts(target);
  queue.add(target);
  while (queue.size() > 0) {
    uint16_t cell = queue.head();
    uint16_t newCost = mCost[cell];
    newCost++;
    for (uint8_t direction = 0; direction < 4; direction++) {
      if (hasExit(cell, direction)) {
        uint16_t nextCell = neighbour(cell, direction);
        if (mCost[nextCell] > newCost) {
          mCost[nextCell] = newCost;
          queue.add(nextCell);
        }
      }
    }
  }
  updateDirections();
  return mCost[0];
};

void Maze::seedQueue(PriorityQueue<FloodInfo> &queue, uint16_t goal, uint16_t cost) {
  if (hasExit(goal, NORTH)) {
    uint16_t nextCell = cellNorth(goal);
    queue.add(FloodInfo(cost, nextCell, 1, DIR_N, SOUTH));
    mCost[nextCell] = cost;
  }
  if (hasExit(goal, EAST)) {
    uint16_t nextCell = cellEast(goal);
    queue.add(FloodInfo(cost, nextCell, 1, DIR_E, WEST));
    mCost[nextCell] = cost;
  }
  if (hasExit(goal, SOUTH)) {
    uint16_t nextCell = cellSouth(goal);
    queue.add(FloodInfo(cost, nextCell, 1, DIR_S, NORTH));
    mCost[nextCell] = cost;
  }
  if (hasExit(goal, WEST)) {
    uint16_t nextCell = cellWest(goal);
    queue.add(FloodInfo(cost, nextCell, 1, DIR_W, EAST));
    mCost[nextCell] = cost;
  }
}

bool Maze::isSolved(void) {
  return mIsSolved;
}

void Maze::save(uint8_t *data) {
  for (int i = 0; i < numCells(); i++) {
    data[i] = mWalls[i];
  }
};

void Maze::load(uint8_t *data) {
  for (int i = 0; i < numCells(); i++) {
    mWalls[i] = data[i];
  }
}

void Maze::initialiseFloodCosts(uint16_t target) {
  // set every cell as unexamined
  for (uint16_t i = 0; i < numCells(); i++) {
    mCost[i] = MAX_COST;
    mDirection[i] = INVALID_DIRECTION;
  }
  // except the target
  mCost[target] = 0;
  mDirection[target] = NORTH;
}

uint16_t Maze::weightedFlood(uint16_t target) {
  PriorityQueue<int> queue;
  const uint16_t aheadCost = 2;

  initialiseFloodCosts(target);
  queue.add(target);
  while (queue.size() > 0) {
    uint16_t newCost;
    uint16_t here = queue.head();
    uint16_t costHere = mCost[here];
    uint8_t thisDirection = mDirection[here];
    for (uint8_t exitDirection = 0; exitDirection < 4; exitDirection++) {
      if (hasExit(here, exitDirection)) {
        uint16_t nextCell = neighbour(here, exitDirection);
        if (thisDirection == exitDirection) {
          newCost = costHere + aheadCost;
        } else {
          newCost = costHere + mCornerWeight;
        }
        if (mCost[nextCell] > newCost) {
          mCost[nextCell] = newCost;
          mDirection[nextCell] = exitDirection;
          queue.add(nextCell);
        }
      }
    }
  }
  updateDirections();
  return mCost[0];
}

/** Although the direction flood uses only directions
 * it updates the manhattan distance for the costing
 * so that  atest for a solution can be made
 * @param target
 * @return
 */

uint16_t Maze::directionFlood(uint16_t target) {
  PriorityQueue<int> queue;
  initialiseFloodCosts(target);
  queue.add(target);
  while (queue.size() > 0) {
    uint16_t here = queue.head();
    uint16_t nextCost = mCost[here] + 1;
    for (uint8_t exit = 0; exit < 4; exit++) {
      if (hasExit(here, exit)) {
        uint16_t next = neighbour(here, exit);
        if (mDirection[next] == INVALID_DIRECTION) {
          mDirection[next] = behind(exit);
          mCost[next] = nextCost;
          queue.add(next);
        }
      }
    }
  }
  return mCost[0];
}

Maze::FloodType Maze::getFloodType() const {
  return mFloodType;
}

void Maze::setFloodType(Maze::FloodType mFloodType) {
  Maze::mFloodType = mFloodType;
}

uint16_t Maze::getCornerWeight() const {
  return mCornerWeight;
}

void Maze::setCornerWeight(uint16_t cornerWeight) {
  Maze::mCornerWeight = cornerWeight;
}


// OLD STUFF BELOW HERE
////////////////////////////////////////////////////

#ifdef STM32F4xx
 uint8_t backupWalls[1024] NOINIT;
#else
 uint8_t backupWalls[1024];
#endif


