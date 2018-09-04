/************************************************************************
*
* Copyright (C) 2017 by Peter Harrison. www.micromouseonline.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without l> imitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
************************************************************************/
#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "mazeconstants.h"
#include "floodinfo.h"
#include "priorityqueue.h"
#include "maze.h"

/*
 * The runlength flood calculates costs based on the length of straights
 */
const uint16_t orthoCostTable[] =
  // low speed costs ( vturn = 1.5m/s/s, acc = 13000 mm/s/s)
{
  0, 98, 75, 63, 55, 50, 46, 43, 40, 38, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36,
};

const uint16_t diagCostTable[] =
  // low speed costs ( vturn = 1.5m/s/s, acc = 13000 mm/s/s)
{
  0, 73, 58, 50, 44, 40, 37, 35, 33, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
};

// high speed costs (vturn = 2000 mm/s, acc = 16667 mm/s/s)
//{0,56,47,41,37,34,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31};

Maze::Maze(uint16_t width) :
  mWidth(width),
  mGoal(DEFAULT_GOAL),
  mPathCostOpen(MAX_COST),
  mPathCostClosed(MAX_COST),
  mIsSolved(false),
  mFloodType(RUNLENGTH_FLOOD),
  mCornerWeight(3),
  mSafetyMask(CLOSED_MASK) {
  resetToEmptyMaze();
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
    xWalls[i].wall.north = UNKNOWN;
    xWalls[i].wall.east = UNKNOWN;
    xWalls[i].wall.south = UNKNOWN;
    xWalls[i].wall.west = UNKNOWN;
  }
}

