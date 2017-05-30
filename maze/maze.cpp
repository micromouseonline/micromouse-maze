//
// Created by Peter Harrison on 26/05/2017.
//

#include "mazeconstants.h"
#include "mazedata.h"

#include "maze.h"

/*
  maze.c
  common functions for manipulating the maze map
  and for creating the flooded route
 */
#include <stdio.h>
#include <stdint.h>


/*
 * The runlength flood calculates costs based on the length of straights
 */
const int costTable[] =
    //                      {100, 22, 16, 12, 10, 9, 8, 7,
    //                         6, 6, 5, 5, 5, 5, 4, 4,
    //                         4, 4, 4, 4, 3, 3, 3, 3
    //                        };
    {100, 13, 11, 9, 8, 7, 6, 6, 5, 5, 5, 5, 5, 4, 4, 4, 4};


Maze theMaze;

Maze::Maze() {
  mIsSolved = false;
  resetToEmptyMaze();
  setGoal(DEFAULT_GOAL);
};

bool Maze::testForSolution(void) { // takes less than 3ms
  setUnknowns();
  mPathCostOpen = flood(theMaze.goal());
  clearUnknowns();
  mPathCostClosed = flood(theMaze.goal());
  mCostDifference = abs(mPathCostClosed - mPathCostOpen);
  mIsSolved = ((mCostDifference < 1));
  return mIsSolved;
};


void Maze::resetToEmptyMaze() {
  for (int i = 0; i < NUMCELLS; i++) {
    mCost[i] = UINT16_MAX;
    mDirection[i] = NORTH;
    mWalls[i] = 0;
  }
  for (int i = 0; i < MAZEWIDTH; i++) {
    setWall(i, WEST);
    setWall(MAZEWIDTH * (MAZEWIDTH - 1) + i, EAST);
    setWall(i * MAZEWIDTH, SOUTH);
    setWall(MAZEWIDTH * i + MAZEWIDTH - 1, NORTH);
  }
  setWall(0, EAST);
  clearWall(0, NORTH);
  mWalls[0] |= VISITED;
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
      mWalls[cell] |= CHECKED_NORTH + WALLNORTH;
      cell = cellNorth(cell);
      mWalls[cell] |= CHECKED_SOUTH + WALLSOUTH;
      break;
    case EAST:
      mWalls[cell] |= CHECKED_EAST + WALLEAST;
      cell = cellEast(cell);
      mWalls[cell] |= CHECKED_WEST + WALLWEST;
      break;
    case SOUTH:
      mWalls[cell] |= CHECKED_SOUTH + WALLSOUTH;
      cell = cellSouth(cell);
      mWalls[cell] |= CHECKED_NORTH + WALLNORTH;
      break;
    case WEST:
      mWalls[cell] |= CHECKED_WEST + WALLWEST;
      cell = cellWest(cell);
      mWalls[cell] |= CHECKED_EAST + WALLEAST;
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
      mWalls[cell] &= ~WALLNORTHMASK;
      mWalls[cell] |= CHECKED_NORTH;
      cell = cellNorth(cell);
      mWalls[cell] &= ~WALLSOUTHMASK;
      mWalls[cell] |= CHECKED_SOUTH;
      break;
    case EAST:
      mWalls[cell] &= ~WALLEASTMASK;
      mWalls[cell] |= CHECKED_EAST;
      cell = cellEast(cell);
      mWalls[cell] &= ~WALLWESTMASK;
      mWalls[cell] |= CHECKED_WEST;
      break;
    case SOUTH:
      mWalls[cell] &= ~WALLSOUTHMASK;
      mWalls[cell] |= CHECKED_SOUTH;
      cell = cellSouth(cell);
      mWalls[cell] &= ~WALLNORTHMASK;
      mWalls[cell] |= CHECKED_NORTH;
      break;
    case WEST:
      mWalls[cell] &= ~WALLWESTMASK;
      mWalls[cell] |= CHECKED_WEST;
      cell = cellWest(cell);
      mWalls[cell] &= ~WALLEASTMASK;
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
  if (wallData & 0x01){
    setWall(cell,NORTH);
  } else {
    clearWall(cell,NORTH);
  }
  if (wallData & 0x02){
    setWall(cell,EAST);
  } else {
    clearWall(cell,EAST);
  }
  if (wallData & 0x04){
    setWall(cell,SOUTH);
  } else {
    clearWall(cell,SOUTH);
  }
  if (wallData & 0x08){
    setWall(cell,WEST);
  } else {
    clearWall(cell,WEST);
  }
}

