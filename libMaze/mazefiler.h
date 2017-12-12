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


#ifndef MICROMOUSE_MAZE_MAZEFILER_H
#define MICROMOUSE_MAZE_MAZEFILER_H

#include "maze.h"
#include <cstdio>

class MazeFiler {
public:

  typedef enum  {
    MAZE_SUCCESS = 0,
    MAZE_READ_ERROR ,
    MAZE_WRITE_ERROR ,
  } MazeFileType;

  MazeFiler();

  int saveMaze(Maze * maze, char *fileName);
  int readMaze(Maze * maze, char * fileName);

  int readBinaryMaze(FILE * fp,  Maze * maze);
  int readTextMaze(FILE * fp, Maze * maze);
  // COPOUT: reading a c declaration is not easy so it is not here.
  int writeBinaryMaze(Maze *maze, char *fileName);
  int writeDeclarationMaze(Maze *maze, char * fileName);
  int writeTextMaze(Maze * maze, char * filename);

private:
  void writeNorthWalls(Maze *maze, uint16_t y, FILE *fp);
  void writeWestWalls(Maze *maze, uint16_t y, FILE *fp);

};

#endif //MICROMOUSE_MAZE_MAZEFILER_H
