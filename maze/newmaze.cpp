//
// Created by Peter Harrison on 26/05/2017.
//

#include "mazedata.h"
#include "newmaze.h"
#include "mazeconstants.h"
#include <stdint.h>
/*
  maze.c
  common functions for manipulating the maze map
  and for creating the flooded route
 */
#include <stdio.h>
#include <stdint.h>

#define NOINIT

// allocate the maze to a known position in memory so that we can avoid
// resetting the contents at reset.
static uint8_t backupWalls[NUMCELLS] NOINIT;

char directionChar[] = "^>v<?";


/*
 * The runlength flood calculates costs based on the length of straights
 */
const int costTable[] =
    //                      {100, 22, 16, 12, 10, 9, 8, 7,
    //                         6, 6, 5, 5, 5, 5, 4, 4,
    //                         4, 4, 4, 4, 3, 3, 3, 3
    //                        };
    {100, 13, 11, 9, 8, 7, 6, 6, 5, 5, 5, 5, 5, 4, 4, 4, 4};




NewMaze::NewMaze() {
  _isSolved = false;
  _goalFound = false;
  savedWalls = backupWalls;
  resetData();
  testForSolution();
  setGoal(DEFAULT_GOAL);
};

bool NewMaze::testForSolution(void) { // takes less than 3ms
  //flood(theMaze.goal(), unknownsAreWalls);
  //flood(theMaze.goal(), unknownsAreClear);
  _costDifference = abs(_costWithUnknownsAsClear - _costWithUnknownsAsWalls);
  _goalFound = _costWithUnknownsAsWalls < UNREACHABLE;
  _isSolved = _goalFound && ((_costDifference < 1));
  return _isSolved;
};;


void NewMaze::clearMaze() {
  resetData();
}