/*
 * Updates the map by adding walls
 * Used when exploring only.
 * Will not remove a wall
 */
void Maze::updateMap(uint16_t cell, uint8_t wallData) {
  if (wallData & 0x01){
    setWall(cell,NORTH);
  }
  if (wallData & 0x02){
    setWall(cell,EAST);
  }
  if (wallData & 0x04){
    setWall(cell,SOUTH);
  }
  if (wallData & 0x08){
    setWall(cell,WEST);
  }
}



/*
 * Distance is returned based upon the setting of the wall flag.
 * No account is taken of the 'wall seen' flag.
 */
uint16_t Maze::costNorth(uint16_t cell) {
  if (hasWall(cell,NORTH)) {
    return UNREACHABLE;
  }
  cell = cellNorth(cell);
  return mCost[cell];
}

uint16_t Maze::costEast(uint16_t cell) {
  if (hasWall(cell,EAST)) {
    return UNREACHABLE;
  }
  cell = cellEast(cell);
  return mCost[cell];
}

uint16_t Maze::costSouth(uint16_t cell) {
  if (hasWall(cell,SOUTH)) {
    return UNREACHABLE;
  }
  cell = cellSouth(cell);
  return mCost[cell];
}

uint16_t Maze::costWest(uint16_t cell) {
  if (hasWall(cell,WEST)) {
    return UNREACHABLE;
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
      result =  UNREACHABLE;
  }
  return result;
}


uint16_t Maze::smallestNeighbourDirection(uint16_t cell, uint8_t heading) {
  uint16_t direction;
  int16_t distance;
  int16_t smallest;
  // assume it is ahead
  direction = heading;
  smallest = cost(cell, direction);
  // now look right
  heading = (heading + 1) & 0x03;
  distance = cost(cell, heading);
  if (distance < smallest) {
    smallest = distance;
    direction = heading;
  }
  // then look left
  heading = (heading + 2) & 0x03;
  distance = cost(cell, heading);
  if (distance < smallest) {
    smallest = distance;
    direction = heading;
  }
  // it should not be behind but ..
  heading = (heading + 3) & 0x03;
  distance = cost(cell, heading);
  if (distance < smallest) {
    direction = heading;
  }
  return direction;
}

void Maze::setUnknowns(void) {
  for (uint16_t i = 0; i < NUMCELLS; i++) {
    mWalls[i] |= (((~mWalls[i]) & VISITED) >> 1);
  }
}

void Maze::clearUnknowns(void) {
  for (uint16_t i = 0; i < NUMCELLS; i++) {
    mWalls[i] &= ~(((~mWalls[i]) & VISITED) >> 1);
  }
}

