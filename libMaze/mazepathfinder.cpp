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
#include <stdio.h>
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
  PathFinish,
  PathError
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
  mReachesTarget(false) {
  memset(mBuffer, 0, 1024);
}

PathFinder::~PathFinder() {

}

char *PathFinder::path() {
  return mBuffer;
}

static char pathOptions[16] = {
  'F', 'R', 'A', 'L',
  'L', 'F', 'R', 'A',
  'A', 'L', 'F', 'R',
  'R', 'A', 'L', 'F'
};

void PathFinder::generateSafePath(const uint16_t start, const uint16_t target, Maze *maze) {

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
  while (here != target) {
    if (!maze->isVisited(here)) {
      break;
    }
    if (mCellCount >= MAX_PATH_LENGTH) {
      break;
    }
    uint8_t headingLast = headingHere;
    headingHere = maze->direction(here);
    char command = pathOptions[headingLast * 4 + headingHere];
    if (command == 'R') {
      mEndHeading = Maze::rightOf(mEndHeading);
      distance += 127;
    }
    if (command == 'L') {
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

void PathFinder::makeDiagonalCommands(const char *src, const uint16_t maxLength, uint8_t *commands) {
  int runLength = 0;
  int p = 0;
  pathgen_state_t state = PathInit;
  assert(maxLength > 2);
  while (state != PathFinish) {
    if (runLength > 31) { // MAGIC: maximum for hald-size libMaze
      commands[0] = CMD_ERROR;
      commands[1] = CMD_STOP;
      break;
    }
    if (p >= maxLength) {
      commands[0] = CMD_ERROR;
      commands[1] = CMD_STOP;
      break;
    }
    char c = *src++;
    switch (state) {
      case PathInit:
        if (c == 'B') {
          commands[p++] = (CMD_BEGIN);
          state = PathStart;
        } else {
          commands[p++] = (CMD_ERR_BEGIN);
          state = PathStop;
        }
        break;
      case PathStart:
        if (c == 'F') {
          runLength = 1;
          state = PathOrtho_F;
        } else if (c == 'R') {
          commands[p++] = (CMD_ERROR_NOF);
          state = PathStop;
        } else if (c == 'L') {
          commands[p++] = (CMD_ERROR_NOF);
          state = PathStop;
        } else if (c == 'S') {
          state = PathStop;
        } else if (c == 'X') {
          state = PathExit;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathOrtho_F:
        if (c == 'F') {
          runLength++;
        } else if (c == 'R') {
          commands[p++] = (FWD0 + runLength);
          state = PathOrtho_R;
        } else if (c == 'L') {
          commands[p++] = (FWD0 + runLength);
          state = PathOrtho_L;
        } else if (c == 'S') {
          commands[p++] = (FWD0 + runLength);
          state = PathStop;
        } else if (c == 'X') {
          commands[p++] = (FWD0 + runLength);
          state = PathExit;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathOrtho_R:
        if (c == 'F') {
          commands[p++] = (SS90FR);
          runLength = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          state = PathOrtho_RR;
        } else if (c == 'L') {
          commands[p++] = (SD45R);
          runLength = 2;
          state = PathDiag_RL;
        } else if (c == 'S') {
          commands[p++] = (SS90ER);
          commands[p++] = (FWD1);
          state = PathStop;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathOrtho_L:
        if (c == 'F') {
          commands[p++] = (SS90FL);
          runLength = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          commands[p++] = (SD45L);
          runLength = 2;
          state = PathDiag_LR;
        } else if (c == 'L') {
          state = PathOrtho_LL;
        } else if (c == 'S') {
          commands[p++] = (SS90EL);
          commands[p++] = (FWD1);
          state = PathStop;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathOrtho_RR:
        if (c == 'F') {
          commands[p++] = (SS180R);
          runLength = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          commands[p++] = (CMD_ERROR_RRR);
          state = PathStop;
        } else if (c == 'L') {
          commands[p++] = (SD135R);
          runLength = 2;
          state = PathDiag_RL;
        } else if (c == 'S') {
          commands[p++] = (SS180R);
          commands[p++] = (FWD1);
          state = PathStop;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathDiag_RL:
        if (c == 'F') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DS45L);
          runLength = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          runLength += 1;
          state = PathDiag_LR;
        } else if (c == 'L') {
          state = PathDiag_LL;
        } else if (c == 'S') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DS45L);
          commands[p++] = (FWD1);
          state = PathStop;
        } else if (c == 'X') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DS45L);
          commands[p++] = (FWD1);
          state = PathExit;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathDiag_LR:
        if (c == 'F') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DS45R);
          runLength = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          state = PathDiag_RR;
        } else if (c == 'L') {
          runLength += 1;
          state = PathDiag_RL;
        } else if (c == 'S') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DS45R);
          commands[p++] = (FWD1);
          state = PathStop;
        } else if (c == 'X') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DS45R);
          commands[p++] = (FWD1);
          state = PathExit;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathOrtho_LL:
        if (c == 'F') {
          commands[p++] = (SS180L);
          runLength = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          commands[p++] = (SD135L);
          runLength = 2;
          state = PathDiag_LR;
        } else if (c == 'L') {
          commands[p++] = (CMD_ERROR_LLL);
          state = PathStop;
        } else if (c == 'S') {
          commands[p++] = (SS180L);
          commands[p++] = (FWD1);
          state = PathStop;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathDiag_LL:
        if (c == 'F') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DS135L);
          runLength = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DD90L);
          runLength = 2;
          state = PathDiag_LR;
        } else if (c == 'L') {
          commands[p++] = (CMD_ERROR_LLL);
          state = PathStop;
        } else if (c == 'S') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DS135L);
          commands[p++] = (FWD1);
          state = PathStop;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathDiag_RR:
        if (c == 'F') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DS135R);
          runLength = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          state = PathDiag_RR;
        } else if (c == 'L') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DD90R);
          runLength = 2;
          state = PathDiag_RL;
        } else if (c == 'S') {
          commands[p++] = (DIA0 + runLength);
          commands[p++] = (DS135R);
          commands[p++] = (FWD1);
          state = PathStop;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathStop:
        commands[p++] = (CMD_STOP);  // make sure the command list gets terminated
        state = PathFinish;
        break;
      case PathExit:
        commands[p++] = (CMD_EXPLORE);
        commands[p++] = (CMD_STOP);  // make sure the command list gets terminated
        state = PathFinish;
        break;
      default:
        commands[p++] = (CMD_ERROR_15);
        state = PathFinish;
        break;
    }
  }
}

