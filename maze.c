/*
 * File:   maze.c
 * Author: peterharrison
 *
 * Created on 08 February 2016, 00:09
 */

#include <stdint.h>
#include "maze.h"



/* bit masks for the wall data */
#define WALL       ((walls_t)0x01)
#define NORTH_WALL (WALL << NORTH)
#define EAST_WALL  (WALL << EAST)
#define SOUTH_WALL (WALL << SOUTH)
#define WEST_WALL  (WALL << WEST)
#define ALL_WALLS (NORTH_WALL + EAST_WALL + SOUTH_WALL + WEST_WALL)
#define WALL_SEEN  ((walls_t)0x10)
#define NORTH_SEEN (WALL_SEEN << NORTH)
#define EAST_SEEN  (WALL_SEEN << EAST)
#define SOUTH_SEEN (WALL_SEEN << SOUTH)
#define WEST_SEEN  (WALL_SEEN << WEST)

#define ALL_SEEN (NORTH_SEEN + EAST_SEEN + SOUTH_SEEN + WEST_SEEN)
#define VISITED ALL_SEEN


static walls_t _walls[MAZE_COLS][MAZE_ROWS];
static cost_t _cost[MAZE_COLS][MAZE_ROWS];
static direction_t _direction[MAZE_COLS][MAZE_ROWS];

/* initialise to a known value*/
static location_t _goal = {7, 7};
static location_t _home = {0, 0};

//=======================================
// LOCATION
//=======================================

location_t DefaultGoal(void){
  location_t goal = {7,7};
  return goal;
}

void SetGoal (location_t location)
{
  _goal = location;
};

location_t Goal (void)
{
  return _goal;
};

location_t Home (void)
{
  return _home;
};


/*
 * Boundaries wrap around in a cylindrical fashion
 */
location_t Neighbour (location_t location, direction_t direction)
{
  switch (direction) {
    case NORTH:
      location.row = location.row + 1;
      if (location.row >= MazeHeight()) {
        location.row = 0;
      }
      break;
    case EAST:
      location.col = location.col + 1;
      if (location.col >= MazeWidth()) {
        location.col = 0;
      }
      break;
    case SOUTH:
      location.row = location.row - 1;
      if (location.row < 0) {
        location.row = MazeHeight() - 1;
      }
      break;
    case WEST:
      location.col = location.col - 1;
      if (location.col < 0) {
        location.col = MazeWidth() - 1;
      }
      break;
    default:
      // do nothing
      break;
  }
  return location;
};

bool IsGoal (location_t location)
{
  return (location.row == _goal.row && location.col == _goal.col);
};

bool IsHome (location_t location)
{
  return (location.row == _home.row && location.col == _home.col);
};


//=======================================
// DIRECTION
//=======================================
void MazeClearDirectionData (void)
{
  location_t loc;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      SetDirection (loc, INVALID);
    }
  }
}

void SetDirection (location_t location, direction_t direction)
{
  _direction[location.row][location.col] = direction;
};

direction_t MazeGetDirection (location_t location)
{
  return _direction[location.row][location.col];
};

/* handy utilities for directions */
direction_t LeftFrom (direction_t direction)
{
  return (direction + DIRECTION_COUNT - 1) % DIRECTION_COUNT;
};

direction_t RightFrom (direction_t direction)
{
  return (direction + 1) % DIRECTION_COUNT;
};

direction_t Behind (direction_t direction)
{
  return (direction + 2) % DIRECTION_COUNT;
};


bool HasExit (location_t location, direction_t direction)
{
  walls_t walls = MazeGetWalls (location);
  return !HaveWall (walls, direction);
}

/* ========== manipulating the walls ==============*/
bool WallIsSeen (walls_t walls, direction_t direction)
{
  return ( (walls & (WALL_SEEN << direction)) != 0);;
};

bool HaveWall (walls_t walls, direction_t direction)
{
  return ( (walls & (WALL << direction)) != 0);
};

/* setting and clearing always sets the seen bits */
void WallSet (walls_t * walls, direction_t direction)
{
  *walls |= (WALL << direction);
  *walls |= (WALL_SEEN << direction);
};

void WallClear (walls_t * walls, direction_t direction)
{
  *walls &= ~ (WALL << direction);
  *walls |= (WALL_SEEN << direction);
};

walls_t WallsNone (void)
{
  //return an initialised wall structure
  walls_t walls;
  walls &= ~ALL_WALLS;
  walls &= ~ALL_SEEN;
  return walls;
}




//=======================================
// COSTS
//=======================================
cost_t Cost (location_t location)
{
  return _cost[location.row][location.col];
};

void SetCost (location_t location, cost_t cost)
{
  _cost[location.row][location.col] = cost;
};


//=======================================
// MAZE
//=======================================



uint8_t MazeWidth (void)
{
  return MAZE_COLS;
}

uint8_t MazeHeight (void)
{
  return MAZE_ROWS;
}


/*
 * clear the costs and directions
 * set the walls to the outside and start cell walls only
 */
void MazeResetData (void)
{
  location_t loc;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      _walls[loc.row][loc.col] = 0;
      _cost[loc.row][loc.col] = 0;
    }
  }
}


/* set a single wall - looks after neighbours - set seen*/
void MazeSetWall (location_t location, direction_t direction)
{
  WallSet (&_walls[location.row][location.col], direction);
  location = Neighbour (location, direction);
  WallSet (&_walls[location.row][location.col], Behind (direction));
}


/* set all four walls for a location - updates neighbours - set seen*/
void MazeUpdateFromWallData (location_t location, walls_t wallData)
{
  if (wallData & NORTH_WALL) {
    MazeSetWall (location, NORTH);
  } else {
    MazeClearWall (location, NORTH);
  }
  if (wallData & EAST_WALL) {
    MazeSetWall (location, EAST);
  } else {
    MazeClearWall (location, EAST);
  }
  if (wallData & SOUTH_WALL) {
    MazeSetWall (location, SOUTH);
  } else {
    MazeClearWall (location, SOUTH);
  }
  if (wallData & WEST_WALL) {
    MazeSetWall (location, WEST);
  } else {
    MazeClearWall (location, WEST);
  }
}

/* clear a single wall - looks after neighbours - set seen*/
void MazeClearWall (location_t location, direction_t direction)
{
  WallClear (&_walls[location.row][location.col], direction);
  location = Neighbour (location, direction);
  WallClear (&_walls[location.row][location.col], Behind (direction));
}

/* return all the walls for a given location */
walls_t MazeGetWalls (location_t location)
{
  return _walls[location.row][location.col];
}



