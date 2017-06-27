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
    mVerbose(false) {
  mMaze = new Maze(16);
}

MazeSearcher::~MazeSearcher() {
  delete mMaze;
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
  mLocation = mMaze->neighbour(mLocation, mHeading);
}

void MazeSearcher::setMazeWalls(const uint8_t *mazeWalls, uint16_t cellCount) {
  mMaze->copyMazeFromFileData(mazeWalls, cellCount);
}

Maze *MazeSearcher::maze() {
  return mMaze;
}

const Maze *MazeSearcher::realMaze() const {
  return mRealMaze;
}

void MazeSearcher::setRealMaze(const Maze *maze) {
  mRealMaze = maze;
}

int MazeSearcher::runTo(uint16_t target) {
  int steps = 0;
  mMaze->flood(target);
  while (mLocation != target) {
    uint8_t heading = mMaze->direction(mLocation);
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
      MazePrinter::printVisitedDirs(mMaze);
    }
  }
  return steps;
}

//TODO: this needs looking at. the returned number of steps is inconsistent
int MazeSearcher::searchTo(uint16_t target) {
  int result = 0;
  while (mLocation != target) {
    mMaze->updateMap(mLocation, mRealMaze->walls(mLocation));
    mMaze->flood(target);
    uint8_t newHeading = mMaze->direction(mLocation);
    if (newHeading == INVALID_DIRECTION) {
      result = E_NO_ROUTE;
      break;
    }
    result++;
    if (result > mMaze->numCells()) {
      result = E_ROUTE_TOO_LONG;
      break;
    }

    switch (searchMethod()) {
      case SEARCH_LEFT_WALL:

        if (mMaze->hasExit(mLocation, Maze::leftOf(mHeading))) {
          newHeading = Maze::leftOf(mHeading);
        } else if (mMaze->hasExit(mLocation, Maze::ahead(mHeading))) {
          newHeading = Maze::ahead(mHeading);
        } else if (mMaze->hasExit(mLocation, Maze::rightOf(mHeading))) {
          newHeading = Maze::rightOf(mHeading);
        } else {
          newHeading = Maze::behind(mHeading);
        }
        setHeading(newHeading);
        break;
      case SEARCH_RIGHT_WALL:
        break;
      case SEARCH_RANDOM:
        break;
      case SEARCH_NORMAL:
      default:

        setHeading(newHeading);
        break;
    }
    move();
    if (isVerbose()) {
      MazePrinter::printVisitedDirs(mMaze);
    }
  }
  return result;
}

int MazeSearcher::searchMethod() const {
  return mSearchMethod;
}

void MazeSearcher::setSearchMethod(int mSearchMethod) {
  MazeSearcher::mSearchMethod = mSearchMethod;
}
