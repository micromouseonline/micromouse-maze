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
    mWalls[i].wall.north = UNKNOWN;
    mWalls[i].wall.east = UNKNOWN;
    mWalls[i].wall.south = UNKNOWN;
    mWalls[i].wall.west = UNKNOWN;
  }
}

void Maze::resetToEmptyMaze() {
  clearData();
  for (uint16_t i = 0; i < width(); i++) {
    setWall(cell(0, i), WEST);
    setWall(cell(width() - 1, i), EAST);
    setWall(cell(i, 0), SOUTH);
    setWall(cell(i, width() - 1), NORTH);
  }
  setWall(0, EAST);
  clearWall(0, NORTH);
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
      uint8_t walls = wallData[cell];
      if (walls & 0x01) {
        setWall(cell, NORTH);
      } else {
        clearWall(cell, NORTH);
      }
      if (walls & 0x02) {
        setWall(cell, EAST);
      } else {
        clearWall(cell, EAST);
      }
      if (walls & 0x04) {
        setWall(cell, SOUTH);
      } else {
        clearWall(cell, SOUTH);
      }
      if (walls & 0x08) {
        setWall(cell, WEST);
      } else {
        clearWall(cell, WEST);
      }
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

uint8_t Maze::fwalls(uint16_t cell) const {
  uint8_t result = 0;
  if (hasWall(cell, NORTH, OPEN_MASK)) {
    result |= 0x01;
  }
  if (hasWall(cell, EAST, OPEN_MASK)) {
    result |= 0x02;
  }
  if (hasWall(cell, SOUTH, OPEN_MASK)) {
    result |= 0x04;
  }
  if (hasWall(cell, WEST, OPEN_MASK)) {
    result |= 0x08;
  }
  return result;
}
uint8_t Maze::walls(uint16_t cell) const {
  return fwalls(cell);
}

bool Maze::hasExit(uint16_t cell, uint8_t direction, uint8_t mask = OPEN_MASK) const {
  // regardless of whether it has been seen
  bool result;
  switch (direction) {
    case NORTH:
      result = isExit(mWalls[cell].wall.north, mask);
      break;
    case EAST:
      result = isExit(mWalls[cell].wall.east, mask);
      break;
    case SOUTH:
      result = isExit(mWalls[cell].wall.south, mask);
      break;
    case WEST:
      result = isExit(mWalls[cell].wall.west, mask);
      break;
  }
  return result;
}


bool Maze::hasWall(uint16_t cell, uint8_t direction, uint8_t mask = OPEN_MASK) const {
  bool result = false;
  switch (direction) {
    case NORTH:
      result = isWall(mWalls[cell].wall.north, mask);
      break;
    case EAST:
      result = isWall(mWalls[cell].wall.east, mask);
      break;
    case SOUTH:
      result = isWall(mWalls[cell].wall.south, mask);
      break;
    case WEST:
      result = isWall(mWalls[cell].wall.west, mask);
      break;
  }
  return result;
};



bool Maze::hasMaskedWall(uint16_t cell, uint8_t direction) {
  bool result;
  switch (direction) {
    case NORTH:
      result = isWall(mWalls[cell].wall.north, mSafetyMask);
      //      result = !((mWalls[cell].wall.north & mSafetyMask) == EXIT);
      break;
    case EAST:
      result = isWall(mWalls[cell].wall.east, mSafetyMask);
      break;
    case SOUTH:
      result = isWall(mWalls[cell].wall.south, mSafetyMask);
      break;
    case WEST:
      result = isWall(mWalls[cell].wall.west, mSafetyMask);
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
  return (mWalls[cell].byte & 0xAA) == 0;
}

void Maze::setVisited(uint16_t cell) {
  mWalls[cell].byte &= 0x55;
}

void Maze::clearVisited(uint16_t cell) {
  mWalls[cell].byte |= 0xAA;
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
      mWalls[cell].wall.north = WALL;
      mWalls[nextCell].wall.south = WALL;
      break;
    case EAST:
      mWalls[cell].wall.east = WALL;
      mWalls[nextCell].wall.west = WALL;
      break;
    case SOUTH:
      mWalls[cell].wall.south = WALL;
      mWalls[nextCell].wall.north = WALL;
      break;
    case WEST:
      mWalls[cell].wall.west = WALL;
      mWalls[nextCell].wall.east = WALL;
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
      mWalls[cell].wall.north = EXIT;
      mWalls[nextCell].wall.south = EXIT;
      break;
    case EAST:
      mWalls[cell].wall.east = EXIT;
      mWalls[nextCell].wall.west = EXIT;
      break;
    case SOUTH:
      mWalls[cell].wall.south = EXIT;
      mWalls[nextCell].wall.north = EXIT;
      break;
    case WEST:
      mWalls[cell].wall.west = EXIT;
      mWalls[nextCell].wall.east = EXIT;
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
}

void Maze::clearUnknowns() {
  mSafetyMask = OPEN_MASK;
}

uint16_t Maze::cost(uint16_t cell) {
  return mCost[cell];
}

uint16_t Maze::cost(uint16_t cell, uint16_t direction) {
  uint16_t result = MAX_COST;
  switch (direction) {
    case NORTH:
      if (isExit(mWalls[cell].wall.north, mSafetyMask)) {
        cell = cellNorth(cell);
        result = mCost[cell];
      }
      break;
    case EAST:
      if (isExit(mWalls[cell].wall.east, mSafetyMask)) {
        cell = cellEast(cell);
        result = mCost[cell];
      }
      break;
    case SOUTH:
      if (isExit(mWalls[cell].wall.south, mSafetyMask)) {
        cell = cellSouth(cell);
        result = mCost[cell];
      }
      break;
    case WEST:
      if (isExit(mWalls[cell].wall.west, mSafetyMask)) {
        cell = cellWest(cell);
        result = mCost[cell];
      }
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
 *  It also only works on the classic maze.
 *
 *  TODO: Better to examine the direction through the gate and
 *  work out how far the mouse can travel in a straight line after that.
 */
void Maze::recalculateGoal() {
  if (width() != 16) {
    return; // only works for classic maze
  }
  uint16_t newGoal = goal();
  // count the entrances
  int entranceCount = 0;

  if (hasExit(0x77, SOUTH, OPEN_MASK)) {
    entranceCount++;
    newGoal = 0x78;
  };
  if (hasExit(0x77, WEST, OPEN_MASK)) {
    entranceCount++;
    newGoal = 0x87;
  };
  if (hasExit(0x78, WEST, OPEN_MASK)) {
    entranceCount++;
    newGoal = 0x88;
  };
  if (hasExit(0x78, NORTH, OPEN_MASK)) {
    entranceCount++;
    newGoal = 0x77;
  };
  if (hasExit(0x88, NORTH, OPEN_MASK)) {
    entranceCount++;
    newGoal = 0x87;
  };
  if (hasExit(0x88, EAST, OPEN_MASK)) {
    entranceCount++;
    newGoal = 0x78;
  };
  if (hasExit(0x87, EAST, OPEN_MASK)) {
    entranceCount++;
    newGoal = 0x77;
  };
  if (hasExit(0x87, SOUTH, OPEN_MASK)) {
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
      if (hasMaskedWall(info.cell, exitWall)) {
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
    if (isExit(mWalls[cell].wall.north, mSafetyMask)) {
      uint16_t nextCell = neighbour(cell, NORTH);
      if (mCost[nextCell] == MAX_COST) {
        mCost[nextCell] = newCost;
        queue.add(nextCell);
      }
    }

    if (isExit(mWalls[cell].wall.east, mSafetyMask)) {
      uint16_t nextCell = neighbour(cell, EAST);
      if (mCost[nextCell] == MAX_COST) {
        mCost[nextCell] = newCost;
        queue.add(nextCell);
      }
    }

    if (isExit(mWalls[cell].wall.south, mSafetyMask)) {
      uint16_t nextCell = neighbour(cell, SOUTH);
      if (mCost[nextCell] == MAX_COST) {
        mCost[nextCell] = newCost;
        queue.add(nextCell);
      }
    }

    if (isExit(mWalls[cell].wall.west, mSafetyMask)) {
      uint16_t nextCell = neighbour(cell, WEST);
      if (mCost[nextCell] == MAX_COST) {
        mCost[nextCell] = newCost;
        queue.add(nextCell);
      }
    }
  }
  updateDirections();
  return mCost[0];
};

void Maze::seedQueue(PriorityQueue<FloodInfo> &queue, uint16_t goal, uint16_t cost) {
  if (!hasMaskedWall(goal, NORTH)) {
    uint16_t nextCell = cellNorth(goal);
    queue.add(FloodInfo(cost, nextCell, 1, DIR_N, SOUTH));
    mCost[nextCell] = cost;
  }
  if (!hasMaskedWall(goal, EAST)) {
    uint16_t nextCell = cellEast(goal);
    queue.add(FloodInfo(cost, nextCell, 1, DIR_E, WEST));
    mCost[nextCell] = cost;
  }
  if (!hasMaskedWall(goal, SOUTH)) {
    uint16_t nextCell = cellSouth(goal);
    queue.add(FloodInfo(cost, nextCell, 1, DIR_S, NORTH));
    mCost[nextCell] = cost;
  }
  if (!hasMaskedWall(goal, WEST)) {
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
    data[i] = mWalls[i].byte;
  }
};

void Maze::load(const uint8_t *data) {
  for (int i = 0; i < numCells(); i++) {
    mWalls[i].byte = data[i];
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

    wall_t wallsHere = mWalls[here];
    if (isExit(wallsHere.wall.north, mSafetyMask)) {
      uint16_t nextCell = neighbour(here, NORTH);
      if (thisDirection == NORTH) {
        newCost = costHere + aheadCost;
      } else {
        newCost = costHere + mCornerWeight;
      }
      if (mCost[nextCell] > newCost) {
        mCost[nextCell] = newCost;
        mDirection[nextCell] = NORTH;
        queue.add(nextCell);
      }
    }

    if (isExit(wallsHere.wall.east, mSafetyMask)) {
      uint16_t nextCell = neighbour(here, EAST);
      if (thisDirection == EAST) {
        newCost = costHere + aheadCost;
      } else {
        newCost = costHere + mCornerWeight;
      }
      if (mCost[nextCell] > newCost) {
        mCost[nextCell] = newCost;
        mDirection[nextCell] = EAST;
        queue.add(nextCell);
      }
    }

    if (isExit(wallsHere.wall.south, mSafetyMask)) {
      uint16_t nextCell = neighbour(here, SOUTH);
      if (thisDirection == SOUTH) {
        newCost = costHere + aheadCost;
      } else {
        newCost = costHere + mCornerWeight;
      }
      if (mCost[nextCell] > newCost) {
        mCost[nextCell] = newCost;
        mDirection[nextCell] = SOUTH;
        queue.add(nextCell);
      }
    }

    if (isExit(wallsHere.wall.west, mSafetyMask)) {
      uint16_t nextCell = neighbour(here, WEST);
      if (thisDirection == WEST) {
        newCost = costHere + aheadCost;
      } else {
        newCost = costHere + mCornerWeight;
      }
      if (mCost[nextCell] > newCost) {
        mCost[nextCell] = newCost;
        mDirection[nextCell] = WEST;
        queue.add(nextCell);
      }
    }

  }
  updateDirections();
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

wall_t Maze::xwalls(uint16_t cell) const {
  return mWalls[cell];
}


uint8_t Maze::getMSafetyMask() const {
  return mSafetyMask;
}

void Maze::loadFromFileData(const uint8_t *fileData) {
  clearData();
  if (fileData) {
    for (uint16_t cell = 0; cell < numCells(); cell++) {
      uint8_t walls = fileData[cell];
      if (walls & 0x01) {
        setWall(cell, NORTH);
      } else {
        clearWall(cell, NORTH);
      }
      if (walls & 0x02) {
        setWall(cell, EAST);
      } else {
        clearWall(cell, EAST);
      }
      if (walls & 0x04) {
        setWall(cell, SOUTH);
      } else {
        clearWall(cell, SOUTH);
      }
      if (walls & 0x08) {
        setWall(cell, WEST);
      } else {
        clearWall(cell, WEST);
      }
    }
  }
}


