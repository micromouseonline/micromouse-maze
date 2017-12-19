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


#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"
#include "maze.h"

/*
 * test the ability of the libMaze to store direction information
 */

TEST (Direction, MazeHeading_defaultValue_isNORTH)
{
  Maze maze(16);
  maze.resetToEmptyMaze();
  for(int i = 0; i < maze.numCells(); i++){
    EXPECT_EQ(NORTH, maze.direction(i));
  }
}

TEST (Direction, MazeSetDirection_ReturnSetValue)
{
  Maze maze(16);
  maze.resetToEmptyMaze();
  maze.setDirection(0x33, EAST);
  EXPECT_EQ(EAST, maze.direction(0x33));
  maze.setDirection(0x33, SOUTH);
  EXPECT_EQ(SOUTH, maze.direction(0x33));
  maze.setDirection(0x33, WEST);
  EXPECT_EQ(WEST, maze.direction(0x33));
  maze.setDirection(0x33, NORTH);
  EXPECT_EQ(NORTH, maze.direction(0x33));
}

TEST (Direction, DirectionGetLeftFrom)
{

  EXPECT_EQ (WEST, Maze::leftOf(NORTH));
  EXPECT_EQ (SOUTH, Maze::leftOf (WEST));
  EXPECT_EQ (EAST, Maze::leftOf(SOUTH));
  EXPECT_EQ (NORTH, Maze::leftOf(EAST));
}


TEST (Direction, DirectionGetRightFrom)
{
  EXPECT_EQ (EAST, Maze::rightOf (NORTH));
  EXPECT_EQ (SOUTH, Maze::rightOf  (EAST));
  EXPECT_EQ (WEST, Maze::rightOf  (SOUTH));
  EXPECT_EQ (NORTH, Maze::rightOf  (WEST));

}

TEST (Direction, Behind)
{
  EXPECT_EQ (SOUTH, Maze::behind (NORTH));
  EXPECT_EQ (WEST, Maze::behind (EAST));
  EXPECT_EQ (NORTH, Maze::behind (SOUTH));
  EXPECT_EQ (EAST, Maze::behind (WEST));
}


TEST (Direction, DifferenceBetween){
  for(uint8_t fromDir = 0; fromDir < 4; fromDir++){
    for(uint8_t toDir = 0; toDir <  4; toDir++){
      uint8_t newDir = Maze::differenceBetween(fromDir,toDir);
      EXPECT_EQ(newDir,(toDir-fromDir)&3);
    }
  }
}


