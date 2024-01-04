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

TEST(MD_04_Direction, MazeHeading_defaultValue_isNORTH) {
  Maze maze(16);
  maze.reset_to_empty();
  for (int i = 0; i < maze.numCells(); i++) {
    EXPECT_EQ(DIR_N, maze.get_direction(i));
  }
}

TEST(MD_04_Direction, MazeSetDirection_ReturnSetValue) {
  Maze maze(16);
  maze.reset_to_empty();
  maze.set_direction(0x33, DIR_E);
  EXPECT_EQ(DIR_E, maze.get_direction(0x33));
  maze.set_direction(0x33, DIR_S);
  EXPECT_EQ(DIR_S, maze.get_direction(0x33));
  maze.set_direction(0x33, DIR_W);
  EXPECT_EQ(DIR_W, maze.get_direction(0x33));
  maze.set_direction(0x33, DIR_N);
  EXPECT_EQ(DIR_N, maze.get_direction(0x33));
}

TEST(MD_04_Direction, DirectionGetLeftFrom) {

  EXPECT_EQ(DIR_W, left_from[DIR_N]);
  EXPECT_EQ(DIR_S, left_from[DIR_W]);
  EXPECT_EQ(DIR_E, left_from[DIR_S]);
  EXPECT_EQ(DIR_N, left_from[DIR_E]);
}


TEST(MD_04_Direction, DirectionGetRightFrom) {
  EXPECT_EQ(DIR_E, right_from[DIR_N]);
  EXPECT_EQ(DIR_S, right_from[DIR_E]);
  EXPECT_EQ(DIR_W, right_from[DIR_S]);
  EXPECT_EQ(DIR_N, right_from[DIR_W]);

}

TEST(MD_04_Direction, Behind) {
  EXPECT_EQ(DIR_S, behind[DIR_N]);
  EXPECT_EQ(DIR_W, behind[DIR_E]);
  EXPECT_EQ(DIR_N, behind[DIR_S]);
  EXPECT_EQ(DIR_E, behind[DIR_W]);
}


TEST(MD_04_Direction, Direction_change) {
  for (Direction fromDir : cardinals) {
    for (Direction toDir : cardinals) {
      uint8_t newDir = Maze::get_direction_change(fromDir, toDir);
      EXPECT_EQ(newDir, (toDir - fromDir) & 7);
    }
  }
}


