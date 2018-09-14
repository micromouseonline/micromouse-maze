/***********************************************************************
 * Created by Peter Harrison on 15/12/2017.
 * Copyright (c) 2017 Peter Harrison
 *
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
 **************************************************************************/


#include "compiler.h"
#include "commandnames.h"
#include <cassert>

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


void makeDiagonalCommands(const char *src, const uint16_t maxLength, uint8_t *commands) {
  int runLength = 0;
  int p = 0;
  pathgen_state_t state = PathInit;
  assert(maxLength > 2);
  while (state != PathFinish) {
    if (runLength > 31) { // MAGIC: maximum for hald-size maze
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
 * It is suitable for moving the mouse more rapidly in the maze while
 * exploring but where it is not felt safe to use diagonals
 */
void makeSmoothCommands(const char *src, const uint16_t maxLength, uint8_t *commands) {
  int runLength = 0; // a counter for the number of cells to be crossed
  int p = 0;
  pathgen_state_t state = PathInit;
  while (state != PathFinish) {
    if (runLength >= 31) { // MAGIC: maximum for hald-size maze
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
void makeInPlaceCommands(const char *src, const uint16_t maxLength, uint8_t *commands) {
  int p = 0;
  int runLength = 0;
  unsigned char cmd = CMD_STOP;
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
        if (runLength >= 31) { // MAGIC: maximum for hald-size maze
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
