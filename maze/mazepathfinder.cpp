/*
 * File:   mazepathfinder.c
 * Author: peterharrison
 *
 * Created on 16 February 2016, 14:55
 */

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
    mCellCount(0),
    mStartHeading(INVALID_DIRECTION),
    mEndHeading(INVALID_DIRECTION),
    mStartCell(0),
    mEndCell(0),
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

void PathFinder::generatePath(const uint16_t start, const uint16_t target, Maze *maze) {

  char *pPath = mBuffer;
  uint16_t here = start;
  uint8_t headingHere = maze->direction(here);
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
    }
    if (command == 'L') {
      mEndHeading = Maze::leftOf(mEndHeading);
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
}

/**
 * The length will always include the final move ('S" or 'X') as it is
 * a cell through which the mouse moves.
 * The start marker ('B') is not counted
 *
 */
uint16_t PathFinder::length() {
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

void PathFinder::makeDiagonalCommands(const char *src, uint8_t *pCommands) {
  int cellCount = 0;
  pathgen_state_t state = PathInit;
  while (state != PathFinish) {
    char c = *src++;
    switch (state) {
      case PathInit:
        if (c == 'B'){
          *pCommands++ = (CMD_BEGIN);
          state = PathStart;
        } else {
          *pCommands++ = (CMD_ERR_BEGIN);
          state = PathStop;
        }
        break;
      case PathStart:
        if (c == 'F') {
          cellCount = 1;
          state = PathOrtho_F;
        } else if (c == 'R') {
          *pCommands++ = (CMD_ERROR_00);
          state = PathStop;
        } else if (c == 'L') {
          *pCommands++ = (CMD_ERROR_00);
          state = PathStop;
        } else if (c == 'S') {
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_00);
          state = PathStop;
        }
        break;
      case PathOrtho_F:
        if (c == 'F') {
          cellCount++;
        } else if (c == 'R') {
          *pCommands++ = (FWD0 + cellCount);
          state = PathOrtho_R;
        } else if (c == 'L') {
          *pCommands++ = (FWD0 + cellCount);
          state = PathOrtho_L;
        } else if (c == 'S') {
          *pCommands++ = (FWD0 + cellCount);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_01);
          state = PathStop;
        }
        break;
      case PathOrtho_R:
        if (c == 'F') {
          *pCommands++ = (SS90FR);
          cellCount = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          state = PathOrtho_RR;
        } else if (c == 'L') {
          *pCommands++ = (SD45R);
          cellCount = 2;
          state = PathDiag_RL;
        } else if (c == 'S') {
          *pCommands++ = (SS90ER);
          *pCommands++ = (FWD1);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_02);
          state = PathStop;
        }
        break;
      case PathOrtho_L:
        if (c == 'F') {
          *pCommands++ = (SS90FL);
          cellCount = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          *pCommands++ = (SD45L);
          cellCount = 2;
          state = PathDiag_LR;
        } else if (c == 'L') {
          state = PathOrtho_LL;
        } else if (c == 'S') {
          *pCommands++ = (SS90EL);
          *pCommands++ = (FWD1);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_03);
          state = PathStop;
        }
        break;
      case PathOrtho_RR:
        if (c == 'F') {
          *pCommands++ = (SS180R);
          cellCount = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          *pCommands++ = (CMD_ERROR_04);
          state = PathStop;
        } else if (c == 'L') {
          *pCommands++ = (SD135R);
          cellCount = 2;
          state = PathDiag_RL;
        } else if (c == 'S') {
          *pCommands++ = (SS180R);
          *pCommands++ = (FWD1);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_04);
          state = PathStop;
        }
        break;
      case PathDiag_RL:
        if (c == 'F') {
          *pCommands++ = (DIA0 + cellCount);
          *pCommands++ = (DS45L);
          cellCount = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          cellCount += 1;
          state = PathDiag_LR;
        } else if (c == 'L') {
          state = PathDiag_LL;
        } else if (c == 'S') {
          *pCommands++ = (DIA0 + cellCount);
          *pCommands++ = (DS45L);
          *pCommands++ = (FWD1);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_05);
          state = PathStop;
        }
        break;
      case PathDiag_LR:
        if (c == 'F') {
          *pCommands++ = (DIA0 + cellCount);
          *pCommands++ = (DS45R);
          cellCount = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          state = PathDiag_RR;
        } else if (c == 'L') {
          cellCount += 1;
          state = PathDiag_RL;
        } else if (c == 'S') {
          *pCommands++ = (DIA0 + cellCount);
          *pCommands++ = (DS45R);
          *pCommands++ = (FWD1);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_06);
          state = PathStop;
        }
        break;
      case PathOrtho_LL:
        if (c == 'F') {
          *pCommands++ = (SS180L);
          cellCount = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          *pCommands++ = (SD135L);
          cellCount = 2;
          state = PathDiag_LR;
        } else if (c == 'L') {
          *pCommands++ = (CMD_ERROR_07);
          state = PathStop;
        } else if (c == 'S') {
          *pCommands++ = (SS180L);
          *pCommands++ = (FWD1);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_07);
          state = PathStop;
        }
        break;
      case PathDiag_LL:
        if (c == 'F') {
          *pCommands++ = (DIA0 + cellCount);
          *pCommands++ = (DS135L);
          cellCount = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          *pCommands++ = (DIA0 + cellCount);
          *pCommands++ = (DD90L);
          cellCount = 2;
          state = PathDiag_LR;
        } else if (c == 'L') {
          *pCommands++ = (CMD_ERROR_08);
          state = PathStop;
        } else if (c == 'S') {
          *pCommands++ = (DIA0 + cellCount);
          *pCommands++ = (DS135L);
          *pCommands++ = (FWD1);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_08);
          state = PathStop;
        }
        break;
      case PathDiag_RR:
        if (c == 'F') {
          *pCommands++ = (DIA0 + cellCount);
          *pCommands++ = (DS135R);
          cellCount = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          state = PathDiag_RR;
        } else if (c == 'L') {
          *pCommands++ = (DIA0 + cellCount);
          *pCommands++ = (DD90R);
          cellCount = 2;
          state = PathDiag_RL;
        } else if (c == 'S') {
          *pCommands++ = (DIA0 + cellCount);
          *pCommands++ = (DS135R);
          *pCommands++ = (FWD1);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_09);
          state = PathStop;
        }
        break;
      case PathStop:
        *pCommands++ = (CMD_STOP);  // make sure the command list gets terminated
        state = PathFinish;
        break;
      case PathExit:
        *pCommands++ = (CMD_EXPLORE);
        *pCommands++ = (CMD_STOP);  // make sure the command list gets terminated
        state = PathFinish;
        break;
      default:
        *pCommands++ = (CMD_ERROR_15);
        state = PathFinish;
        break;
    }
  }
}

