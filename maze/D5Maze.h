//
// Created by Peter Harrison on 26/05/2017.
//

#ifndef MAZE_D5MAZE_H
#define MAZE_D5MAZE_H

#include "mazeconstants.h"
#include "priorityqueue.h"
#include <stdint.h>

class D5Maze{
public:
enum PrintStyle {PRINT_AS_CDECL, PRINT_WITH_COSTS, PRINT_WITH_DIRS, PRINT_WITH_DIRS_IF_VISITED, PRINT_WALLS_ONLY};
  D5Maze();

inline void setGoal(uint16_t goal) {
  _goal = goal;
}

inline uint16_t goal() {
  return _goal;
}


inline uint16_t cellNorth(uint16_t cell) {
  cell = (uint16_t)(cell + 1);
  if (cell >= NUMCELLS) {
    cell -= NUMCELLS;
  }
  return cell;
}

inline uint16_t cellEast(uint16_t cell) {
  cell = (uint16_t)(cell + MAZEWIDTH);
  if (cell >= NUMCELLS) {
    cell -= NUMCELLS;
  }
  return cell;
}

inline uint16_t cellSouth(uint16_t cell) {
  cell = (uint16_t)(cell + NUMCELLS - 1);
  if (cell >= NUMCELLS) {
    cell -= NUMCELLS;
  }
  return cell;
}

inline uint16_t cellWest(uint16_t cell) {
  cell = (uint16_t)(cell + NUMCELLS - MAZEWIDTH);
  if (cell >= NUMCELLS) {
    cell -= NUMCELLS;
  }
  return cell;
}


inline bool isKnownWall(uint8_t wallData, uint8_t heading) {
  return (wallData & (WALL_KNOWN << (2 * heading))) != 0;
}


inline int hasExit(int cell, int direction) {
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


inline int rightOf(int direction) {
  int result;
  switch (direction) {
    case NORTH:
      result =  EAST;
      break;
    case EAST:
      result =  SOUTH;
      break;
    case SOUTH:
      result =  WEST;
      break;
    case WEST:
      result =  NORTH;
      break;
    default:
      result =  direction;
  }
  return result;
}


inline int leftOf(int direction) {
  int result;
  switch (direction) {
    case NORTH:
      result =  WEST;
      break;
    case EAST:
      result =  NORTH;
      break;
    case SOUTH:
      result =  EAST;
      break;
    case WEST:
      result =  SOUTH;
      break;
    default:
      result =  direction;
  }
  return result;
}

// return the state of the walls at a given cell.
inline uint8_t walls(uint16_t cell) {
  return mWalls[cell];
}

inline uint8_t walls(uint16_t x, uint16_t y) {
  return mWalls[x * MAZEWIDTH + y];
}

// return the distance data
inline int16_t cost(uint16_t cell) {
  return mCost[cell];
}
inline int16_t cost(uint16_t x, uint16_t y) {
  return mCost[x * MAZEWIDTH + y];
}
// return the heading data
inline uint8_t heading(uint16_t cell) {
  return  mHeading[cell];
}
inline uint8_t heading(uint16_t x, uint16_t y) {
  return mHeading[x * MAZEWIDTH + y];
}

inline bool isSolved(void) {
  return _isSolved;
}

inline bool isVisited(uint16_t cell) {
  return ((mWalls[cell] & VISITED) == VISITED);
}

inline bool isVisited(uint16_t x, uint16_t y) {
  return ((mWalls[x * MAZEWIDTH + y] & VISITED) == VISITED);
}


inline int16_t costDifference(void) {
  return _costDifference;
}

inline bool goalFound(void) {
  return _goalFound;
}

inline uint8_t toFileFormat(uint8_t wallData) {
  return (uint8_t)((wallData & 1) + ((wallData >> 1) & 2) + ((wallData >> 2) & 4) + ((wallData >> 3) & 8));
}

void resetData(void);

// set maze to empty except start and edges
void clearMaze(void);

// modify a single wall in a cell. Will not remove existing data
void setWall(uint16_t cell, uint8_t wall);
void clearWall(uint16_t cell, uint8_t wall);


// adds all walls for a cell
// mWalls should be a four bit quantity as stored in a .maz file
void updateWalls(uint16_t cell, uint8_t mWalls);

uint16_t neighbour(uint16_t cell, uint16_t heading);

void setUnknownsAsWalls(void);
void setUnknownsAsClear(void);


int16_t  flood(uint16_t goal, floodMode mode);
int runLengthFlood(int goal);
int16_t distanceNorth(uint16_t cell);
int16_t distanceEast(uint16_t cell);
int16_t distanceSouth(uint16_t cell);
int16_t distanceWest(uint16_t cell);
int16_t getDistance(uint16_t cell, uint16_t heading);
uint16_t smallestNeighbourDirection(uint16_t cell, uint8_t heading = NORTH);
void print(PrintStyle style);

  uint16_t mCost[NUMCELLS];
uint8_t mHeading[NUMCELLS];

bool testForSolution(void);


uint16_t recalculateGoal();

protected:
PriorityQueue openList;
uint16_t _goal;
uint8_t * savedWalls;
uint8_t mWalls[NUMCELLS] ;
int16_t _costWithUnknownsAsWalls;
int16_t _costWithUnknownsAsClear;
int16_t _costDifference;
bool _isSolved;
bool _goalFound;
};

#endif //MAZE_D5MAZE_H
