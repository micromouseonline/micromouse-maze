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
  0,  98, 75, 63, 55, 50, 46, 43,
  40, 38, 36, 36, 36, 36, 36, 36,
  36, 36, 36, 36, 36, 36, 36, 36,
  36, 36, 36, 36, 36, 36, 36, 36,
  36, 36, 36, 36, 36, 36, 36, 36,
  36, 36, 36, 36, 36, 36, 36, 36,
  36, 36, 36, 36, 36, 36, 36, 36,
  36, 36, 36, 36, 36, 36, 36, 36,
};

const uint16_t diagCostTable[] =
  // low speed costs ( vturn = 1.5m/s/s, acc = 13000 mm/s/s)
{
  0, 73, 58, 50, 44, 40, 37, 35,
  33, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31,
  31, 31, 31, 31, 31, 31, 31, 31,
};


// high speed costs (vturn = 2000 mm/s, acc = 16667 mm/s/s)
//{0,56,47,41,37,34,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31};

Maze::Maze(uint16_t width) :
  mWidth(width) {
  //  addToGoalArea(7, 7);
  //  resetToEmptyMaze();
};

uint16_t Maze::width() const {
  return mWidth;
}

uint16_t Maze::numCells() {
  return mWidth * mWidth;
}

void Maze::clearData() {
  for (uint16_t i = 0; i < 1024; i++) {
    mCost[i] = MAX_COST;
    mDirection[i] = NORTH;
    xWalls[i] = 0xf0; // all unseen exits
  }
  clearGoalArea();
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
  clearUnknowns();
  addToGoalArea(7, 7);
  if (mWidth == 16) {
    addToGoalArea(7, 8);
    addToGoalArea(8, 7);
    addToGoalArea(8, 8);
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
  if (wallData & 0x80) {
    addToGoalArea(cell);
  }
}

/**
 * by laboriously seeting each wall in each cell, the maze will always
 * be left in a legal state where there can be no walls that are present
 * in a cell and absent when lookd at from the other side in the next cell.
 */
void Maze::copyMazeFromFileData(const uint8_t *wallData, uint16_t cellCount) {
  clearData();
  if (cellCount == 1024) {
    setWidth(32);
  } else {
    setWidth(16);
  }
  //  if (cellCount > numCells()) {
  //    return; // ERROR here
  //  }
  if (wallData) {
    for (uint16_t cell = 0; cell < numCells(); cell++) {
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

uint16_t Maze::goal() const {
  if (goalArea.size() > 0) {
    return goalArea.front();
  } else {
    return 0;
  }
}

void Maze::setGoal(uint16_t goal) {
  clearGoalArea();
  goalArea.push_back(goal);
}

uint8_t Maze::walls(uint16_t cell) const {
  uint8_t result = 0;
  for (int i = 0; i < 4; i++) {
    if (!hasExit(cell, i)) {
      result |= (1 << i);
    }
  }
  return result;
}


uint8_t Maze::openWalls(uint16_t cell)  {
  int openCloseMask = mOpenCloseMask;
  mOpenCloseMask = OPEN_MASK;
  uint8_t   result = 0;
  for (int i = 0; i < 4; i++) {
    if (!hasExit(cell, i)) {
      result |= (1 << i);
    }
  }
  mOpenCloseMask = openCloseMask;
  return result;
}

uint8_t Maze::closedWalls(uint16_t cell)  {
  int openCloseMask = mOpenCloseMask;
  mOpenCloseMask = CLOSED_MASK;
  uint8_t   result = 0;
  for (int i = 0; i < 4; i++) {
    if (!hasExit(cell, i)) {
      result |= (1 << i);
    }
  }
  mOpenCloseMask = openCloseMask;
  return result;
}


bool Maze::isSeen(uint16_t cell, uint8_t direction) {
  return (xWalls[cell] & (0x10 << direction)) == 0;
}

bool Maze::hasExit(uint16_t cell, uint8_t direction) const {
  uint8_t maskedWalls = xWalls[cell] & (mOpenCloseMask << direction);
  return maskedWalls == 0;
}

bool Maze::hasWall(uint16_t cell, uint8_t direction) {
  return !hasExit(cell, direction);
}

bool Maze::hasRealExit(uint16_t cell, uint8_t direction) {
  return isSeen(cell, direction) && hasExit(cell, direction);
}

bool Maze::hasRealWall(uint16_t cell, uint8_t direction) {
  return isSeen(cell, direction) && hasWall(cell, direction);
}

uint8_t Maze::direction(uint16_t cell) {
  return mDirection[cell];
}

void Maze::setDirection(uint16_t cell, uint8_t direction) {
  mDirection[cell] = direction;
}

bool Maze::isVisited(uint16_t cell) {
  return (xWalls[cell] & ALL_UNSEEN) == 0;
}


void Maze::setVisited(uint16_t cell) {
  xWalls[cell] &= ~ALL_UNSEEN;
}

void Maze::clearVisited(uint16_t cell) {
  xWalls[cell] |= ALL_UNSEEN;
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
      xWalls[cell] &= ~UNSEEN_NORTH;
      xWalls[cell] |= WALL_NORTH;
      xWalls[nextCell] &= ~UNSEEN_SOUTH;
      xWalls[nextCell] |= WALL_SOUTH;
      break;
    case EAST:
      xWalls[cell] &= ~UNSEEN_EAST;
      xWalls[cell] |= WALL_EAST;
      xWalls[nextCell] &= ~UNSEEN_WEST;
      xWalls[nextCell] |= WALL_WEST;
      break;
    case SOUTH:
      xWalls[cell] &= ~UNSEEN_SOUTH;
      xWalls[cell] |= WALL_SOUTH;
      xWalls[nextCell] &= ~UNSEEN_NORTH;
      xWalls[nextCell] |= WALL_NORTH;
      break;
    case WEST:
      xWalls[cell] &= ~UNSEEN_WEST;
      xWalls[cell] |= WALL_WEST;
      xWalls[nextCell] &= ~UNSEEN_EAST;
      xWalls[nextCell] |= WALL_EAST;
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
      xWalls[cell] &= ~UNSEEN_NORTH;
      xWalls[cell] &= ~WALL_NORTH;
      xWalls[nextCell] &= ~UNSEEN_SOUTH;
      xWalls[nextCell] &= ~WALL_SOUTH;
      break;
    case EAST:
      xWalls[cell] &= ~UNSEEN_EAST;
      xWalls[cell] &= ~WALL_EAST;
      xWalls[nextCell] &= ~UNSEEN_WEST;
      xWalls[nextCell] &= ~WALL_WEST;
      break;
    case SOUTH:
      xWalls[cell] &= ~UNSEEN_SOUTH;
      xWalls[cell] &= ~WALL_SOUTH;
      xWalls[nextCell] &= ~UNSEEN_NORTH;
      xWalls[nextCell] &= ~WALL_NORTH;
      break;
    case WEST:
      xWalls[cell] &= ~UNSEEN_WEST;
      xWalls[cell] &= ~WALL_WEST;
      xWalls[nextCell] &= ~UNSEEN_EAST;
      xWalls[nextCell] &= ~WALL_EAST;
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
//closed
void Maze::setUnknowns() {
  mOpenCloseMask = CLOSED_MASK;
}
//open
void Maze::clearUnknowns() {
  mOpenCloseMask = OPEN_MASK;
}

uint16_t Maze::cost(uint16_t cell) {
  return mCost[cell];
}

/*
 * Distance is returned based upon the setting of the wall flag.
 * No account is taken of the 'wall seen' flag.
 */
uint16_t Maze::costNorth(uint16_t cell) {
  if (!hasExit(cell, NORTH)) {
    return MAX_COST;
  }
  cell = cellNorth(cell);
  return mCost[cell];
}

uint16_t Maze::costEast(uint16_t cell) {
  if (hasExit(cell, EAST)) {
    cell = cellEast(cell);
    return mCost[cell];
  } else {
    return MAX_COST;
  }
}

uint16_t Maze::costSouth(uint16_t cell) {
  if (hasExit(cell, SOUTH)) {
    cell = cellSouth(cell);
    return mCost[cell];
  } else {
    return MAX_COST;
  }
}

uint16_t Maze::costWest(uint16_t cell) {
  if (hasExit(cell, WEST)) {
    cell = cellWest(cell);
    return mCost[cell];
  } else {
    return MAX_COST;
  }
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
 *
 *  NOTE: Should this use the open or closed maze?
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
    FloodInfo info = queue.front();
    queue.pop();
    /*
     * test each wall for an exit. Skip any blocked, or already used exits
     */
    for (uint8_t exitWall = 0; exitWall < 4; exitWall++) {
      if (exitWall == info.entryWall) {
        continue;
      }
      if (!hasExit(info.cell, exitWall)) {
        continue;
      }
      uint16_t nextCell = neighbour(info.cell, exitWall);
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
      if (newCost < mCost[nextCell]) {
        mCost[nextCell] = newCost;
        queue.push(FloodInfo(newCost, nextCell, newRunLength, exitDir, opposite(exitWall)));
      }
    }
  }
  //NOTE: this need not be done here - only when the directions are acually needed
  updateDirections();
  return mCost[0];
}

uint16_t Maze::manhattanFlood(uint16_t target) {
  PriorityQueue<uint16_t> queue;
  initialiseFloodCosts(target);
  queue.push(target);
  while (queue.size() > 0) {
    uint16_t cell = queue.front();
    queue.pop();
    uint16_t newCost = mCost[cell];
    newCost++;
    for (uint8_t direction = 0; direction < 4; direction++) {
      if (hasExit(cell, direction)) {
        uint16_t nextCell = neighbour(cell, direction);
        if (mCost[nextCell] > newCost) {
          mCost[nextCell] = newCost;
          queue.push(nextCell);
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
    queue.push(FloodInfo(cost, nextCell, 1, DIR_N, SOUTH));
    mCost[nextCell] = cost;
  }
  if (hasExit(goal, EAST)) {
    uint16_t nextCell = cellEast(goal);
    queue.push(FloodInfo(cost, nextCell, 1, DIR_E, WEST));
    mCost[nextCell] = cost;
  }
  if (hasExit(goal, SOUTH)) {
    uint16_t nextCell = cellSouth(goal);
    queue.push(FloodInfo(cost, nextCell, 1, DIR_S, NORTH));
    mCost[nextCell] = cost;
  }
  if (hasExit(goal, WEST)) {
    uint16_t nextCell = cellWest(goal);
    queue.push(FloodInfo(cost, nextCell, 1, DIR_W, EAST));
    mCost[nextCell] = cost;
  }
}

bool Maze::isSolved() {
  return mIsSolved;
}

void Maze::save(uint8_t *data) {
  for (int i = 0; i < numCells(); i++) {
    data[i] = xWalls[i];
  }
};

void Maze::load(const uint8_t *data) {
  for (int i = 0; i < numCells(); i++) {
    xWalls[i] = data[i];
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
  queue.push(target);
  while (queue.size() > 0) {
    uint16_t newCost;
    auto here = static_cast<uint16_t>(queue.front());
    queue.pop();
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
          queue.push(nextCell);
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
  queue.push(target);
  while (queue.size() > 0) {
    auto here = static_cast<uint16_t>(queue.front());
    queue.pop();
    auto nextCost = static_cast<uint16_t>(mCost[here] + 1);
    for (uint8_t exit = 0; exit < 4; exit++) {
      if (hasExit(here, exit)) {
        uint16_t next = neighbour(here, exit);
        if (mDirection[next] == INVALID_DIRECTION) {
          mDirection[next] = behind(exit);
          mCost[next] = nextCost;
          queue.push(next);
        }
      }
    }
  }
  return mCost[0];
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

Maze::FloodType Maze::getFloodType() const {
  return mFloodType;
}

void Maze::setWidth(uint16_t mWidth) {
  Maze::mWidth = mWidth;
  clearData();
  //  resetToEmptyMaze();
}

uint8_t Maze::getXWalls(int cell) const {
  return xWalls[cell];
}

void Maze::clearGoalArea() {
  goalArea.clear();
}

void Maze::addToGoalArea(int cell) {
  goalArea.push_back(cell);
}

void Maze::addToGoalArea(int x, int y) {
  goalArea.push_back(cellID(x, y));
}

bool Maze::goalContains(int cell) const {
  return end(goalArea) != find(begin(goalArea), end(goalArea), cell);
}

bool Maze::goalContains(int x, int y) const {
  int cell = cellID(x, y);
  return end(goalArea) != find(begin(goalArea), end(goalArea), cell);
}



int Maze::goalAreaSize() const {
  return goalArea.size();
}

void Maze::removeFromGoalArea(int x, int y) {
  removeFromGoalArea(cellID(x, y));
}

void Maze::removeFromGoalArea(int cell) {
  goalArea.remove(cell);
}


std::list<int> Maze::getGoalArea() const {
  return goalArea;
}

void Maze::setGoalArea(std::list<int> &goalArea) {
  this->goalArea = goalArea;
}
