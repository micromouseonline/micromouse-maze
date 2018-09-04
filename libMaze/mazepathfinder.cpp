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

#include "mazepathfinder.h"
#include <cstdio>
#include <cstring>

static const char *inPlaceTurnNames[] = {
  "IP45R",
  "IP45L",
  "IP90R",
  "IP90L",
  "IP135R",
  "IP135L",
  "IP180R",
  "IP180L",
};

static const char *smoothTurnNames[] = {
  "SS90SR",
  "SS90SL",
  "SS90FR",
  "SS90FL",
  "SS180R",
  "SS180L",
  "SD45R",
  "SD45L",
  "SD135R",
  "SD135L",
  "DS45R",
  "DS45L",
  "DS135R",
  "DS135L",
  "DD90R",
  "DD90L",
  "SS90ER",
  "SS90EL"
};

typedef enum {
  PathInit,
  PathStart,
  PathOrtho_F,
  PathOrtho_R,
  PathOrtho_L,
  PathOrtho_RR,
  PathOrtho_LL,
  PathDiag_RL,
  PathDiag_LR,
  PathDiag_RR,
  PathDiag_LL,
  PathStop,
  PathExit,
  PathFinish
} pathgen_state_t;

/*
 * Generate a path from cost data following a flood;
 * The method simply walks downhill from start to target marking the
 * direction data on its way.
 * All cells not on the path will have INVALID direction data
 * Returns the length of the path in cells
 *
 * No attempt is made to verify that a valid path exists
 */


PathFinder::PathFinder() :
  mStartHeading(INVALID_DIRECTION),
  mEndHeading(INVALID_DIRECTION),
  mCellCount(0),
  mStartCell(0),
  mEndCell(0),
  mDistance(0),
  mReachesTarget(false),
  mStopAtUnvisited(true) {
  memset(mBuffer, 0, 1024);
}

PathFinder::~PathFinder() = default;

char *PathFinder::path() {
  return mBuffer;
}

static char pathOptions[16] = {
  'F', 'R', 'A', 'L',
  'L', 'F', 'R', 'A',
  'A', 'L', 'F', 'R',
  'R', 'A', 'L', 'F'
};

/*
 * mouse only ever uses
 * setUnknowns + unsafe for a speedrun
 * and
 * clearUnknowns + safe for searching
 *
 * setUnknowns means using the SAFE_MASK (closed)
 * with this setting, the path cannot go through unknown cells
 * so safe and unsafe should be the same once the goal has been found
 *
 * clearUnknowns means using the UNSAFE_MASK (open)
 */
void PathFinder::generateSafePath(const uint16_t start, const uint16_t target, Maze *maze) {
  mStopAtUnvisited = true;
  //  CONVERT THIS FOR SAFETY MASK
  generatePath(start, target, maze);
}

void PathFinder::generateUnsafePath(const uint16_t start, const uint16_t target, Maze *maze) {
  mStopAtUnvisited = false;
  generatePath(start, target, maze);
}