void Maze::resetToEmptyMaze() {
  clearData();
  for (uint16_t i = 0; i < width(); i++) {
    setWall(i, WEST);
    setWall(static_cast<uint16_t>(width() * (width() - 1) + i), EAST);
    setWall(i * width(), SOUTH);
    setWall(static_cast<uint16_t>(width() * i + width() - 1), NORTH);
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

uint8_t Maze::ahead(uint8_t direction) {
  return direction;
}

uint8_t Maze::rightOf(uint8_t direction) {
  return (uint8_t)((direction + 1) % 4);
}

uint8_t Maze::leftOf(uint8_t direction) {
  return (uint8_t)((direction + 3) % 4);
}

uint8_t Maze::behind(uint8_t direction) {
  return (uint8_t)((direction + 2) % 4);
}

uint8_t Maze::opposite(uint8_t direction) {
  return behind(direction);
}

uint8_t Maze::differenceBetween(uint8_t oldDirection, uint8_t newDirection) {
  return static_cast<uint8_t>((newDirection - oldDirection) & 0x03);

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

uint8_t Maze::walls(uint16_t cell) const {
  uint8_t result = 0;
  result = static_cast<uint8_t>(mWalls[cell] & 0x0F);
  return result;
}


bool Maze::hasExit(uint16_t cell, uint8_t direction) {
  return (mWalls[cell] & (0x01 << direction)) == 0;
}

bool Maze::hasWall(uint16_t cell, uint8_t direction) {
  return (mWalls[cell] & (0x01 << direction)) != 0;
}

bool Maze::hasRealExit(uint16_t cell, uint8_t direction) {
  bool result;
  switch (direction) {
    case NORTH:
      result = xWalls[cell].wall.north == EXIT;
      break;
    case EAST:
      result = xWalls[cell].wall.east == EXIT;
      break;
    case SOUTH:
      result = xWalls[cell].wall.south == EXIT;
      break;
    case WEST:
      result = xWalls[cell].wall.west == EXIT;
      break;
  }
  return result;
}

bool Maze::hasRealWall(uint16_t cell, uint8_t direction) {
  bool result;
  switch (direction) {
    case NORTH:
      result = xWalls[cell].wall.north == WALL;
      break;
    case EAST:
      result = xWalls[cell].wall.east == WALL;
      break;
    case SOUTH:
      result = xWalls[cell].wall.south == WALL;
      break;
    case WEST:
      result = xWalls[cell].wall.west == WALL;
      break;
  }
  return result;
}

uint8_t Maze::direction(uint16_t cell) {
  return mDirection[cell];
}

void Maze::setDirection(uint16_t cell, uint8_t direction) {
  mDirection[cell] = direction;
}

bool Maze::isVisited(uint16_t cell) {
  return ((mWalls[cell] & VISITED) == VISITED);
}

void Maze::setVisited(uint16_t cell) {
  mWalls[cell] |= VISITED;
  xWalls[cell].byte &= 0x55;
}

void Maze::clearVisited(uint16_t cell) {
  mWalls[cell] &= ~VISITED;
  xWalls[cell].byte |= 0xAA;
}

/*
 * unconditionally adds a wall in the map.
 * over-writes whatever is there.
 * should only be used when setting up a maze.
 * To update the maze when running, use updateWalls(cell,wallData)
 */
void Maze::setWall(uint16_t cell, uint8_t direction) {
  uint16_t nextCell = neighbour(cell, direction);
  switch (direction) {
    case NORTH:
      xWalls[cell].wall.north = WALL;
      xWalls[nextCell].wall.south = WALL;
      mWalls[cell] |= CHECKED_NORTH + WALL_NORTH;
      mWalls[nextCell] |= CHECKED_SOUTH + WALL_SOUTH;
      break;
    case EAST:
      xWalls[cell].wall.east = WALL;
      xWalls[nextCell].wall.west = WALL;
      mWalls[cell] |= CHECKED_EAST + WALL_EAST;
      mWalls[nextCell] |= CHECKED_WEST + WALL_WEST;
      break;
    case SOUTH:
      xWalls[cell].wall.south = WALL;
      xWalls[nextCell].wall.north = WALL;
      mWalls[cell] |= CHECKED_SOUTH + WALL_SOUTH;
      mWalls[nextCell] |= CHECKED_NORTH + WALL_NORTH;
      break;
    case WEST:
      xWalls[cell].wall.west = WALL;
      xWalls[nextCell].wall.east = WALL;
      mWalls[cell] |= CHECKED_WEST + WALL_WEST;
      mWalls[nextCell] |= CHECKED_EAST + WALL_EAST;
      break;
    default:
      ; // do nothing -although this is an error
      break;
  }
}

/*
 * unconditionally clears a wall in the map.
 * over-writes whatever is there.
 * normally used only when setting up a maze.
 * To update the maze when running, use updateMap(cell,wallData)
 */
void Maze::clearWall(uint16_t cell, uint8_t direction) {
  uint16_t nextCell = neighbour(cell, direction);
  switch (direction) {
    case NORTH:
      xWalls[cell].wall.north = EXIT;
      xWalls[nextCell].wall.south = EXIT;
      mWalls[cell] &= ~WALL_NORTH;
      mWalls[cell] |= CHECKED_NORTH;
      mWalls[nextCell] &= ~WALL_SOUTH;
      mWalls[nextCell] |= CHECKED_SOUTH;
      break;
    case EAST:
      xWalls[cell].wall.east = EXIT;
      xWalls[nextCell].wall.west = EXIT;
      mWalls[cell] &= ~WALL_EAST;
      mWalls[cell] |= CHECKED_EAST;
      mWalls[nextCell] &= ~WALL_WEST;
      mWalls[nextCell] |= CHECKED_WEST;
      break;
    case SOUTH:
      xWalls[cell].wall.south = EXIT;
      xWalls[nextCell].wall.north = EXIT;
      mWalls[cell] &= ~WALL_SOUTH;
      mWalls[cell] |= CHECKED_SOUTH;
      mWalls[nextCell] &= ~WALL_NORTH;
      mWalls[nextCell] |= CHECKED_NORTH;
      break;
    case WEST:
      xWalls[cell].wall.west = EXIT;
      xWalls[nextCell].wall.east = EXIT;
      mWalls[cell] &= ~WALL_WEST;
      mWalls[cell] |= CHECKED_WEST;
      mWalls[nextCell] &= ~WALL_EAST;
      mWalls[nextCell] |= CHECKED_EAST;
      break;
    default:
      ; // do nothing -although this is an error
      break;
  }
}

/*
 * Updates the map by adding walls
 * Used when exploring only.
 *
 */
void Maze::updateMap(uint16_t cell, uint8_t wallData) {
  if (wallData & WALL_NORTH) {
    setWall(cell, NORTH);
  } else {
    clearWall(cell, NORTH);
  }
  if (wallData & WALL_EAST) {
    setWall(cell, EAST);
  } else {
    clearWall(cell, EAST);
  }
  if (wallData & WALL_SOUTH) {
    setWall(cell, SOUTH);
  } else {
    clearWall(cell, SOUTH);
  }
  if (wallData & WALL_WEST) {
    setWall(cell, WEST);
  } else {
    clearWall(cell, WEST);
  }
}

void Maze::setUnknowns() {
  mSafetyMask = CLOSED_MASK;
  for (uint16_t i = 0; i < numCells(); i++) {
    auto mask = static_cast<uint8_t>(~(mWalls[i] & 0xF0));
    mWalls[i] |= mask >> 4;
  }
}

void Maze::clearUnknowns() {
  mSafetyMask = OPEN_MASK;
  for (uint16_t i = 0; i < numCells(); i++) {
    auto mask = static_cast<uint8_t>(~(mWalls[i] & 0xF0));
    mWalls[i] &= ~(mask >> 4);
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

uint8_t Maze::directionToSmallest(uint16_t cell) {
  auto smallestDirection = INVALID_DIRECTION;
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

bool Maze::testForSolution() { // takes less than 3ms
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

  if (hasRealExit(0x77, SOUTH)) {
    entranceCount++;
    newGoal = 0x78;
  };
  if (hasRealExit(0x77, WEST)) {
    entranceCount++;
    newGoal = 0x87;
  };
  if (hasRealExit(0x78, WEST)) {
    entranceCount++;
    newGoal = 0x88;
  };
  if (hasRealExit(0x78, NORTH)) {
    entranceCount++;
    newGoal = 0x77;
  };
  if (hasRealExit(0x88, NORTH)) {
    entranceCount++;
    newGoal = 0x87;
  };
  if (hasRealExit(0x88, EAST)) {
    entranceCount++;
    newGoal = 0x78;
  };
  if (hasRealExit(0x87, EAST)) {
    entranceCount++;
    newGoal = 0x77;
  };
  if (hasRealExit(0x87, SOUTH)) {
    entranceCount++;
    newGoal = 0x88;
  };
  if (entranceCount != 0) {
    setGoal(newGoal);
  }
}

int32_t Maze::costDifference() {
  return int32_t(mPathCostClosed) - int32_t(mPathCostOpen);
}

uint16_t Maze::openMazeCost() const {
  return mPathCostOpen;
}

uint16_t Maze::closedMazeCost() const {
  return mPathCostClosed;
}

uint16_t Maze::flood(uint16_t target) {
  uint16_t cost = MAX_COST;
  switch (mFloodType) {
    case MANHATTAN_FLOOD:
      cost = manhattanFlood(target);
      break;
    case WEIGHTED_FLOOD:
      cost = weightedFlood(target);
      break;
    case RUNLENGTH_FLOOD:
      cost = runLengthFlood(target);
      break;
    case DIRECTION_FLOOD:
      cost = directionFlood(target);
      break;
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
 * For each exit from the goal cell, seed the queue with the corresponding
 * neighbour. Note that single-cell goals may have multiple exits and the
 * centre region in the classic contest will also have a number of possible
 * exits
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
      auto turnSize = static_cast<uint16_t>(abs(int(info.entryDir) - int(exitDir)));
      if (turnSize > 4) {
        turnSize = static_cast<uint16_t>(7 - turnSize);
      }
      uint16_t turnCost = 0;;
      if (info.entryDir == exitDir) {
        newRunLength++;
      } else {
        newRunLength = 1;
        turnCost = static_cast<uint16_t>(turnSize * 22); // MAGIC: empirical value for best-looking routes
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

bool Maze::isSolved() {
  return mIsSolved;
}

void Maze::save(uint8_t *data) {
  for (int i = 0; i < numCells(); i++) {
    data[i] = mWalls[i];
  }
};

void Maze::load(const uint8_t *data) {
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
    auto here = static_cast<uint16_t>(queue.head());
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
 * so that  a test for a solution can be made
 */

uint16_t Maze::directionFlood(uint16_t target) {
  PriorityQueue<int> queue;
  initialiseFloodCosts(target);
  queue.add(target);
  while (queue.size() > 0) {
    auto here = static_cast<uint16_t>(queue.head());
    auto nextCost = static_cast<uint16_t>(mCost[here] + 1);
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

Maze::FloodType Maze::floodType() {
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

uint8_t Maze::internalWalls(uint16_t cell) const {
  return mWalls[cell];
}

wall_t Maze::xwalls(uint16_t cell) const {
  return xWalls[cell];
}

uint8_t Maze::getMSafetyMask() const {
  return mSafetyMask;
};




