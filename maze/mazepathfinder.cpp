/*
 * File:   mazepathfinder.c
 * Author: peterharrison
 *
 * Created on 16 February 2016, 14:55
 */

#include "maze.h"
#include "mazepathfinder.h"


/*
 * Generate a path from cost data following a flood;
 * The method simply walks downhill from start to target marking the
 * direction data on its way.
 * All cells not on the path will have INVALID direction data
 * Returns the length of the path in cells
 *
 * No attempt is made to verify that a valid path exists
 */


//TODO:  add another 'direction' that is STOP.
// assumes the maze to have been flooded
int IsolatePath (location_t start, location_t target)
{
  int pathLength = 0;
  location_t here = start;
  if (Cost (here) == MAX_COST) {
    SetDirection (here, INVALID);
    return -1;  // this is an error condition. Not well handled.
  }
  if (Cost (here) == 0) {
    SetDirection (here, INVALID);
    return 0;  // this is an error condition. Not well handled.
  }
  MazeResetDirections();
  while (! (here.row == target.row && here.col == target.col)) {
    direction_t direction;
    direction = SmallestNeighbourDirection (here);
    SetDirection (here, direction);
    here = Neighbour (here, direction);
    pathLength++;
    if (pathLength >= 250) {
      break;
    }
  }
  return pathLength;
}