void NewMaze::resetData() {
  for (int i = 0; i < NUMCELLS; i++) {
    mWalls[i] = 0;
    //  queue[i] = 0;
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
 * unconditionally adds a wall to the data.
 * over-writes whatever is there.
 * should only be used when setting up a maze.
 * To update the maze when running, use updateWalls(cell,wallData)
 */
void NewMaze::setWall(uint16_t cell, uint8_t heading) {
  switch (heading) {
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
 * unconditionally adds a wall to the data.
 * over-writes whatever is there.
 * should only be used when setting up a maze.
 * To update the maze when running, use updateWalls(cell,wallData)
 */
void NewMaze::clearWall(uint16_t cell, uint8_t heading) {
  switch (heading) {
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
 * and update that cell as well as its neighbors with
 * data for all four walls whether or not they are present
 * Effectively, it will also mark the current cell as
 * completely visited
 * Whenever an update is done, the maze gets saved to the backup array.
 */
void NewMaze::updateWalls(uint16_t cell, uint8_t newWalls) {
  //logInfo ("Update walls at 0x%02X with 0x%02X \n", cell, newWalls);
  uint8_t replacementWalls = newWalls;
  // first do the walls in this cell
  uint8_t existingWalls = mWalls[cell];
  if (isKnownWall(existingWalls, NORTH)) {
    replacementWalls &= ~(WALLNORTHMASK);  // remove them from the update
  }
  if (isKnownWall(existingWalls, SOUTH)) {
    replacementWalls &= ~(WALLSOUTHMASK);  // remove them from the update
  }
  if (isKnownWall(existingWalls, EAST)) {
    replacementWalls &= ~(WALLEASTMASK);  // remove them from the update
  }
  if (isKnownWall(existingWalls, WEST)) {
    replacementWalls &= ~(WALLWESTMASK);  // remove them from the update
  }
  existingWalls |= replacementWalls | VISITED;
  mWalls[cell] = existingWalls;
  //now do the neighbours in the same order of directions
  uint16_t nextCell;
  nextCell = cellNorth(cell);
  if (!isKnownWall(mWalls[nextCell], SOUTH)) {
    replacementWalls = ((newWalls << 4) & WALLSOUTHMASK) | CHECKED_SOUTH;
    mWalls[nextCell] |= replacementWalls;
  }
  nextCell = cellSouth(cell);
  if (!isKnownWall(mWalls[nextCell], NORTH)) {
    replacementWalls = ((newWalls >> 4) & WALLNORTHMASK) | CHECKED_NORTH;
    mWalls[nextCell] |= replacementWalls;
  }
  nextCell = cellWest(cell);
  if (!isKnownWall(mWalls[nextCell], EAST)) {
    replacementWalls = ((newWalls >> 4) & WALLEASTMASK) | CHECKED_EAST;
    mWalls[nextCell] |= replacementWalls;
  }
  nextCell = cellEast(cell);
  if (!isKnownWall(mWalls[nextCell], WEST)) {
    replacementWalls = ((newWalls << 4) & WALLWESTMASK) | CHECKED_WEST;
    mWalls[nextCell] |= replacementWalls;
  }
}



/*
 * Distance is returned based upon the setting of the wall flag.
 * No account is taken of the 'wall seen' flag.
 */
int16_t NewMaze::distanceNorth(uint16_t cell) {
  if (mWalls[cell] & WALLNORTH) {
    return UNREACHABLE;
  }
  cell = cellNorth(cell);
  return mCost[cell];
}

int16_t NewMaze::distanceEast(uint16_t cell) {
  if (walls(cell) & WALLEAST) {
    return UNREACHABLE;
  }
  cell = cellEast(cell);
  return mCost[cell];
}

int16_t NewMaze::distanceSouth(uint16_t cell) {
  if (walls(cell) & WALLSOUTH) {
    return UNREACHABLE;
  }
  cell = cellSouth(cell);
  return mCost[cell];
}

int16_t NewMaze::distanceWest(uint16_t cell) {
  if (walls(cell) & WALLWEST) {
    return UNREACHABLE;
  }
  cell = cellWest(cell);
  return mCost[cell];
}

int16_t NewMaze::getDistance(uint16_t cell, uint16_t direction) {
  int16_t result;
  switch (direction) {
    case NORTH:
      result =  distanceNorth(cell);
      break;
    case EAST:
      result =  distanceEast(cell);
      break;
    case SOUTH:
      result =  distanceSouth(cell);
      break;
    case WEST:
      result =  distanceWest(cell);
      break;
    default:
      result =  UNREACHABLE;
  }
  return result;
}

uint16_t NewMaze::smallestNeighbourDirection(uint16_t cell, uint8_t heading) {
  uint16_t direction;
  int16_t distance;
  int16_t smallest;
  // assume it is ahead
  direction = heading;
  smallest = getDistance(cell, direction);
  // now look right
  heading = (heading + 1) & 0x03;
  distance = getDistance(cell, heading);
  if (distance < smallest) {
    smallest = distance;
    direction = heading;
  }
  // then look left
  heading = (heading + 2) & 0x03;
  distance = getDistance(cell, heading);
  if (distance < smallest) {
    smallest = distance;
    direction = heading;
  }
  // it should not be behind but ..
  heading = (heading + 3) & 0x03;
  distance = getDistance(cell, heading);
  if (distance < smallest) {
    direction = heading;
  }
  return direction;
}

void NewMaze::setUnknownsAsWalls(void) {
  for (uint16_t i = 0; i < NUMCELLS; i++) {
    mWalls[i] |= (((~mWalls[i]) & VISITED) >> 1);
  }
}

void NewMaze::setUnknownsAsClear(void) {
  for (uint16_t i = 0; i < NUMCELLS; i++) {
    mWalls[i] &= ~(((~mWalls[i]) & VISITED) >> 1);
  }
}


uint16_t NewMaze::neighbour(uint16_t cell, uint16_t heading) {
  uint16_t neighbour;
  switch (heading) {
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

uint16_t NewMaze::recalculateGoal() {
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

int16_t NewMaze::flood(uint16_t goal, floodMode mode) {
  int16_t cost;
  if (mode == unknownsAreWalls) {
    setUnknownsAsWalls();
    cost = runLengthFlood(goal);
    //logInfo ("Flooding to: 0x%02X unknowns set, cost = %d.\n", goal, cost);
    _costWithUnknownsAsWalls = cost;
  } else {
    setUnknownsAsClear();
    cost = runLengthFlood(goal);
    //logInfo ("Flooding to: 0x%02X unknowns clear, cost = %d.\n", goal, cost);
    _costWithUnknownsAsClear = cost;
  }
  setUnknownsAsClear();
  return cost;
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
int NewMaze::runLengthFlood(int goal) {
  openList.clear();
  // set every cell as unexamined
  for (uint16_t i = 0; i < NUMCELLS; i++) {
    mCost[i] = UNREACHABLE;
  }
  // except the goal
  mCost[goal] = 0;
  mHeading[goal] = NORTH;
  //TODO: Guard against a closed-in goal
  if (hasExit(goal, NORTH)) {
    int nextCell = cellNorth(goal);
    openList.push(nextCell, 0);
    mHeading[nextCell] = NORTH;
    mCost[nextCell] = costTable[1];
    mHeading[goal] = NORTH;
  }
  if (hasExit(goal, EAST)) {
    int nextCell = cellEast(goal);
    openList.push(nextCell, 0);
    mHeading[nextCell] = EAST;
    mCost[nextCell] = costTable[1];
    mHeading[goal] = EAST;
  }
  if (hasExit(goal, WEST)) {
    int nextCell = cellWest(goal);
    openList.push(nextCell, 0);
    mHeading[nextCell] = WEST;
    mCost[nextCell] = costTable[1];
    mHeading[goal] = WEST;
  }
  if (hasExit(goal, SOUTH)) {
    int nextCell = cellSouth(goal);
    openList.push(nextCell, 0);
    mHeading[nextCell] = SOUTH;
    mCost[nextCell] = costTable[1];
    mHeading[goal] = SOUTH;
  }
  // each (accessible) cell will be processed only once
  int nextCost = 0;
  while (openList.hasItems()) {
    FloodInfo info = openList.smallest();
    uint16_t here = info.cell;
    int headingHere = mHeading[here];
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
        mHeading[nextCell] = nextHeading;
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
        mHeading[nextCell] = nextHeading;
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
        mHeading[nextCell] = nextHeading;
        mCost[nextCell] = nextCost;
      }
    }
  }
  for (int i = 0; i < NUMCELLS; i++) {
    mHeading[i] = (smallestNeighbourDirection(i));
  }
  return mCost[0];
};