uint16_t Maze::recalculateGoal() {
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
      setGoal(newGoal);
      break;
    case 2:
      setGoal(newGoal);
      break;
    case 3:
      setGoal(newGoal);
      break;
    default:
      break;
  }
  setGoal(newGoal);

  return entranceCount;
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
uint16_t  Maze::runLengthFlood(uint16_t goal) {
  openList.clear();
  // set every cell as unexamined
  for (uint16_t i = 0; i < NUMCELLS; i++) {
    mCost[i] = UNREACHABLE;
  }
  // except the goal
  mCost[goal] = 0;
  mDirection[goal] = NORTH;
  //TODO: Guard against a closed-in goal
  if (hasExit(goal, NORTH)) {
    int nextCell = cellNorth(goal);
    openList.push(nextCell, 0,'F',0);
    mDirection[nextCell] = NORTH;
    mCost[nextCell] = costTable[1];
    mDirection[goal] = NORTH;
  }
  if (hasExit(goal, EAST)) {
    int nextCell = cellEast(goal);
    openList.push(nextCell, 0,'F',0);
    mDirection[nextCell] = EAST;
    mCost[nextCell] = costTable[1];
    mDirection[goal] = EAST;
  }
  if (hasExit(goal, WEST)) {
    int nextCell = cellWest(goal);
    openList.push(nextCell, 0,'F',0);
    mDirection[nextCell] = WEST;
    mCost[nextCell] = costTable[1];
    mDirection[goal] = WEST;
  }
  if (hasExit(goal, SOUTH)) {
    int nextCell = cellSouth(goal);
    openList.push(nextCell, 0,'F',0);
    mDirection[nextCell] = SOUTH;
    mCost[nextCell] = costTable[1];
    mDirection[goal] = SOUTH;
  }
  // each (accessible) cell will be processed only once
  int nextCost = 0;
  while (!openList.empty()) {
    FloodInfo info = openList.smallest();
    uint16_t here = info.cell;
    int headingHere = mDirection[here];
    int nextHeading = headingHere;
    uint8_t runLength = info.runLength ;
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
        case 'F': // on a straight
          runLength += 1;
          nextCost = mCost[here] + costTable[runLength];
          break;
      }
      if (mCost[nextCell] == UNREACHABLE) {
        openList.push(nextCell, nextCost, 'F', runLength);
        mDirection[nextCell] = nextHeading;
        mCost[nextCell] = nextCost;
      }
    };

    //---------------try left
    nextHeading = leftOf(headingHere);
    nextCell = neighbour(here, nextHeading);
    if (hasExit(here, nextHeading)) {
      switch (lastTurn) {
        case 'F': // left turn into possible diagonal
          runLength = 1;
          nextCost = mCost[here] + (costTable[runLength] * 3) / 4;
          break;
        case 'L': // 180 turn?
          runLength = 1;
          nextCost = mCost[here] + (costTable[runLength] * 3) / 2;
          break;
        case 'R': // on a diagonal
          runLength += 1;
          nextCost = mCost[here] + (costTable[runLength] * 7) / 10;
          break;

      }
      if (mCost[nextCell] == UNREACHABLE) {
        openList.push(nextCell, nextCost, 'L', runLength);
        mDirection[nextCell] = nextHeading;
        mCost[nextCell] = nextCost;
      }
    }
    //---------------try right
    nextHeading = rightOf(headingHere);
    nextCell = neighbour(here, nextHeading);
    if (hasExit(here, nextHeading)) {
      switch (lastTurn) {
        case 'F': // left turn into possible diagonal
          runLength = 1;
          nextCost = mCost[here] + (costTable[runLength] * 3) / 4;
          break;
        case 'R': // 180 turn?
          runLength = 1;
          nextCost = mCost[here] + (costTable[runLength] * 3) / 2;
          break;
        case 'L': // on a diagonal
          runLength += 1;
          nextCost = mCost[here] + (costTable[runLength] * 7) / 10;
          break;

      }
      if (mCost[nextCell] == UNREACHABLE) {
        openList.push(nextCell, nextCost, 'R', runLength);
        mDirection[nextCell] = nextHeading;
        mCost[nextCell] = nextCost;
      }
    }
  }
  for (int i = 0; i < NUMCELLS; i++) {
    mDirection[i] = (smallestNeighbourDirection(i));
  }
  return mCost[0];
}

void Maze::setGoal(uint16_t goal) {
  mGoal = goal;
}

