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
const uint16_t costTable[] =
    //                      {100, 22, 16, 12, 10, 9, 8, 7,
    //                         6, 6, 5, 5, 5, 5, 4, 4,
    //                         4, 4, 4, 4, 3, 3, 3, 3
    //                        };
    { 100, 13, 11, 9, 8, 7, 6, 6, 5, 5, 5, 5, 5, 4, 4, 4, 4 };


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
  mIsSolved = mPathCostClosed <= mPathCostOpen;
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

/*
      when each cell is added to the queue, we should store the direction
      to the cell we came from.
      when flooding using directions, I need to take into account my currnt
      heading so that I don't have to stop to turn around unless absolutely necessary.
      On the other hand, suppose the route found that way is much longer?
      This should not matter when exploring and should not happen when fast running?
      Ideally, the solver will produce a vector field telling me which way to LEAVE
      each cell to get to my goal.
      Generally, flooding out from the goal allows me to walk downhill but the
      starting direction is arbitrary.
      Flooding out from the start should let me get started sooner but my
      algorithm will have to be able to backtrack to makesure I have the best route.
      This starts to make it look more like an A* algorithm.
      Perhaps this is fine if I only need to go back one step. The queue based flooder
      here can store a direction in each cell that tells me how to find its predecessor
      then I can update the predecesor with a different cost and direction if necessary.
      Looks like it would be best if the flags, direction and distance for each cell
      was stored in a structure for neatness.
 */

/*
 *  TODO: Initialising the queue needs to be more clever.
 * For each exit from the goal cell, seed the queue with the corresponding neighbour
 * Note that single-cell goals may have multiple exits and the centre region in the
 * classic contest will also have a number of possible exits
 * */
uint16_t Maze::runLengthFlood(uint16_t goal) {
  openList.clear();
  // set every cell as unexamined
  for (uint16_t i = 0; i < numCells(); i++) {
    mCost[i] = MAX_COST;
  }
  // except the goal
  mCost[goal] = 0;
  mDirection[goal] = NORTH;
  //TODO: Guard against a closed-in goal
  if (hasExit(goal, NORTH)) {
    uint16_t nextCell = cellNorth(goal);
    openList.add(FloodInfo(0, nextCell, 0, 'F'));
    mDirection[nextCell] = NORTH;
    mCost[nextCell] = costTable[1];
    mDirection[goal] = NORTH;
  }
  if (hasExit(goal, EAST)) {
    uint16_t nextCell = cellEast(goal);
    openList.add(FloodInfo(0, nextCell, 0, 'F'));
    mDirection[nextCell] = EAST;
    mCost[nextCell] = costTable[1];
    mDirection[goal] = EAST;
  }
  if (hasExit(goal, WEST)) {
    uint16_t nextCell = cellWest(goal);
    openList.add(FloodInfo(0, nextCell, 0, 'F'));
    mDirection[nextCell] = WEST;
    mCost[nextCell] = costTable[1];
    mDirection[goal] = WEST;
  }
  if (hasExit(goal, SOUTH)) {
    uint16_t nextCell = cellSouth(goal);
    openList.add(FloodInfo(0, nextCell, 0, 'F'));
    mDirection[nextCell] = SOUTH;
    mCost[nextCell] = costTable[1];
    mDirection[goal] = SOUTH;
  }
  // each (accessible) cell will be processed only once
  uint16_t nextCost = 0;
  while ((openList.size() > 0)) {
    FloodInfo info = openList.fetch();
    uint16_t here = info.cell;
    uint8_t headingHere = mDirection[here];
    uint8_t nextHeading = headingHere;
    uint8_t runLength = info.runLength;

    char lastTurn = info.lastTurn;
    uint16_t nextCell = neighbour(here, nextHeading);

    // moving forwards
    if (hasExit(here, nextHeading)) {
      switch (lastTurn) {
        case 'R': // left turn into possible diagonal
        case 'L': // right turn into possible diagonal
          runLength += 1;
          nextCost = mCost[here] + (costTable[runLength] * 3) / 2;
          break;
        case 'F':
        default: // on a straight
          runLength += 1;
          nextCost = mCost[here] + costTable[runLength];
          break;
      }
      if (mCost[nextCell] == MAX_COST) {
        openList.add(FloodInfo(nextCost, nextCell, runLength, 'F'));
        mDirection[nextCell] = nextHeading;
        mCost[nextCell] = nextCost;
      }
    };

    //---------------try left
    nextHeading = leftOf(headingHere);
    nextCell = neighbour(here, nextHeading);
    if (hasExit(here, nextHeading)) {
      switch (lastTurn) {
        case 'R': // on a diagonal
          runLength += 1;
          nextCost = mCost[here] + (costTable[runLength] * 7) / 10;
          break;
        case 'L': // 180 turn?
          runLength = 1;
          nextCost = mCost[here] + (costTable[runLength] * 3) / 2;
          break;
        case 'F':
        default :  // left turn into possible diagonal
          runLength = 1;
          nextCost = mCost[here] + (costTable[runLength] * 3) / 4;
          break;

      }
      if (mCost[nextCell] == MAX_COST) {
        openList.add(FloodInfo(nextCost, nextCell, runLength, 'L'));
        mDirection[nextCell] = nextHeading;
        mCost[nextCell] = nextCost;
      }
    }
    //---------------try right
    nextHeading = rightOf(headingHere);
    nextCell = neighbour(here, nextHeading);
    if (hasExit(here, nextHeading)) {
      switch (lastTurn) {
        case 'R': // 180 turn?
          runLength = 1;
          nextCost = mCost[here] + (costTable[runLength] * 3) / 2;
          break;
        case 'L': // on a diagonal
          runLength += 1;
          nextCost = mCost[here] + (costTable[runLength] * 7) / 10;
          break;
        case 'F':
        default :  // left turn into possible diagonal
          runLength = 1;
          nextCost = mCost[here] + (costTable[runLength] * 3) / 4;
          break;

      }
      if (mCost[nextCell] == MAX_COST) {
        openList.add(FloodInfo(nextCost, nextCell, runLength, 'R'));
        mDirection[nextCell] = nextHeading;
        mCost[nextCell] = nextCost;
      }
    }
  }
  updateDirections();
  return mCost[0];
}


bool Maze::isSolved(void) {
  return mIsSolved;
}
