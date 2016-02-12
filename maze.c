/*
 * File:   maze.c
 * Author: peterharrison
 *
 * Created on 08 February 2016, 00:09
 */

#include <stdint.h>
#include "maze.h"

static walls_t walls[MAZE_COLS][MAZE_ROWS];
static cost_t cost[MAZE_COLS][MAZE_ROWS];
static direction_t _direction[MAZE_COLS][MAZE_ROWS];

/* initialise to a known value*/
static location_t goal = {7, 8};
static location_t home = {0, 0};

//=======================================
// LOCATION
//=======================================

void MazeSetGoal (location_t location)
{
  goal = location;
};

location_t MazeGetGoal (void)
{
  return goal;
};

location_t MazeGetHome (void)
{
  return home;
};


/*
 * No attempt is made to deal with boundary overflows. THis is by design.
 */
location_t LocationGetNeighbour (location_t location, direction_t direction)
{
  switch (direction) {
    case NORTH:
      location.row = location.row + 1;
      break;
    case EAST:
      location.col = location.col + 1;
      break;
    case SOUTH:
      location.row = location.row - 1;
      break;
    case WEST:
      location.col = location.col - 1;
      break;
    default:
      // do nothing
      break;
  }
  return location;
};

bool LocationIsInGoal (location_t location)
{
  return (location.row == goal.row && location.col == goal.col);
};

bool LocationIsInHome (location_t location)
{
  return (location.row == 0 && location.col == 0);
};


//=======================================
// DIRECTION
//=======================================

void MazeSetDirection (location_t location, direction_t direction)
{

};

direction_t MazeGetDirection (location_t location)
{
  return INVALID;
};

/* handy utilities for directions */
direction_t DirectionGetLeftFrom (direction_t direction)
{
  return INVALID;
};

direction_t DirectionGetRightFrom (direction_t direction)
{
  return INVALID;
};

direction_t DirectionGetBehindFrom (direction_t direction)
{
  return INVALID;
};

