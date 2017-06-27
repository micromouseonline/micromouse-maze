/*
 * File:   mazepathfinder.h
 * Author: peterharrison
 *
 * Created on 16 February 2016, 14:55
 */

#ifndef MAZEPATHFINDER_H
#define MAZEPATHFINDER_H


/*
 * The PathFinder class examines a properly flooded maze and uses its data
 * to construct a path for the mouse to follow.
 *
 * A basic path is a simple character string. Each letter in the string
 * represents a command for the robot in a cell of the maze.
 *
 * PathString commands
 *  'B' : Begin path. Must be present. No motion. Robot initialisation.
 *  'F' : Move forward one cell.
 *  'R' : Turn right.
 *  'L' : Turn left.
 *  'S' : Stop moving. Robot centered in the cell.
 *  'X' : Explore. Robot centered in the cell, moving at explore speed
 *
 *
 *  A PathString can be converted into a series of mouse commands. Each command
 *  is a single byte representing more complex behaviour.
 *
 *  The simplest level effectively run length encodes the PathString and
 *  generates smooth turns for each 'L' or 'R' instruction.
 *
 *  The more complex version produces a set of instructions that will
 *  resulting a fast run using diagonals. This command list must obey a
 *  basic syntax as illustrated below.
 *
 *  Note that there must be a start command and one of the two finish commands.
 *  Every turn has a straight move before and after it. Straight moves are
 *  either orthogonal or diagonal.
 *
 *            ----------------------------------------------
 *          /                                                \
 *          \                                                /
 *   START-----ORTHO----SS90-----------------------------------------EXPLORE---
 *         \         \--SS180----/                       /     /  \--FINISH -/
 *         |          |                                  |     |
 *         |          |                                  |     |
 *         |          |            .--DD90--.            |     |
 *         |          |            \        /            |     |
 *         |          |\--SD45--------DIAG------DS45-----/     |
 *         |           \--SD135-/             \-DS135-/        |
 *         |                                                   |
 *         \--------------------------------------------------/
 *
 *
 *  The strings or command lists are created in buffers provided by the caller.
 *  Thus, the caller is responsible for managing the storage allocation and
 *  de-allocation. The Pathfinder will not create any objects that it does not
 *  then destroy.
 *
 *
 *  TODO: protection needs to stop PathFinder from overrunning callers memory.
 *
 */


/*
 * clear all the direction arrows except those along the least-cost path
 * from start to target.
 * Expects a flooded maze.
 * Returns without any action if the start cost is MAX_COST, indicating
 * there is no route to the goal
 * An unflooded maze will have undefined results - the function may not return.
 */

/* TODO: make this follow a path until there is no smaller neighbour */
//int IsolatePath (location_t start, location_t target);

class PathFinder {
 public:
  PathFinder();
  ~PathFinder();
 private:
};


#endif /* MAZEPATHFINDER_H */