void PathFinder::generatePath(const uint16_t start, const uint16_t target, Maze *maze) {

  char *pPath = mBuffer;
  uint16_t distance = 0;
  uint16_t here = start;
  uint8_t headingHere = maze->direction(here);
  mStartCell = start;
  mEndCell = target;
  mStartHeading = headingHere;
  mEndHeading = mStartHeading;
  mCellCount = 0;
  *pPath++ = 'B';
  if (headingHere == INVALID_DIRECTION) {
    *pPath++ = 'S';
    *pPath = 0;
    return;
  }
  char lastTurn = 'F';
  while (here != target) {
    if (mStopAtUnvisited && !maze->isVisited(here)) {
      break;
    }
    if (mCellCount >= MAX_PATH_LENGTH) {
      break;
    }
    uint8_t headingLast = headingHere;
    //    headingHere = maze->direction(here);
    char command = pathOptions[headingLast * 4 + headingHere];
    uint16_t smallest = maze->cost(here);
    uint16_t nextCost;
    switch (lastTurn) {
      case 'L':
        nextCost = maze->cost(here, Maze::rightOf(headingHere));
        if (nextCost < smallest) {
          smallest = nextCost;
          command = 'R';
        }
        nextCost = maze->cost(here, Maze::ahead(headingHere));
        if (nextCost < smallest) {
          smallest = nextCost;
          command = 'F';
        }
        nextCost = maze->cost(here, Maze::leftOf(headingHere));
        if (nextCost < smallest) {
          command = 'L';
        }

        break;
      case 'R':
        nextCost = maze->cost(here, Maze::leftOf(headingHere));
        if (nextCost < smallest) {
          smallest = nextCost;
          command = 'L';
        }
        nextCost = maze->cost(here, Maze::ahead(headingHere));
        if (nextCost < smallest) {
          smallest = nextCost;
          command = 'F';
        }
        nextCost = maze->cost(here, Maze::rightOf(headingHere));
        if (nextCost < smallest) {
          command = 'R';
        }
        break;
      default:
        nextCost = maze->cost(here, Maze::ahead(headingHere));
        if (nextCost < smallest) {
          smallest = nextCost;
          command = 'F';
        }
        nextCost = maze->cost(here, Maze::rightOf(headingHere));
        if (nextCost < smallest) {
          smallest = nextCost;
          command = 'R';
        }
        nextCost = maze->cost(here, Maze::leftOf(headingHere));
        if (nextCost < smallest) {
          command = 'L';
        }
        break;
    }
    lastTurn = command;
    if (command == 'R') {
      headingHere = Maze::rightOf(headingHere);
      mEndHeading = Maze::rightOf(mEndHeading);
      distance += 127;
    }
    if (command == 'L') {
      headingHere = Maze::leftOf(headingHere);
      mEndHeading = Maze::leftOf(mEndHeading);
      distance += 127;
    }
    if (command == 'F') {
      distance += 180;
    }
    *pPath++ = command;
    mCellCount++;
    here = maze->neighbour(here, headingHere);
  }
  mEndCell = here;
  if (mEndCell == target) {
    *pPath++ = 'S';
    mReachesTarget = true;
  } else {
    *pPath++ = 'X';
    mReachesTarget = false;
  }
  // this is a string to be sure it gets terminated properly
  mCellCount++;
  *pPath = 0;
  mDistance = distance;
}

/**
 * The length will always include the final move ('S" or 'X') as it is
 * a cell through which the mouse moves.
 * The start marker ('B') is not counted
 *
 */
uint16_t PathFinder::cellCount() {
  return mCellCount;
}

uint8_t PathFinder::startHeading() const {
  return mStartHeading;
}

uint8_t PathFinder::endHeading() const {
  return mEndHeading;
}

uint16_t PathFinder::endCell() const {
  return mEndCell;
}

bool PathFinder::reachesTarget() const {
  return mReachesTarget;
}

uint16_t PathFinder::startCell() const {
  return mStartCell;
}

void PathFinder::listCommands(uint8_t *commands) {
  char done = 0;
  printf("\n");
  while (!done) {
    unsigned char command = *commands++;
    if (command == CMD_END) {
      printf("CMD_END\n");
    } else if (command == CMD_ERROR) {
      printf("CMD_ERROR, ");
    } else if (command == CMD_EXPLORE) {
      printf("CMD_EXPLORE\n");
    } else if (command == CMD_STOP) {
      printf("CMD_STOP\n");
      done = 1;
    } else if (command == CMD_BEGIN) {
      printf("%s, ", "CMD_BEGIN");
    } else if (command <= FWD31) {
      printf("FWD%d, ", command - FWD0);
    } else if (command <= DIA31) {
      printf("DIA%d, ", command - DIA0);
    } else if (command <= IP180L) {
      printf("%s, ", inPlaceTurnNames[command - INPLACE]);
    } else if (command <= SS90EL) {
      printf("%s, ", smoothTurnNames[command - SMOOTH]);
    } else if (command >= 0xF0) {
      printf("CMD_ERROR_%02d, ", command - 0xF0);
    } else {
      printf("OTHER - %02x\n", command);
    }
  }
}

uint16_t PathFinder::distance() {
  return mDistance;
}

void PathFinder::reversePath() {

}

void PathFinder::reversePath(char *s) {
  (void)s;
}
