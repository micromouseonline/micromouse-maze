/*
 * File:   mazesearcher.c
 * Author: peterharrison
 *
 * Created on 17 February 2016, 21:31
 */
#include <assert.h>
#include <stdio.h>
#include "maze.h"
#include "mazeflooder.h"
#include "mazeprinter.h"
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

