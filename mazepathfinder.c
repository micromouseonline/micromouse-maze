/*
 * File:   mazepathfinder.c
 * Author: peterharrison
 *
 * Created on 16 February 2016, 14:55
 */

#include "maze.h"
#include "mazeflooder.h"
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

int IsolatePath (location_t start, location_t target)
{
  int pathLength = 0;
  location_t here = start;
  direction_t direction;
  if (Cost (here) == MAX_COST) {
    return -1;  // this is an error condition. Not well handled.
  }
  MazeClearDirectionData();
  while (! (here.row == target.row && here.col == target.col)) {
    direction = SmallestNeighbourDirection (here);
    SetDirection (here, direction);
    here = Neighbour (here, direction);
    pathLength++;
  }
  pathLength++; // to get to the last cell;
  return pathLength;
}