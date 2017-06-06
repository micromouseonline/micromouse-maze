//
// Created by Peter Harrison on 26/05/2017.
//

#include "mazeconstants.h"
#include "mazedata.h"

#include "maze.h"
#include "priorityqueue.h"


#include <stdio.h>



/*
 * The runlength flood calculates costs based on the length of straights
 */
const uint16_t orthoCostTable[] =
    // low speed costs ( vturn = 1.5m/s/s, acc = 13000 mm/s/s)
    {0, 98, 75, 63, 55, 50, 46, 43, 40, 38, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,};

const uint16_t diagCostTable[] =
    // low speed costs ( vturn = 1.5m/s/s, acc = 13000 mm/s/s)
    {0, 73, 58, 50, 44, 40, 37, 35, 33, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31};

// high speed costs (vturn = 2000 mm/s, acc = 16667 mm/s/s)
//{0,56,47,41,37,34,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31};

uint16_t turnCostTable[] = {
    75,  // 45 degree
    149,  // 90 degree
    225,  // 135 degree
    318,  // 180 degree
};


Maze::Maze(uint16_t width) {
  mWidth = width;
  mIsSolved = false;
  resetToEmptyMaze();
  setGoal(DEFAULT_GOAL);
};


uint16_t Maze::width() {
  return mWidth;
}

uint16_t Maze::numCells() {
  return mWidth * mWidth;
}


void Maze::clearWallData() {
  for (uint16_t i = 0; i < numCells(); i++) {
    mCost[i] = MAX_COST;
    mDirection[i] = NORTH;
    mWalls[i] = 0;
  }
}


void Maze::resetToEmptyMaze() {
  clearWallData();
  for (int i = 0; i < width(); i++) {
    setWall(i, WEST);
    setWall(width() * (width() - 1) + i, EAST);
    setWall(i * width(), SOUTH);
    setWall(width() * i + width() - 1, NORTH);
  }
  setWall(0, EAST);
  clearWall(0, NORTH);
}


void Maze::copyMaze(const uint8_t *wallData, uint16_t cellCount) {
  clearWallData();
  if (cellCount > numCells()) {
    return; // ERROR here
  }
  if (wallData) {
    for (uint16_t cell = 0; cell < cellCount; cell++) {
      copyCellFromFileData(cell, wallData[cell]);
    }
  }
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
    case NORTH:
      neighbour = cellNorth(cell);
      break;
    case EAST:
      neighbour = cellEast(cell);
      break;
    case SOUTH:
      neighbour = cellSouth(cell);
      break;
    case WEST:
      neighbour = cellWest(cell);
      break;
    default:
      neighbour = MAX_COST;
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
  return (uint8_t) ((wallData & 1) + ((wallData >> 1) & 2) + ((wallData >> 2) & 4) + ((wallData >> 3) & 8));;
}


bool Maze::isKnownWall(uint16_t cell, uint8_t direction) {
  return (mWalls[cell] & (WALL_KNOWN << (2 * direction))) != 0;
}

bool Maze::hasExit(uint16_t cell, uint8_t direction) {
  return (walls(cell) & (1 << direction)) == 0;
}

bool Maze::hasWall(uint16_t cell, uint8_t direction) {
  return (walls(cell) & (1 << direction)) != 0;
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


void Maze::resetCell(uint16_t cell) {
  mWalls[cell] = 0;
}


/*
 * unconditionally adds a wall in the map.
 * over-writes whatever is there.
 * should only be used when setting up a maze.
 * To update the maze when running, use updateWalls(cell,wallData)
 */
void Maze::setWall(uint16_t cell, uint8_t direction) {
  switch (direction) {
    case NORTH:
      mWalls[cell] |= CHECKED_NORTH + WALL_NORTH;
      cell = cellNorth(cell);
      mWalls[cell] |= CHECKED_SOUTH + WALL_SOUTH;
      break;
    case EAST:
      mWalls[cell] |= CHECKED_EAST + WALL_EAST;
      cell = cellEast(cell);
      mWalls[cell] |= CHECKED_WEST + WALL_WEST;
      break;
    case SOUTH:
      mWalls[cell] |= CHECKED_SOUTH + WALL_SOUTH;
      cell = cellSouth(cell);
      mWalls[cell] |= CHECKED_NORTH + WALL_NORTH;
      break;
    case WEST:
      mWalls[cell] |= CHECKED_WEST + WALL_WEST;
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
    case NORTH:
      mWalls[cell] &= ~WALL_NORTH;
      mWalls[cell] |= CHECKED_NORTH;
      cell = cellNorth(cell);
      mWalls[cell] &= ~WALL_SOUTH;
      mWalls[cell] |= CHECKED_SOUTH;
      break;
    case EAST:
      mWalls[cell] &= ~WALL_EAST;
      mWalls[cell] |= CHECKED_EAST;
      cell = cellEast(cell);
      mWalls[cell] &= ~WALL_WEST;
      mWalls[cell] |= CHECKED_WEST;
      break;
    case SOUTH:
      mWalls[cell] &= ~WALL_SOUTH;
      mWalls[cell] |= CHECKED_SOUTH;
      cell = cellSouth(cell);
      mWalls[cell] &= ~WALL_NORTH;
      mWalls[cell] |= CHECKED_NORTH;
      break;
    case WEST:
      mWalls[cell] &= ~WALL_WEST;
      mWalls[cell] |= CHECKED_WEST;
      cell = cellWest(cell);
      mWalls[cell] &= ~WALL_EAST;
      mWalls[cell] |= CHECKED_EAST;
      break;
  }
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
    case NORTH:
      result = costNorth(cell);
      break;
    case EAST:
      result = costEast(cell);
      break;
    case SOUTH:
      result = costSouth(cell);
      break;
    case WEST:
      result = costWest(cell);
      break;
    default:
      result = MAX_COST;
  }
  return result;
}