/*
 * The smooth command list uses only orthogonal moves and 90 degree
 * explore turns. It should be very safe but continuous.
 * It is suitable for moving the mouse more rapidly in the maze while
 * exploring but where it is not felt safe to use diagonals
 */
void PathFinder::makeSmoothCommands(const char *src, uint8_t *pCommands) {
  int x = 0; // a counter for the number of cells to be crossed
  pathgen_state_t state = PathInit;
  while (state != PathFinish) {
    char c = *src++;
    switch (state) {
      case PathInit:
        if (c=='B'){
          *pCommands++ = (CMD_BEGIN);
          state = PathStart;
        } else {
          *pCommands++ = (CMD_ERR_BEGIN);
          state = PathStop;
        }
        break;
      case PathStart:
        if (c == 'F') {
          x = 1;
          state = PathOrtho_F;
        } else if (c == 'R') {
          *pCommands++ = (CMD_ERROR_00);
          state = PathStop;
        } else if (c == 'L') {
          *pCommands++ = (CMD_ERROR_00);
          state = PathStop;
        } else if (c == 'X') {
          state = PathExit;
        } else if (c == 'S') {
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_00);
          state = PathStop;
        }
        break;
      case PathOrtho_F:
        if (c == 'F') {
          x++;
        } else if (c == 'R') {
          *pCommands++ = (FWD0 + x);
          state = PathOrtho_R;
        } else if (c == 'L') {
          *pCommands++ = (FWD0 + x);
          state = PathOrtho_L;
        } else if (c == 'X') {
          state = PathExit;
        } else if (c == 'S') {
          *pCommands++ = (FWD0 + x);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_01);
          state = PathStop;
        }
        break;
      case PathOrtho_R:
        if (c == 'F') {
          *pCommands++ = (SS90ER);
          x = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          *pCommands++ = (SS90ER);
          *pCommands++ = (FWD1);
          state = PathOrtho_R;
        } else if (c == 'L') {
          *pCommands++ = (SS90ER);
          *pCommands++ = (FWD1);
          state = PathOrtho_L;
        } else if (c == 'X') {
          *pCommands++ = (SS90ER);
          *pCommands++ = (FWD1);
          state = PathExit;
        } else if (c == 'S') {
          *pCommands++ = (SS90ER);
          *pCommands++ = (FWD1);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_02);
          state = PathStop;
        }
        break;
      case PathOrtho_L:
        if (c == 'F') {
          *pCommands++ = (SS90EL);
          x = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          *pCommands++ = (SS90EL);
          *pCommands++ = (FWD1);
          state = PathOrtho_R;
        } else if (c == 'L') {
          *pCommands++ = (SS90EL);
          *pCommands++ = (FWD1);
          state = PathOrtho_L;
        } else if (c == 'X') {
          *pCommands++ = (SS90EL);
          *pCommands++ = (FWD1);
          state = PathExit;
        } else if (c == 'S') {
          *pCommands++ = (SS90EL);
          *pCommands++ = (FWD1);
          state = PathStop;
        } else {
          *pCommands++ = (CMD_ERROR_03);
          state = PathStop;
        }
        break;
      case PathStop:
        *pCommands++ = (CMD_STOP);  // make sure the command list gets terminated
        state = PathFinish;
        break;
      case PathExit:
        *pCommands++ = (CMD_EXPLORE);
        *pCommands++ = (CMD_STOP);  // make sure the command list gets terminated
        state = PathFinish;
        break;
      default:
        *pCommands++ = (CMD_ERROR_15);
        state = PathFinish;
        break;
    }
  }
}

