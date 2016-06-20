/*
 * File:   maze.c
 * Author: peterharrison
 *
 * Created on 08 February 2016, 00:09
 */

#include <stdint.h>
#include "maze.h"






static walls_t _walls[MAZE_COLS][MAZE_ROWS];
static cost_t _cost[MAZE_COLS][MAZE_ROWS];
static direction_t _direction[MAZE_COLS][MAZE_ROWS];

/* initialise to a known value*/
static location_t _defaultGoal = {7, 7};
static location_t _goal = {7, 7};
static location_t _home = {0, 0};

//=======================================
// LOCATION
//=======================================

location_t Location (uint8_t row, uint8_t col)
{
  location_t result;
  result.row = row;
  result.col = col;
  return result;
}


location_t DefaultGoal (void)
{
  return _defaultGoal;
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
  location_t result;
  result = location;
  switch (direction) {
    case NORTH:
      result.row = location.row + 1;
      if (result.row >= MazeHeight()) {
        result.row = 0;
      }
      break;
    case EAST:
      result.col = location.col + 1;
      if (result.col >= MazeWidth()) {
        result.col = 0;
      }
      break;
    case SOUTH:
      result.row = location.row - 1;
      if (result.row < 0) {
        result.row = MazeHeight() - 1;
      }
      break;
    case WEST:
      result.col = location.col - 1;
      if (result.col < 0) {
        result.col = MazeWidth() - 1;
      }
      break;
    default:
      ;// do nothing
      break;
  }
  return result;
};

bool IsGoal (location_t location)
{
  /*
   * for the classic contest we could also consider:
   * if (location.row < 7) return false;
   * if (location.row > 8) return false;
   * if (location.col < 7) return false;
   * if (location.col > 8) return false;
   * return true;
   */
  return (location.row == _goal.row && location.col == _goal.col);
};

bool IsHome (location_t location)
{
  return (location.row == _home.row && location.col == _home.col);
};


//=======================================
// DIRECTION
//=======================================
void MazeResetDirections (void)
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

direction_t Direction (location_t location)
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



/*
 * return the direction to neighbour with the smallest cost
 * There will always be one unless the cell has all walls.
 * That should not happen in normal maze and so no special care is taken
 * Only accessible neighbours are tested
 */

direction_t SmallestNeighbourDirection (location_t loc)
{
  direction_t result = NORTH;
  location_t neighbour;
  cost_t smallestCost;
  cost_t cost;

  smallestCost = MAX_COST;
  if (HasExit (loc, NORTH)) {
    neighbour = Neighbour (loc, NORTH);
    cost = Cost (neighbour);
    if (cost < smallestCost) {
      smallestCost = cost;
      result = NORTH;
    }
  }
  if (HasExit (loc, EAST)) {
    neighbour = Neighbour (loc, EAST);
    cost = Cost (neighbour);
    if (cost < smallestCost) {
      smallestCost = cost;
      result = EAST;
    }
  }
  if (HasExit (loc, SOUTH)) {
    neighbour = Neighbour (loc, SOUTH);
    cost = Cost (neighbour);
    if (cost < smallestCost) {
      smallestCost = cost;
      result = SOUTH;
    }
  }
  if (HasExit (loc, WEST)) {
    neighbour = Neighbour (loc, WEST);
    cost = Cost (neighbour);
    if (cost < smallestCost) {
      // there is no longe a need to remember the smallest cost
      result = WEST;
    }
  }
  return result;
}


bool HasExit (location_t location, direction_t direction)
{
  walls_t walls = Walls (location);
  return !WallExists (walls, direction);
}

/* ========== manipulating the walls ==============*/
bool WallIsSeen (walls_t walls, direction_t direction)
{
  return ( (walls & (WALL_SEEN << direction)) != 0);;
};

bool WallExists (walls_t walls, direction_t direction)
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

//return an initialised wall structure
walls_t WallsNone (void)
{
  walls_t walls = 0;
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


void MazeInit (void)
{
  MazeResetWalls();
  MazeResetCosts();
  MazeResetDirections();
  location_t loc;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    loc.col = 0;
    MazeAddWall (loc, WEST);
    loc.col = MAZE_COLS - 1;
    MazeAddWall (loc, EAST);
  }
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    loc.row = 0;
    MazeAddWall (loc, SOUTH);
    loc.row = MAZE_ROWS - 1;
    MazeAddWall (loc, NORTH);
  }
  loc.row = 0;
  loc.col = 0;
  MazeAddWall (loc, EAST);
}

/*
 * clear the costs and directions
 * set the walls to the outside and start cell walls only
 */
void MazeResetWalls (void)
{
  location_t loc;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      _walls[loc.row][loc.col] = EMPTY;
    }
  }
}


/*
 * clear the costs and directions
 * set the walls to the outside and start cell walls only
 */
void MazeResetCosts (void)
{
  location_t loc;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      _cost[loc.row][loc.col] = 0;
    }
  }
}


/* set a single wall - looks after neighbours - set seen*/
void MazeAddWall (location_t location, direction_t direction)
{
  WallSet (&_walls[location.row][location.col], direction);
  location = Neighbour (location, direction);
  WallSet (&_walls[location.row][location.col], Behind (direction));
}


/* set all four walls for a location - updates neighbours - set seen*/
void UpdateCellFromWallData (location_t location, walls_t wallData)
{
  if (wallData & NORTH_WALL) {
    MazeAddWall (location, NORTH);
  } else {
    MazeRemoveWall (location, NORTH);
  }
  if (wallData & EAST_WALL) {
    MazeAddWall (location, EAST);
  } else {
    MazeRemoveWall (location, EAST);
  }
  if (wallData & SOUTH_WALL) {
    MazeAddWall (location, SOUTH);
  } else {
    MazeRemoveWall (location, SOUTH);
  }
  if (wallData & WEST_WALL) {
    MazeAddWall (location, WEST);
  } else {
    MazeRemoveWall (location, WEST);
  }
}


/* clear a single wall - looks after neighbours - set seen*/
void MazeRemoveWall (location_t location, direction_t direction)
{
  WallClear (&_walls[location.row][location.col], direction);
  location = Neighbour (location, direction);
  WallClear (&_walls[location.row][location.col], Behind (direction));
}

/* return all the walls for a given location */
walls_t Walls (location_t location)
{
  return _walls[location.row][location.col];
}


bool Visited (location_t location)
{
  return (Walls (location) & VISITED) == VISITED;
}