/*
 * The smooth command list uses only orthogonal moves and 90 degree
 * explore turns. It should be very safe but continuous.
 * It is suitable for moving the mouse more rapidly in the libMaze while
 * exploring but where it is not felt safe to use diagonals
 */
void PathFinder::makeSmoothCommands(const char *src, const uint16_t maxLength, uint8_t *commands) {
  int runLength = 0; // a counter for the number of cells to be crossed
  int p = 0;
  pathgen_state_t state = PathInit;
  while (state != PathFinish) {
    if (runLength >= 31) { // MAGIC: maximum for hald-size libMaze
      commands[p++] = CMD_ERROR;
      commands[p] = CMD_STOP;
      break;
    }
    if (p >= maxLength) {
      commands[0] = CMD_ERROR;
      commands[1] = CMD_STOP;
      break;
    }

    char c = *src++;
    switch (state) {
      case PathInit:
        if (c == 'B') {
          commands[p++] = (CMD_BEGIN);
          state = PathStart;
        } else {
          commands[p++] = (CMD_ERR_BEGIN);
          state = PathStop;
        }
        break;
      case PathStart:
        if (c == 'F') {
          runLength = 1;
          state = PathOrtho_F;
        } else if (c == 'R') {
          commands[p++] = (CMD_ERROR_NOF);
          state = PathStop;
        } else if (c == 'L') {
          commands[p++] = (CMD_ERROR_NOF);
          state = PathStop;
        } else if (c == 'X') {
          state = PathExit;
        } else if (c == 'S') {
          state = PathStop;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathOrtho_F:
        if (c == 'F') {
          runLength++;
        } else if (c == 'R') {
          commands[p++] = (FWD0 + runLength);
          state = PathOrtho_R;
        } else if (c == 'L') {
          commands[p++] = (FWD0 + runLength);
          state = PathOrtho_L;
        } else if (c == 'X') {
          commands[p++] = (FWD0 + runLength);
          state = PathExit;
        } else if (c == 'S') {
          commands[p++] = (FWD0 + runLength);
          state = PathStop;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathOrtho_R:
        if (c == 'F') {
          commands[p++] = (SS90ER);
          runLength = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          commands[p++] = (SS90ER);
          commands[p++] = (FWD1);
          state = PathOrtho_R;
        } else if (c == 'L') {
          commands[p++] = (SS90ER);
          commands[p++] = (FWD1);
          state = PathOrtho_L;
        } else if (c == 'X') {
          commands[p++] = (SS90ER);
          commands[p++] = (FWD1);
          state = PathExit;
        } else if (c == 'S') {
          commands[p++] = (SS90ER);
          commands[p++] = (FWD1);
          state = PathStop;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathOrtho_L:
        if (c == 'F') {
          commands[p++] = (SS90EL);
          runLength = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          commands[p++] = (SS90EL);
          commands[p++] = (FWD1);
          state = PathOrtho_R;
        } else if (c == 'L') {
          commands[p++] = (SS90EL);
          commands[p++] = (FWD1);
          state = PathOrtho_L;
        } else if (c == 'X') {
          commands[p++] = (SS90EL);
          commands[p++] = (FWD1);
          state = PathExit;
        } else if (c == 'S') {
          commands[p++] = (SS90EL);
          commands[p++] = (FWD1);
          state = PathStop;
        } else {
          commands[p++] = (CMD_ERROR_END);
          state = PathStop;
        }
        break;
      case PathStop:
        commands[p] = (CMD_STOP);  // make sure the command list gets terminated
        state = PathFinish;
        break;
      case PathExit:
        commands[p++] = (CMD_EXPLORE);
        commands[p] = (CMD_STOP);  // make sure the command list gets terminated
        state = PathFinish;
        break;
      default:
        commands[p++] = (CMD_ERROR);
        state = PathFinish;
        break;
    }
  }
}

/*
 *
 */
void PathFinder::makeInPlaceCommands(const char *src, const uint16_t maxLength, uint8_t *commands) {
  int p = 0;
  int runLength = 0;
  unsigned char cmd;
  bool finished = false;
  assert(maxLength >= 2);
  while (!finished) {
    if (p >= maxLength) {
      commands[0] = CMD_ERROR;
      commands[1] = CMD_STOP;
      break;
    }
    char c = *src++;

    switch (c) {
      case 'B':
        commands[p++] = CMD_BEGIN;
        cmd = FWD0;
        runLength = 0;
        break;
      case 'F':
        cmd++;
        runLength++;
        if (runLength >= 31) { // MAGIC: maximum for hald-size libMaze
          commands[p++] = CMD_ERROR;
          commands[p] = CMD_STOP;
          finished = true;
        }
        break;
      case 'L':
        commands[p++] = cmd;
        commands[p++] = IP90L;
        cmd = FWD1;
        break;
      case 'R':
        commands[p++] = cmd;
        commands[p++] = IP90R;
        cmd = FWD1;
        break;
      case 'S':
        commands[p++] = cmd;
        commands[p++] = CMD_STOP;
        finished = true;
        break;
      case 'X':
        commands[p++] = cmd;
        commands[p++] = CMD_EXPLORE;
        commands[p] = CMD_STOP;
        finished = true;
        break;
      default:
        commands[p++] = CMD_ERROR;
        commands[p] = CMD_STOP;
        finished = true;
        break;
    }
  };
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


void PathFinder::generateUnsafePath(const uint16_t start, const uint16_t target, Maze *maze) {

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
  while (here != target) {
    if (mCellCount >= MAX_PATH_LENGTH) {
      break;
    }
    uint8_t headingLast = headingHere;
    headingHere = maze->direction(here);
    char command = pathOptions[headingLast * 4 + headingHere];
    if (command == 'R') {
      mEndHeading = Maze::rightOf(mEndHeading);
      distance += 127;
    }
    if (command == 'L') {
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

void PathFinder::reversePath(char * s) {
  int length = strlen(s);
  if (length == 0) {
    return;
  }
  int i, j;
  int terminator = s[length - 1];
  for (i = 0, j = length - 1; i < j; i++, j--) {
    int c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
  // All the directions get reversed
  for (i = 0; i < length; i++) {
    int c = s[i];
    if (c == 'R') {
      c = 'L';
    } else if (c == 'L') {
      c = 'R';
    }
    s[i] = c;
  }
  // fixup the begin and terminator
  s[0] = 'B';
  s[length - 1] = terminator;
}

void PathFinder::reversePath() {
  reversePath(mBuffer);
}

