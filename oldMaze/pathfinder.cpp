/*
Copyright (c) 2014 Peter Harrison

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */
//#include "globals.h"
#include "commands.h"
#include "pathfinder.h"
#include <stdio.h>

unsigned char commandList[500];
unsigned char tempList[500];

const char *inPlaceTurnNames[] = {
    "IP45R",
    "IP45L",
    "IP90R",
    "IP90L",
    "IP135R",
    "IP135L",
    "IP180R",
    "IP180L",
};

const char *smoothTurnNames[] = {
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

// run through a simple string creating a list of mouse commands from a
// shorthand string containing characters e.g. FRFLFFFX...
// run length encode straights and generate in-place turns at each corner
// note that the input string is expecting  to see an 'F' after every turn


void parseCommandString(uint8_t *commands, const char *s) {
  enum {
    RUNNING = 0,
    TURNING = 1,
    STOPPING
  };
  int p;
  int state;
  int done;
  unsigned char cmd;
  cmd = FWD0;
  p = 0;
  done = 0;

  do {
    char c = *s++;
    if (c == 'B') {
      commands[p++] = CMD_BEGIN;
      cmd = FWD0;
    } else if (c == 'F') {
      cmd++;
    } else if (c == 'L') {
      commands[p++] = cmd;
      commands[p++] = IP90L;
      cmd = FWD1;
    } else if (c == 'R') {
      commands[p++] = cmd;
      commands[p++] = IP90R;
      cmd = FWD1;
    } else if (c == 'S') {
      commands[p++] = cmd;
      commands[p++] = STOP;
    } else if (c == 'X') {
      commands[p++] = cmd;
      commands[p++] = CMD_END;
      done = 1;
    }
    if (p > 255) {
      done = 1;
    }
    if (c == 0) {
      done = 1;
    }
  } while (!done);
}

void listCommands(unsigned char *commandList) {
  char done = 0;
  while (!done) {
    unsigned char command = *commandList++;
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

/*
 * Generate a command sequence from a string input. The generated path will
 * allow a micromouse to move diagonally in the maze.
 * The input string is a null-terminated array of characters.
 *
 * Passing in an empty string will generate an error.
 *
 * Only characters from the set FLRS are accepted. Other characters
 * in the input array will cause an error command to be emitted.
 *
 * The output is performed by the function *pCommands++ = () which adds a single
 * command to the command list. Modify *pCommands++ = () to do something else
 * with the generated results.
 *
 * If there is an error during conversion, the output command list will
 * still contain valid output up to the point where the error is detected.
 *
 * A single pass is taken through the input string and commands are
 * generated as soon as there is an unambiguous state for the command.
 *
 * The input string will typically be generated form the maze solver data
 * and each valid character in that string has the following meaning:
 *   F : move forward one cell orthogonally
 *   R : perform an in-place right turn of 90 degrees
 *   L : perform an in-place left turn of 90 degrees
 *   S : Stop moving in this cell. This is the goal.
 *
 * Refer to the associated state chart for a view of how the states are
 * related to each other.
 *
 * NOTE that the output command list will be limited in size. The function
 * will continue to generate output values as long as there is valid input.
 * It knows nothing about the size of available output.
 *
 * The states have simple numbers rather than an enum since I could not
 * think of good names to use. Since then, I have but this version
 * maintains compatibility with the MINOS 2014 slides. Possible names are
 * shown as a comment for each state.
 */

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

void makeDiagonalPath(const char *src, unsigned char *pCommands) {
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

void makeSmoothPath(const char *src, unsigned char *pCommands) {
  int x = 0; // a counter for the number of cells to be crossed
  pathgen_state_t state = PathInit;
  while (state != PathFinish) {
    char c = *src++;
//    printf("%c",c);
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





// =======================================================================
// make a command list starting at currentCell heading shead to targetCell
// =======================================================================

/***
  This is given the starting cell, the finishing cell and the start heading
  of the mouse and will fill commandList with a series of instructions to
  get the mouse to the target.

  The return value is the heading that the mouse will have when the move
  finishes. That is used to orient the mouse after the run because command
  following does not bother to keep track of heading. If the mouse is lost,
  it returns a value of -1.

  As a side-effect, the mouse will update the value of the global variable
  solved to a zero if the maze is unsolved or 1 if it is solved

  While generating the path, a check is made to see if a cell on that
  path is unvisited. Should the path go through such a cell, the maze is
  marked as unsolved and a record of that cell is kept for use by the
  searcher in the global firstUnvisitedCell.

 **/





// TODO: move the path generators out to another module


// =======================================================================
// compilation of slanted travelling command list
// =======================================================================

void diagonals(void) {
  unsigned char x = 0;
  int cptr = 0;
  int tptr = 0;
  unsigned char cmd = commandList[cptr];
  // always copy the first command over.
  tempList[tptr++] = cmd;
  // if it is a turn, copy it and skip past it. That is, always start the
  // sequence translation with a straight.
  if ((cmd == IP90R) || (cmd == IP90L)) {
    cptr++;
    cmd = commandList[cptr];
    tempList[tptr++] = cmd;
  }
  while (1) {
    unsigned char c0, c1, c2, c3, c4, c5, c6;
    // ========== command input ==========
    c0 = commandList[cptr + 0];
    c1 = commandList[cptr + 1];
    c2 = commandList[cptr + 2];
    c3 = commandList[cptr + 3];
    c4 = commandList[cptr + 4];
    c5 = commandList[cptr + 5];
    c6 = commandList[cptr + 6];
    if ((c1 > FWD1) && (c1 < FWD16)) {
      tempList[tptr++] = c1;
      cptr = cptr + 1;
      // ========== the right lane modification ========== *
    } else if ((c0 > FWD1) && (c0 < FWD16) && (c1 == IP90R) && (c2 == FWD1) && (c3 == IP90L) && (c4 > FWD1) && (c4 < FWD16)) {
      tempList[tptr++] = SD45R;
      tempList[tptr++] = DIA2;
      tempList[tptr++] = DS45L;
      cptr = cptr + 3;
      // ========== the left lane modification ========== *
    } else if ((c0 > FWD1) && (c0 < FWD16) && (c1 == IP90L) && (c2 == FWD1) && (c3 == IP90R) && (c4 > FWD1) && (c4 < FWD16)) {
      tempList[tptr++] = SD45L;
      tempList[tptr++] = DIA2;
      tempList[tptr++] = DS45R;
      cptr = cptr + 3;
      // ===== straight advancing -> the right 45 -> tilt ===== *
    } else if ((c0 < FWD16) && (c1 == IP90R) && (c2 == FWD1) && (c3 == IP90L)) {
      tempList[tptr++] = SD45R;
      x = DIA1;
      cptr = cptr + 1;
      // ===== straight advancing -> the left 45 -> tilt ===== *
    } else if ((c0 < FWD16) && (c1 == IP90L) && (c2 == FWD1) && (c3 == IP90R)) {
      tempList[tptr++] = SD45L;
      x = DIA1;
      cptr = cptr + 1;
      // ===== straight advancing -> the right 135 -> tilt ===== *
    } else if ((c0 < FWD16) && (c1 == IP90R) && (c2 == FWD1) && (c3 == IP90R) && (c4 == FWD1) && (c5 == IP90L)) {
      tempList[tptr++] = SD135R;
      x = DIA1;
      cptr = cptr + 3;
      // ===== straight advancing -> the left 135 -> tilt ===== *
    } else if ((c0 < FWD16) && (c1 == IP90L) && (c2 == FWD1) && (c3 == IP90L) && (c4 == FWD1) && (c5 == IP90R)) {
      tempList[tptr++] = SD135L;
      x = DIA1;
      cptr = cptr + 3;
      // ===== tilt -> the right 45 -> straight advancing ===== *
    } else if ((c0 == IP90L) && (c1 == FWD1) && (c2 == IP90R) && (c3 > FWD1) && (c3 < FWD16)) {
      x = x + 1;
      tempList[tptr++] = x;
      tempList[tptr++] = DS45R;
      cptr = cptr + 2;
      // ===== tilt -> the left 45 -> straight advancing ===== *
    } else if ((c0 == IP90R) && (c1 == FWD1) && (c2 == IP90L) && (c3 > FWD1) && (c3 < FWD16)) {
      x = x + 1;
      tempList[tptr++] = x;
      tempList[tptr++] = DS45L;
      cptr = cptr + 2;
      // ===== tilt -> the right 135 -> straight advancing ===== *
    } else if ((c0 == IP90L) && (c1 == FWD1) && (c2 == IP90R) && (c3 == FWD1) && (c4 == IP90R) && (c5 > FWD1) && (c5 < FWD16)) {
      x = x + 1;
      tempList[tptr++] = x;
      tempList[tptr++] = DS135R;
      cptr = cptr + 4;
      // ===== tilt -> the left 135 -> straight advancing ===== *
    } else if ((c0 == IP90R) && (c1 == FWD1) && (c2 == IP90L) && (c3 == FWD1) && (c4 == IP90L) && (c5 > FWD1) && (c5 < FWD16)) {
      x = x + 1;
      tempList[tptr++] = x;
      tempList[tptr++] = DS135L;
      cptr = cptr + 4;
      // ===== tilt -> the right 90 -> tilt ===== *
    } else if ((c0 == IP90L) && (c1 == FWD1) && (c2 == IP90R) && (c3 == FWD1) && (c4 == IP90R) && (c5 == FWD1) && (c6 == IP90L)) {
      tempList[tptr++] = x + 1;
      tempList[tptr++] = DD90R;
      x = DIA1;
      cptr = cptr + 4;
      // ===== tilt -> the left 90 -> tilt ===== *
    } else if ((c0 == IP90R) && (c1 == FWD1) && (c2 == IP90L) && (c3 == FWD1) && (c4 == IP90L) && (c5 == FWD1) && (c6 == IP90R)) {
      tempList[tptr++] = x + 1;
      tempList[tptr++] = DD90L;
      x = DIA1;
      cptr = cptr + 4;
      // ===== tilt -> the right 45 -> straight advancing (goal) ===== *
    } else if ((c0 == IP90L) && (c1 == FWD1) && (c2 == IP90R) && (c3 == FWD1) && (c4 == STOP)) {
      // TODO BUG here: turn exits too far into final cell and the mouse has to go backwards!!!
      x = x + 1;
      tempList[tptr++] = x;
      tempList[tptr++] = DS45R;
      cptr = cptr + 2;
      // ===== tilt -> the left 45 -> straight advancing (goal) ===== *
    } else if ((c0 == IP90R) && (c1 == FWD1) && (c2 == IP90L) && (c3 == FWD1) && (c4 == STOP)) {
      x = x + 1;
      tempList[tptr++] = x;
      tempList[tptr++] = DS45L;
      cptr = cptr + 2;
      // ===== tilt -> the right 135 -> straight advancing (goal) ===== *
    } else if ((c0 == IP90L) && (c1 == FWD1) && (c2 == IP90R) && (c3 == FWD1) && (c4 == IP90R) && (c5 == FWD1) && (c6 == STOP)) {
      x = x + 1;
      tempList[tptr++] = x;
      tempList[tptr++] = DS135R;
      cptr = cptr + 4;
      // ===== tilt -> the left 135 -> straight advancing (goal) ===== *
    } else if ((c0 == IP90R) && (c1 == FWD1) && (c2 == IP90L) && (c3 == FWD1) && (c4 == IP90L) && (c5 == FWD1) && (c6 == STOP)) {
      x = x + 1;
      tempList[tptr++] = x;
      tempList[tptr++] = DS135L;
      cptr = cptr + 4;
      // ========== tilt ========== *
    } else if ((c0 == IP90R) && (c1 == FWD1) && (c2 == IP90L) && (c3 == FWD1) && (c4 == IP90R)) {
      x = x + 1;
      cptr = cptr + 2;
      // ========== tilt ========== *
    } else if ((c0 == IP90L) && (c1 == FWD1) && (c2 == IP90R) && (c3 == FWD1) && (c4 == IP90L)) {
      x = x + 1;
      cptr = cptr + 2;
    } else {
      tempList[tptr++] = c1;
      cptr++;
    }
    if (c1 == (uint8_t) CMD_STOP) {
      break;
    }
  }
  tempList[tptr++] = CMD_STOP;
  tempList[tptr++] = CMD_END;
  for (int i = 0; i < 255; i++) {
    commandList[i] = tempList[i];
  }
}

void fastTurns(void) {
  unsigned char cmd;
  int cp = 0;
  int tp = 0;
  // sort out what to do if the first command is a turn
  // this should not happen?
  // we can always turn to face north when
  // entering the start square.
  // in the center block - what happens if we search for
  // other center block cells? need to be sure we have been in all four really.
  cmd = commandList[cp];
  tempList[tp++] = cmd; // just copy the first command
  if ((cmd == IP90R) || (cmd == IP90L)) {  // if it was a turn-in-place
    cp = cp + 1; // copy the next one too
    cmd = commandList[cp];
    tempList[tp++] = cmd;
  }
  while (1) {
    unsigned char c0, c1, c2, c3, c4;
    // make a look-ahead list
    c0 = commandList[cp + 0];
    c1 = commandList[cp + 1];
    c2 = commandList[cp + 2];
    c3 = commandList[cp + 3];
    c4 = commandList[cp + 4];
    if ((c1 > FWD1) && (c1 < FWD16)) {  // we already have c0 - if it was a turn, copy
      // simple straights
      tempList[tp++] = c1; // the subsequent straight
      cp = cp + 1;
    } else if ((c0 >= FWD1) && (c0 < FWD16) && (c1 == SS90ER) && (c2 == FWD1) && (c3 == SS90ER) && (c4 >= FWD1) && (c4 < FWD16)) {
      // 2 or more straights each side of two rights
      tempList[tp++] = SS180R; // all in one 180 degree turn
      cp = cp + 3;
    } else if ((c0 >= FWD1) && (c0 < FWD16) && (c1 == SS90EL) && (c2 == FWD1) && (c3 == SS90EL) && (c4 >= FWD1) && (c4 < FWD16)) {
      // 2 or more straights each side of two lefts
      tempList[tp++] = SS180L; // all in one 180 degree turn
      cp = cp + 3;
    } else if ((c0 >= FWD1) && (c0 < FWD16) && (c1 == SS90ER) && (c2 >= FWD2) && (c2 < FWD16)) {
      // a right turn with 3 or more straights either side
      tempList[tp++] = SS90FR; // corner cutting turn
      cp = cp + 1;
    } else if ((c0 >= FWD1) && (c0 < FWD16) && (c1 == SS90EL) && (c2 >= FWD2) && (c2 < FWD16)) {
      // a left turn with 3 or more straights either side
      tempList[tp++] = SS90FL; // corner cutting turn
      cp = cp + 1;
    } else {
      // everything else
      tempList[tp++] = c1; // just copy it
      cp++;
    };
    if (c1 == CMD_STOP) {
      break; // there had better be a CMD_STOP in there soewhere
    }
  }
  tempList[tp++] = CMD_STOP; // dont forget to put it in the new list
  tempList[tp++] = CMD_END; // dont forget to put it in the new list
  for (int i = 0; i < 255; i++) { // put these back in the commandList
    commandList[i] = tempList[i]; // this can actually be done in-place
  }
}

void smoothTurns(void) {
  uint8_t *cp = commandList;
  while (*cp) {
    if (*cp == IP90R) {
      *cp = SS90ER;
    }
    if (*cp == IP90L) {
      *cp = SS90EL;
    }
    cp++;
  }
}

