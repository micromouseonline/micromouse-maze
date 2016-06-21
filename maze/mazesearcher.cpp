/*
 * File:   mazesearcher.c
 * Author: peterharrison
 *
 * Created on 17 February 2016, 21:31
 */
#include <assert.h>
#include "maze.h"
#include "mazereader.h"
#include "mazeflooder.h"
#include "mazesearcher.h"

static location_t mousePosition;
static direction_t mouseHeading;

void MouseInit (void)
{
  MouseSetPosition (Location (0, 0));
  MouseSetHeading (NORTH);
}


location_t MousePosition (void)
{
  return mousePosition;
}


direction_t MouseHeading (void)
{
  return mouseHeading;
}

/* note: no error checking is done */
/* an assert here would be good */
void MouseSetPosition (location_t location)
{
  assert (location.row >= 0);
  assert (location.col >= 0);
  assert (location.row < MAZE_ROWS);
  assert (location.row < MAZE_COLS);
  mousePosition = location;
}

void MouseSetHeading (direction_t direction)
{
  mouseHeading = direction;
}


/* move the mouse by one cell in the direction given by heading */
/* no error checking is done for walls or borders */
void MouseMove (void)
{
  MouseSetPosition (Neighbour (mousePosition, mouseHeading));
}

/* mouse should follow the direction pointers until it is at the goal */
void MouseRunTo (location_t target)
{
  int step = 0;
  while (! (MousePosition().row == target.row && MousePosition().col == target.col)) {
    direction_t direction = Direction (MousePosition());
    if (direction == INVALID) {
      break;
    }
    MouseSetHeading (direction);
    MouseMove();
    step ++;
    if (step > 256) {
      break;
    }
  }
}

/*
 * Perform a search from the mouse current location to the target location
 * uses a full flood after each step
 * Returns the number of steps needed to get to the target
 */
int MouseSearchToFullFlood (location_t target)
{

  int steps = 0;
  while (! (MousePosition().row == target.row && MousePosition().col == target.col)) {
    walls_t actualWalls = ReadWallSensors (MousePosition());
    UpdateCellFromWallData (MousePosition(), actualWalls);
    FloodMazeClassic (target);
    direction_t direction = Direction (MousePosition());
    if (direction == INVALID) {
      break;
    }
    MouseSetHeading (direction);
    MouseMove();
    steps++;
  }
  return steps;
}


int MouseSearchToModifiedFlood (location_t target)
{

  int steps = 0;
  FloodMazeClassic (target);	/* seed the costs before using modified flood */
  while (! (MousePosition().row == target.row && MousePosition().col == target.col)) {
    walls_t actualWalls = ReadWallSensors (MousePosition());
    UpdateCellFromWallData (MousePosition(), actualWalls);
    ModifiedFlood (MousePosition());
    direction_t direction = Direction (MousePosition());
    MouseSetHeading (direction);
    MouseMove();
    steps++;
    if (steps > 500) {
      break;
    }
  }
  return steps;
}


int MouseSearchToModifiedFloodAll (location_t target)
{

  int steps = 0;
  FloodMazeClassic (target);	/* seed the costs before using modified flood */
  while (! (MousePosition().row == target.row && MousePosition().col == target.col)) {
    walls_t actualWalls = ReadWallSensors (MousePosition());
    UpdateCellFromWallData (MousePosition(), actualWalls);
    ModifiedFloodAll (MousePosition());
    direction_t direction = Direction (MousePosition());
    MouseSetHeading (direction);
    MouseMove();
    steps++;
    if (steps > 500) {
      break;
    }
  }
  return steps;
}

