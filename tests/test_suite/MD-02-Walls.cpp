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
#include "maze.h"


class MD_02_Walls : public ::testing::Test {
protected:
  CellWalls walls;

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

TEST_F(MD_02_Walls, cell_walls_initial_values) {
  EXPECT_EQ(UNKNOWN, walls.north);
  EXPECT_EQ(UNKNOWN, walls.east);
  EXPECT_EQ(UNKNOWN, walls.south);
  EXPECT_EQ(UNKNOWN, walls.west);
}

TEST_F(MD_02_Walls, cell_walls_as_byte) {
  EXPECT_EQ(0, walls.as_legacy_byte());
  walls.north = EXIT;
  walls.east = WALL;
  walls.south = UNKNOWN;
  walls.west = VIRTUAL;
  EXPECT_EQ(0b00000010, walls.as_legacy_byte());
  EXPECT_EQ(0b11100100, walls.as_byte());
}

TEST_F(MD_02_Walls, set_walls_from_legacy_byte) {
  walls.set_from_legacy_byte((0b00001100));
  EXPECT_EQ(EXIT, walls.north);
  EXPECT_EQ(EXIT, walls.east);
  EXPECT_EQ(WALL, walls.south);
  EXPECT_EQ(WALL, walls.west);
}

TEST_F(MD_02_Walls, test_for_unknowns) {
  EXPECT_TRUE(walls.has_unknowns());
  walls.set_from_legacy_byte((0b00001100));
  EXPECT_FALSE(walls.has_unknowns());
}



