/************************************************************************
* File:   mazepathfinder.h
* Author: peterharrison
*
* Created on 16 February 2016, 14:55
*
* Copyright (C) 2017 by Peter Harrison. www.micromouseonline.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without l> imitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
************************************************************************/


#ifndef MAZEPATHFINDER_H
#define MAZEPATHFINDER_H

#include <stdint.h>
#include "maze.h"
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
 *  The basic PathString is stored in a buffer held by the PathFinder class so
 *  that it is available to generate command lists of different kinds.
 *
 *  The command lists are created in buffers provided by the caller.
 *
 *  Thus, the caller is responsible for managing the storage allocation and
 *  de-allocation. The Pathfinder will not create any objects that it does not
 *  then destroy.
 *
 *  The Pathfinder assumes it may be used on a half size maze so the maximum path
 *  length is large.
 *
 *  In the unlikely event it became necessary to save memory or accommodate
 *  different size mazes/paths, it may be appropriate to subclass a simpler
 *  version intended only for the classic contest
 *
 */


#include "maze.h"
#include "commandnames.h"

#define MAX_PATH_LENGTH 1022

class PathFinder {
public:

  PathFinder();
  ~PathFinder();
  char * path();
  ///  Create a simple pathstring representing the route from start to finsh in the maze
  void generateSafePath(const uint16_t start, const uint16_t finish, Maze *maze);

  ///  Create a simple pathstring representing the route from start to finsh in the maze
  /// but do not stop at unvisited cells
  void generateUnsafePath(const uint16_t start, const uint16_t finish, Maze *maze);
  void makeInPlaceCommands(const char *src, const uint16_t maxLength, uint8_t *commands);
  /// Convert the path to a set of commands using only 90 degree explore turns
  void makeDiagonalCommands(const char *src, const uint16_t maxLength, uint8_t *commands);
  /// Convert the path to a set of commands using the full range of turns and moves
  void makeSmoothCommands(const char *src, const uint16_t maxLength, uint8_t *commands);
  /// this is not well suited here but it makes migration easier
  void listCommands(uint8_t * commands);


  /// return the number of cells traversed by the path
  uint16_t cellCount();
  /// return a maesure of the distance (in mm) covered by the path
  uint16_t distance();
  /// the heading recorded in the maze at the start cell.
  uint8_t startHeading() const;
  /// the heading recorded in the maze at the finish cell.
  uint8_t endHeading() const;
  /// The cell where the path starts (in case the caller cannot remember?)
  uint16_t startCell() const;
  /// The cell where the path finishes. Not necessarily the requested finish cell.
  uint16_t endCell() const;
  /// The path may not reach the target and so more exploring will be needed
  bool reachesTarget() const;
  /// Reverse the path string to allow flooding from location to target
  void reversePath();
  void reversePath(char * s);

private:
  char mBuffer[MAX_PATH_LENGTH + 2];
  uint8_t mStartHeading;
  uint8_t mEndHeading;
  uint16_t mCellCount;
  uint16_t mStartCell;
  uint16_t mEndCell;
  uint16_t mDistance;
  bool mReachesTarget;
};


#endif /* MAZEPATHFINDER_H */

