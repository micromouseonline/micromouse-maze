/***********************************************************************
 * Created by Peter Harrison on 03/07/2017.
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


#include "mazefiler.h"
#include <cstring>

MazeFiler::MazeFiler() = default;

bool endsWith(const char * src, const char * ending) {
  size_t srcLength = strlen(src);
  if (srcLength == 0) {
    return false;
  }
  size_t endLength = strlen(ending);
  if (endLength == 0) {
    return false;
  }
  if (strlen(ending) > strlen(src)) {
    return false;
  }
  size_t pos = srcLength - endLength;
  for (size_t i = 0; i < endLength; i++) {
    if (src[pos + i] != ending[i]) {
      return false;
    }
  }
  return true;
}


int MazeFiler::saveMaze(Maze * maze, char *fileName) {
  if (endsWith(fileName, ".txt")) {
    writeTextMaze(maze, fileName);
    return true;
  } else if (endsWith(fileName, ".maz")) {
    writeBinaryMaze(maze, fileName);
    return true;
  } else if (endsWith(fileName, ".cpp") || (endsWith(fileName, ".c"))) {
    writeDeclarationMaze(maze, fileName);
    return true;
  } else {
    return false;
  }
}

int MazeFiler::readMaze(Maze *maze, char *fileName) {
  FILE * fp;
  fp = fopen(fileName, "r");
  if (fp == nullptr) {
    return MAZE_FILER_NOT_FOUND;
  }
  if (readBinaryMaze(fp, maze) == 0) {
    fclose(fp);
    return MAZE_FILER_SUCCESS;
  }
  if (readTextMaze(fp, maze) == 0) {
    fclose(fp);
    return MAZE_FILER_SUCCESS;
  }
  return MAZE_FILER_READ_ERROR;
}

/* A binary maze file is stored as sequential bytes
 * in 'natural' order. That is, the first byte in the file
 * is cell 0,0 followed by the cells in the left-most column, col 0.
 * Next will be col 1 and so on. Each cell is just the raw wall data
 * as defined for internal maze storage.
 * Since the first cell read is the start cell, it must have walls
 * to its West, South and East giving it a value of 0x0E. This is the
 * only fixed-value cell in a maze
 * It is not guaranteed that the maze is stored internally as bytes.
 * nor is it guaranteed that char is a byte!!!!!
 */

int MazeFiler::readBinaryMaze(FILE *fp,  Maze * maze) {
  uint8_t buffer[1024];
  size_t bytesRead = fread(buffer, 1, 1024, fp);
  if (buffer[0] != 0x0e) {
    // probably not a binary maze
    return MAZE_FILER_BAD_FORMAT;
  }
  if (maze->numCells() > bytesRead) {
    return MAZE_FILER_BAD_FORMAT;
  }
  maze->loadFromFileData(buffer);
  return MAZE_FILER_SUCCESS;
}


/* A text maze can be stored in several formats.
 * most common is to have a single '+' or 'o' for each post
 * followed by a '-' for a horizontal wall, a space for
 * no wall and a '|' for a vertical wall.
 * Alternatively, better printing can be achieved with
 * two or three '-' characters for a horizontal wall.
 * A text maze may use a single (different) character to represent both posts and walls.
 * It is assumed these use only one character for a horizontal wall.
 * Assuming the text file is stored in the normal orientation
 * the first post is the northwest
 * This function will attempt to read all these formats.
 *
 * By the time we get here, we know that the file has at least 256 bytes so
 * it is possible to take a couple of shortcuts when examining the file
 */


