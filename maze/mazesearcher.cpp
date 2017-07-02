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

#include <assert.h>
#include "maze.h"
#include "mazesearcher.h"
#include "mazeprinter.h"
#include "stddef.h"

MazeSearcher::MazeSearcher() :
    mLocation(0),
    mHeading(NORTH),
    mMap(NULL),
    mRealMaze(NULL),
    mVerbose(false),
    mSearchMethod(SEARCH_NORMAL) {
  mMap = new Maze(16);
  mMap->setFloodType(Maze::MANHATTAN_FLOOD);
}

MazeSearcher::~MazeSearcher() {
  delete mMap;
}

bool MazeSearcher::isVerbose() const {
  return mVerbose;
}

void MazeSearcher::setVerbose(bool mVerbose) {
  MazeSearcher::mVerbose = mVerbose;
}

uint16_t MazeSearcher::location() const {
  return mLocation;
}

void MazeSearcher::setLocation(uint16_t location) {
  MazeSearcher::mLocation = location;
}

uint8_t MazeSearcher::heading() const {
  return mHeading;
}

void MazeSearcher::setHeading(uint8_t heading) {
  MazeSearcher::mHeading = heading;
}

void MazeSearcher::move() {
  mLocation = mMap->neighbour(mLocation, mHeading);
}

void MazeSearcher::setMapFromFileData(const uint8_t *mazeWalls, uint16_t cellCount) {
  mMap->copyMazeFromFileData(mazeWalls, cellCount);
}

Maze *MazeSearcher::map() {
  return mMap;
}

const Maze *MazeSearcher::realMaze() const {
  return mRealMaze;
}

void MazeSearcher::setRealMaze(const Maze *maze) {
  mRealMaze = maze;
}

int MazeSearcher::runTo(uint16_t target) {
  int steps = 0;
  mMap->flood(target);
  while (mLocation != target) {
    uint8_t heading = mMap->direction(mLocation);
    if (heading == INVALID_DIRECTION) {
      steps = -1;
      break;
    }

    setHeading(heading);
    move();
    steps++;
    if (steps > 256) {
      steps = -2;
      break;
    }
    if (isVerbose()) {
      MazePrinter::printVisitedDirs(mMap);
    }
  }
  return steps;
}

// TODO: this needs looking at.
// the returned number of steps may be inconsistent
int MazeSearcher::searchTo(uint16_t target) {
  int stepCount = 0;
  while (mLocation != target) {
    mMap->updateMap(mLocation, mRealMaze->walls(mLocation));
    uint8_t newHeading;
    switch (mSearchMethod) {
      case SEARCH_LEFT_WALL:
        newHeading = followLeftWall();
        break;
      case SEARCH_RIGHT_WALL:
        newHeading = followRightWall();
        break;
      case SEARCH_ALTERNATE:
        newHeading = followAlternateWall();
        break;
      case SEARCH_NORMAL:
        mMap->flood(target);
        newHeading = mMap->direction(mLocation);
        break;
      default:
        newHeading = INVALID_DIRECTION;
        break;
    }
    if (newHeading == INVALID_DIRECTION) {
      stepCount = E_NO_ROUTE;
      break;
    }
    setHeading(newHeading);
    stepCount++;
    if (stepCount > mMap->numCells()) {
      stepCount = E_ROUTE_TOO_LONG;
      break;
    }
    move();
    if (isVerbose()) {
      MazePrinter::printVisitedDirs(mMap);
    }
  }
  return stepCount;
}

uint8_t MazeSearcher::followLeftWall() const {
  uint8_t newHeading;
  if (mMap->hasExit(mLocation, Maze::leftOf(mHeading))) {
    newHeading = Maze::leftOf(mHeading);
  } else if (mMap->hasExit(mLocation, Maze::ahead(mHeading))) {
    newHeading = Maze::ahead(mHeading);
  } else if (mMap->hasExit(mLocation, Maze::rightOf(mHeading))) {
    newHeading = Maze::rightOf(mHeading);
  } else {
    newHeading = Maze::behind(mHeading);
  }
  return newHeading;
}

uint8_t MazeSearcher::followRightWall() const {
  uint8_t newHeading;
  if (mMap->hasExit(mLocation, Maze::rightOf(mHeading))) {
    newHeading = Maze::rightOf(mHeading);
  } else if (mMap->hasExit(mLocation, Maze::ahead(mHeading))) {
    newHeading = Maze::ahead(mHeading);
  } else if (mMap->hasExit(mLocation, Maze::leftOf(mHeading))) {
    newHeading = Maze::leftOf(mHeading);
  } else {
    newHeading = Maze::behind(mHeading);
  }
  return newHeading;
}

uint8_t MazeSearcher::followAlternateWall() const {
  static bool useLeft = true;
  uint8_t newHeading;
  newHeading = useLeft ? followLeftWall() : followRightWall();
  useLeft = !useLeft;
  return newHeading;
}

void MazeSearcher::setSearchMethod(int mSearchMethod) {
  MazeSearcher::mSearchMethod = mSearchMethod;
}

void MazeSearcher::turnRight() {
  mHeading = Maze::rightOf(mHeading);
}

void MazeSearcher::turnLeft() {
  mHeading = Maze::leftOf(mHeading);
}

void MazeSearcher::turnAround() {
  mHeading = Maze::behind(mHeading);
}