void Maze::setCost(uint16_t cell, uint16_t cost) {
  mCost[cell] = cost;
}


uint8_t Maze::directionToSmallest(uint16_t cell, uint8_t direction) {
  uint8_t newDirection;
  uint16_t neighbourCost;
  uint16_t smallestCost;
  newDirection = direction;
  // assume it is ahead
  smallestCost = cost(cell, direction);
  neighbourCost = cost(cell, rightOf(direction));
  if (neighbourCost < smallestCost) {
    smallestCost = neighbourCost;
    newDirection = rightOf(direction);
  }
  neighbourCost = cost(cell, leftOf(direction));
  if (neighbourCost < smallestCost) {
    smallestCost = neighbourCost;
    newDirection = leftOf(direction);
  }
  neighbourCost = cost(cell, behind(direction));
  if (neighbourCost < smallestCost) {
    newDirection = behind(direction);
  }
  return newDirection;
}


void Maze::updateDirections()
{
  for (uint16_t i = 0; i < numCells(); i++) {
    mDirection[i] = directionToSmallest(i, NORTH);
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
    case 0:
      break;
    case 1:
    case 2:
    case 3:
      setGoal(newGoal);
      setGoal(newGoal);
      break;
    default:
      break;
  }
  setGoal(newGoal);
}


int16_t Maze::costDifference(void) {
  return mCostDifference;
}


uint16_t Maze::openMazeCost() const {
  return mPathCostOpen;
}

uint16_t Maze::closedMazeCost() const {
  return mPathCostClosed;
}

uint16_t Maze::flood(uint16_t goal) {
  return runLengthFlood(goal);
}


static uint8_t getExitDirection[] = {255, 3, 4, 5, 7, 255, 5, 6, 0, 1, 255, 7, 1, 2, 3, 255};
/*
 *  TODO: Initialising the queue needs to be more clever.
 * For each exit from the goal cell, seed the queue with the corresponding neighbour
 * Note that single-cell goals may have multiple exits and the centre region in the
 * classic contest will also have a number of possible exits
 * */
uint16_t Maze::runLengthFlood(uint16_t goal) {
  PriorityQueue<FloodInfo> queue ;
  // set every cell as unexamined
  for (uint16_t i = 0; i < numCells(); i++) {
    mCost[i] = MAX_COST;
  }
  // except the goal
  mCost[goal] = 0;
  // Add all the neighbours of teh goal to the queue
  uint16_t cost = orthoCostTable[1];
  if (hasExit(goal, NORTH)) {
    uint16_t nextCell = cellNorth(goal);
    queue.add(FloodInfo(cost, nextCell, 1, DIR_N, SOUTH));
    mCost[nextCell] = cost;
  }
  if (hasExit(goal, EAST)) {
    uint16_t nextCell = cellEast(goal);
    queue.add(FloodInfo(cost, nextCell, 1,  DIR_E, WEST));
    mCost[nextCell] = cost;
  }
  if (hasExit(goal, SOUTH)) {
    uint16_t nextCell = cellSouth(goal);
    queue.add(FloodInfo(cost, nextCell, 1,  DIR_S, NORTH));
    mCost[nextCell] = cost;
  }
  if (hasExit(goal, WEST)) {
    uint16_t nextCell = cellWest(goal);
    queue.add(FloodInfo(cost, nextCell, 1,  DIR_W, EAST));
    mCost[nextCell] = cost;
  }
  //
  // each (accessible) cell will be processed only once
  while ((queue.size() > 0)) {
    FloodInfo info = queue.fetch();
    uint16_t here = info.cell;
    uint8_t entryDir = info.entryDir;
    uint8_t entryWall = info.entryWall;
    /*
     * test each wall for an exit. Skip any blocked, or already used exits
     */
    for (uint8_t exitWall = 0; exitWall < 4; exitWall++) {
      if (exitWall == entryWall) {
        continue;
      }
      if (hasWall(here, exitWall)) {
        continue;
      }
      uint16_t nextCell = neighbour(here, exitWall);
      if (mCost[nextCell] < MAX_COST) {
        continue;
      }
      uint8_t exitDir = getExitDirection[entryWall * 4 + exitWall];
      uint8_t newRunLength = info.runLength;
      uint16_t turnSize = abs(int(entryDir) - int(exitDir));
      if (turnSize > 4) {
        turnSize = 7 - turnSize;
      }
      uint16_t turnCost = 0; ;
      if (entryDir == exitDir) {
        newRunLength ++;
      } else {
        newRunLength = 1;
        turnCost = turnSize * 90 + 45;
      }
      uint16_t newCost = ((exitDir & 1) == 0) ? orthoCostTable[newRunLength] : diagCostTable[newRunLength];
      newCost += turnCost + mCost[here];
      mCost[nextCell] = newCost;
      queue.add(FloodInfo(newCost, nextCell, newRunLength,  exitDir, opposite(exitWall)));
    }
  }
  return mCost[0];
}



bool Maze::isSolved(void) {
  return mIsSolved;
}

uint8_t Maze::opposite(uint8_t direction) {
  return behind(direction);
}