int MazeFiler::readTextMaze(FILE *infile, Maze * maze) {
  int const maxLineLength = 3 + 4 * 32;
  char nsWalls[maxLineLength], ewWalls[maxLineLength];
  char *result;
  char postchar;
  char hwallchar;
  char vwallchar;
  int row;
  int col;
  int charsPerCell;
  rewind(infile);

  result = fgets(nsWalls, maxLineLength, infile);
  if (result == nullptr) {
    return MAZE_FILER_EMPTY_FILE;
  }
  unsigned long lineLength = strlen(nsWalls);
  if (lineLength < (32)) {
    //printf("unknown maze format for '%s' - first line too short\n", fname);
    return MAZE_FILER_BAD_FORMAT;
  }
  // those are the two obvious errors sorted out
  // the first character we see is the post
  postchar = nsWalls[0];
  // the next character after the post is a horizontal wall
  hwallchar = nsWalls[1];
  // where we next see a post tells us how many characters per cell
  // although we are interested only in 1 or 2
  if (nsWalls[2] == postchar) {
    charsPerCell = 2;
  } else if (nsWalls[3] == postchar) {
    charsPerCell = 3;
  } else if (nsWalls[4] == postchar) {
    charsPerCell = 4;
  } else {
    return MAZE_FILER_BAD_FORMAT;
  }
  if (!fgets(ewWalls, maxLineLength, infile)) {
    return MAZE_FILER_BAD_FORMAT;
  }

  // and the first character on the next line is a vertical wall
  vwallchar = ewWalls[0];

  // both of the wall characters must not be blank
  if ((hwallchar == ' ') || (vwallchar == ' ')) {
    //printf("The file has blank walls in the top left corner (%s)\n", fname);
    return MAZE_FILER_BAD_FORMAT;
  }


  // now we just assume the rest of the file makes sense
  // go back to the start
  rewind(infile);
  maze->clearData();
  maze->resetToEmptyMaze();
  // and begin parsing lines
  // a text maze starts top left and every row takes up two lines of text
  int mazeWidth = maze->width();
  row = maze->width() - 1;
  while (row >= 0) {
    result = fgets(nsWalls, maxLineLength, infile); /* north walls */
    if (result == nullptr) {
      return MAZE_FILER_BAD_FORMAT;
    }
    result = fgets(ewWalls, maxLineLength, infile); /* east-west walls */
    if (result == nullptr) {
      return MAZE_FILER_BAD_FORMAT;
    }
    // now just go through the lines grabbing wall information
    // we only look at the west side because the last cell always has an east wall
    for (col = 0; col < mazeWidth; col++) {
      if (nsWalls[1 + charsPerCell * col] != ' ') {
        maze->setWall(row + mazeWidth * col, NORTH);
      } else {
        maze->clearWall(row + mazeWidth * col, NORTH);
      }
      if (ewWalls[charsPerCell * col] != ' ') {
        maze->setWall(row + mazeWidth * col, WEST);
      } else {
        maze->clearWall(row + mazeWidth * col, WEST);
      }
      for (int i = 1; i < charsPerCell; i++) {
        if (ewWalls[charsPerCell * col + i] == 'G') {
          maze->setGoal(row + mazeWidth * col);
        }
      }
    }
    if (ewWalls[charsPerCell * mazeWidth] != ' ') {
      maze->setWall(row + (mazeWidth - 1) * col, EAST);
    } else {
      maze->clearWall(row + (mazeWidth - 1) * col, EAST);

    }
    row--;
  }

  // there should be one row of text left which is the south walls of the maze
  result = fgets(nsWalls, maxLineLength, infile); /* north walls */
  if (result == NULL) {
    return MAZE_FILER_BAD_FORMAT;
  }
  row = 0;
  for (col = 0; col < mazeWidth; col++) {
    if (nsWalls[1 + charsPerCell * col] != ' ') {
      maze->setWall(static_cast<uint16_t>(row + mazeWidth * col), SOUTH);
    } else {
      maze->clearWall(static_cast<uint16_t>(row + mazeWidth * col), SOUTH);
    }
  }
  return MAZE_FILER_SUCCESS;
}

int MazeFiler::writeBinaryMaze(Maze *maze, char * fileName) {
  FILE * fp;
  fp = fopen(fileName, "w");
  if (fp == nullptr) {
    return MAZE_FILER_WRITE_ERROR;
  } else {
    for (uint16_t i = 0; i < maze->numCells(); i++) {
      fputc(maze->fwalls(i), fp);
    }
    fclose(fp);
  }
  return MAZE_FILER_SUCCESS;
}

int MazeFiler::writeDeclarationMaze(Maze *maze, char * fileName) {
  FILE * fp;
  fp = fopen(fileName, "w");
  if (fp == nullptr) {
    return MAZE_FILER_WRITE_ERROR;
  } else {
    char temp[256];
    snprintf(temp, sizeof(temp), "const uint8_t %s[];\n\n", "maze");
    fputs(temp, fp);
    snprintf(temp, sizeof(temp), "const uint8_t %s[] = {\n", "maze");
    fputs(temp, fp);
    for (uint16_t x = 0; x < maze->width(); x++) {
      fputs("   ", fp);
      for (uint16_t y = 0; y < maze->width(); y++) {
        uint16_t i = x * maze->width() + y;
        snprintf(temp, sizeof(temp), "0x%02X, ", maze->fwalls(i));
        fputs(temp, fp);
      }
      fputs("\n", fp);
    }
    fputs("   };\n\n", fp);
    fclose(fp);
  }
  return MAZE_FILER_SUCCESS;
}


void MazeFiler::writeNorthWalls(Maze *maze, uint16_t y, FILE *fp) {
  for (uint16_t x = 0; x < maze->width(); x++) {
    uint16_t cell = x * maze->width() + y;
    if (maze->hasWall(cell, NORTH, OPEN_MASK)) {
      fputs("o---", fp);
    } else {
      fputs("o   ", fp);
    }
  }
  fputs("o\n", fp);
}


void MazeFiler::writeWestWalls(Maze *maze, uint16_t y, FILE *fp) {
  for (uint16_t x = 0; x < maze->width(); x++) {
    uint16_t cell = x * maze->width() + y;
    if (maze->hasWall(cell, WEST, OPEN_MASK)) {
      fputs("|", fp);
    } else {
      fputs(" ", fp);
    }
    if (cell == maze->goal()) {
      fputs(" G ", fp);
    } else {
      fputs("   ", fp);
    }
  }
  fputs("|\n", fp);
}

int MazeFiler::writeTextMaze(Maze *maze, char * fileName) {
  FILE * fp;
  fp = fopen(fileName, "w");
  if (fp == nullptr) {
    return MAZE_FILER_WRITE_ERROR;
  } else {
    for (int y = (maze->width() - 1); y >= 0; y--) {
      writeNorthWalls(maze, y, fp);
      writeWestWalls(maze, y, fp);
    }
    for (int x = 0; x < maze->width(); x++) {
      fputs("o---", fp);
    }
    fputs("o\n", fp);
    fclose(fp);
  }
  return MAZE_FILER_SUCCESS;
}
