/*
 * File:   mazesearcher.c
 * Author: peterharrison
 *
 * Created on 17 February 2016, 21:31
 */
#include <assert.h>
#include "maze.h"
#include "mazesearcher.h"
#include "mazeprinter.h"
#include "stddef.h"



/* move the mouse by one cell in the direction given by heading */
/* no error checking is done for walls or borders */
//void MouseMove (void)
//{
////  MouseSetPosition (Neighbour (mousePosition, mouseHeading));
//}


/*
 * Perform a search from the mouse current mLocation to the target mLocation
 * uses a full flood after each step
 * Returns the number of steps needed to get to the target
 */
//int MouseSearchToFullFlood (location_t target)
//{
//
//  int steps = 0;
//  while (! (MousePosition().row == target.row && MousePosition().col == target.col)) {
////    walldata_t actualWalls = ReadWallSensors (MousePosition());
////    UpdateCellFromWallData (MousePosition(), actualWalls);
////    FloodMazeClassic (target);
//    direction_t direction = Direction (MousePosition());
//    if (direction == BAD_DIRECTION) {
//      break;
//    }
//    MouseSetHeading (direction);
//    MouseMove();
//    steps++;
//  }
//  return steps;
//}


//int MouseSearchToModifiedFlood (location_t target)
//{
//
//  int steps = 0;
////  FloodMazeClassic (target);	/* seed the costs before using modified flood */
//  while (! (MousePosition().row == target.row && MousePosition().col == target.col)) {
////    walldata_t actualWalls = ReadWallSensors (MousePosition());
////    UpdateCellFromWallData (MousePosition(), actualWalls);
//    //ModifiedFlood (MousePosition());
//    direction_t direction = Direction (MousePosition());
//    MouseSetHeading (direction);
//    MouseMove();
//    steps++;
//    if (steps > 500) {
//      break;
//    }
//  }
//  return steps;
//}


//int MouseSearchToModifiedFloodAll (location_t target)
//{
//
//  int steps = 0;
////  FloodMazeClassic (target);	/* seed the costs before using modified flood */
//  while (! (MousePosition().row == target.row && MousePosition().col == target.col)) {
////    walldata_t actualWalls = ReadWallSensors (MousePosition());
////    UpdateCellFromWallData (MousePosition(), actualWalls);
//    //ModifiedFloodAll (MousePosition());
//    direction_t direction = Direction (MousePosition());
//    MouseSetHeading (direction);
//    MouseMove();
//    steps++;
//    if (steps > 500) {
//      break;
//    }
//  }
//  return steps;
//}


MazeSearcher::MazeSearcher() :
    mHeading(NORTH),
    mLocation(0),
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

//TODO: this needs looking at. the returned number of steps is inconsistent
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