uint16_t Maze::goal() {
  return mGoal;
}

uint16_t Maze::home() {
  return 0;
}

uint16_t Maze::cellNorth(uint16_t cell) {
  cell = (uint16_t)(cell + 1);
  if (cell >= NUMCELLS) {
    cell -= NUMCELLS;
  }
  return cell;
}

uint16_t Maze::cellEast(uint16_t cell) {
  cell = (uint16_t)(cell + MAZEWIDTH);
  if (cell >= NUMCELLS) {
    cell -= NUMCELLS;
  }
  return cell;
}

uint16_t Maze::cellSouth(uint16_t cell) {
  cell = (uint16_t)(cell + NUMCELLS - 1);
  if (cell >= NUMCELLS) {
    cell -= NUMCELLS;
  }
  return cell;
}

uint16_t Maze::cellWest(uint16_t cell) {
  cell = (uint16_t)(cell + NUMCELLS - MAZEWIDTH);
  if (cell >= NUMCELLS) {
    cell -= NUMCELLS;
  }
  return cell;
}

uint16_t Maze::neighbour(uint16_t cell, uint16_t direction) {
  uint16_t neighbour;
  switch (direction) {
    case NORTH:
      neighbour =  cellNorth(cell);
      break;
    case EAST:
      neighbour =  cellEast(cell);
      break;
    case SOUTH:
      neighbour =  cellSouth(cell);
      break;
    case WEST:
      neighbour =  cellWest(cell);
      break;
    default:
      neighbour =  UINT16_MAX;
  }
  return neighbour;
}

bool Maze::isKnownWall(uint16_t cell, uint8_t direction) {
  return (mWalls[cell] & (WALL_KNOWN << (2 * direction))) != 0;
}

bool Maze::hasExit(uint16_t cell, uint8_t direction) {
  int result = 0;
  switch (direction) {
    case NORTH:
      result = (mWalls[cell] & WALLNORTH) == 0 ;
      break;
    case EAST:
      result = (mWalls[cell] & WALLEAST) == 0;
      break;
    case SOUTH:
      result = (mWalls[cell] & WALLSOUTH) == 0;
      break;
    case WEST:
      result = (mWalls[cell] & WALLWEST) == 0;
      break;
    default:
      result =  0;
  }
  return result;
}

bool Maze::hasWall(uint16_t cell, uint8_t direction) {
  return !hasExit(cell,direction);
}

uint8_t Maze::rightOf(uint8_t direction) {
  return (direction + 1) % 4;
}

uint8_t Maze::leftOf(uint8_t direction) {
  return (direction + 3) % 4;
}

uint8_t Maze::walls(uint16_t cell) {
  uint8_t wallData = mWalls[cell];
  return (uint8_t)((wallData & 1) + ((wallData >> 1) & 2) + ((wallData >> 2) & 4) + ((wallData >> 3) & 8));;
}

uint16_t Maze::cost(uint16_t cell) {
  return mCost[cell];
}


uint8_t Maze::direction(uint16_t cell) {
  return  mDirection[cell];
}


bool Maze::isSolved(void) {
  return mIsSolved;
}

bool Maze::isVisited(uint16_t cell) {
  return ((mWalls[cell] & VISITED) == VISITED);
}

int16_t Maze::costDifference(void) {
  return mCostDifference;
}


uint8_t Maze::behind(uint8_t direction) {
  return (direction +2 ) % 4;
}

void Maze::setDirection(uint16_t cell, uint8_t direction) {
  assert(direction == NORTH || direction == EAST || direction == SOUTH || direction == WEST);
  mDirection[cell] = direction;
}

void Maze::setCost(uint16_t cell, uint16_t cost) {
   mCost[cell] = cost;
}

uint16_t Maze::numCells() {
  return NUMCELLS;
}

uint16_t Maze::width() {
  return MAZEWIDTH;
}
