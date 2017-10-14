/************************************************************************
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


#ifndef MAZESEARCHER_H
#define MAZESEARCHER_H

/*
 * The mazeSearcher is the mouse. The robot that explores and runs the libMaze.
 * It gets its sensor data from the worldview and uses it to update a libMaze
 * and act appropriately.
 *
 * It is here that the behaviour of the mouse will be defined. For each
 * action, a single public function should be defined.
 *
 * Note that there is no access to private state information except through
 * accessor functions. Thus, it is possible to implement the mouse in any
 * way the user chooses and the tests will only deal with the public
 * functions.
 *
 * A single SearchTo function is provided along with an enum naming the
 * search method and means to select one of those methods.
 *
 * From the outside, code should set a method and then call MouseSearchTo().
 * there should not be any direct calls to specific search methods.
 */

#include <stdint.h>

class MazeSearcher {
public:

  enum {
    SEARCH_NORMAL,
    SEARCH_ALTERNATE,
    SEARCH_LEFT_WALL,
    SEARCH_RIGHT_WALL,
  };

  enum {
    E_NO_ROUTE = -1,
    E_ROUTE_TOO_LONG = -2,
  };

  MazeSearcher();
  ~MazeSearcher();
  uint16_t location() const;
  void setLocation(uint16_t location);
  uint8_t heading() const;
  void setHeading(uint8_t heading);
  void setMapFromFileData(const uint8_t *mazeWalls, uint16_t cellCount);
  Maze *map();
  /// move the mouse 1 cell in in the current Heading
  const Maze *realMaze() const;
  void setRealMaze(const Maze *mRealMaze);
  void move();
  void turnRight();
  void turnLeft();
  void turnAround();
  /// follow direction data in the maze to get to the given target cell
  /// return the number of steps needed
  int runTo(uint16_t target);
  /// search unknown maze for target cell
  /// return the number of steps needed
  int searchTo(uint16_t target);

  void setSearchMethod(int mSearchMethod);
  bool isVerbose() const;
  void setVerbose(bool mVerbose);

  uint8_t followLeftWall() const;
  uint8_t followRightWall() const;
  uint8_t followAlternateWall() const;

private:
  uint16_t mLocation;
  uint8_t mHeading;
  Maze *mMap;
  const Maze *mRealMaze;
  bool mVerbose;
  int mSearchMethod;
  MazeSearcher &operator=(const MazeSearcher &rhs);
  MazeSearcher(const MazeSearcher &orig);
};

#endif /* MAZESEARCHER_H */