/*
 * TODO: The pathstring must always end in a null (CMD_STOP) so that it can be treated as a string
 * TODO: protection is needed against over-running the command buffer.
 * TODO: CMD_STOP should not be how 'S' makes it end probably.
 * TODO: could this usefully return a value like the path length or negative for an error
 *
 */
void PathFinder::makeInPlaceCommands(const char *src, uint8_t *commands) {
  int p = 0;
  unsigned char cmd;
  bool finished = false;
  while (!finished) {
    if (p > 250) {
      break;
    }
    char c = *src++;
    switch (c) {
      case 'B':
        commands[p++] = CMD_BEGIN;
        cmd = FWD0;
        break;
      case 'F':
        cmd++;
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
    } else if (command == CMD_EXPLORE) {
      printf("CMD_EXPLORE\n");
    } else if (command == CMD_STOP) {
      printf("CMD_STOP\n");
      done = 1;
    } else if (command == CMD_BEGIN) {
      printf("%s, ", "CMD_BEGIN");
    } else if (command < FWD16) {
      printf("FWD%d, ", command - FWD0);
    } else if (command < DIA31) {
      printf("DIA%d, ", command - DIA0);
    } else if (command <= IP180L) {
      printf("%s, ", inPlaceTurnNames[command - INPLACE]);
    } else if (command <= SS90EL) {
      printf("%s, ", smoothTurnNames[command - SMOOTH]);
    } else {
      printf("OTHER - %02x\n", command);
    }
  }
}

