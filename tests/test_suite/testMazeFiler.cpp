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
#include "mazefiler.h"
#include "mazeprinter.h"



class TestMazeFiler : public ::testing::Test {
protected:
  Maze *maze16;
  Maze *maze32;


  virtual void SetUp() {
    maze16 = new Maze(16);
    maze16->reset_to_empty();
    maze32 = new Maze(32);
    maze32->reset_to_empty();

  }

  virtual void TearDown() {
    delete maze16;
    delete maze32;
  }

};

TEST_F(TestMazeFiler, LoadClassicTextFile) {
  MazeFiler filer;
  char name[] = "mazefiles/classic/taiwan2018cef.txt";
  EXPECT_EQ(MazeFiler::MAZE_SUCCESS, filer.readMaze(maze16, name));
  EXPECT_EQ(16, maze16->width());
  EXPECT_EQ(4, maze16->goalAreaSize());
  EXPECT_TRUE(maze16->goalContains(maze16->cellID(7, 7)));
  EXPECT_TRUE(maze16->goalContains(maze16->cellID(7, 8)));
  EXPECT_TRUE(maze16->goalContains(maze16->cellID(8, 7)));
  EXPECT_TRUE(maze16->goalContains(maze16->cellID(8, 8)));
  EXPECT_TRUE(maze16->goalContains(0x77));
  EXPECT_TRUE(maze16->goalContains(0x78));
  EXPECT_TRUE(maze16->goalContains(0x87));
  EXPECT_TRUE(maze16->goalContains(0x88));

}
TEST_F(TestMazeFiler, LoadHalfSizeTextFile) {
  MazeFiler filer;
  char name[] = "mazefiles/halfsize/japan2013hef.txt";
  EXPECT_EQ(0, filer.readMaze(maze16, name));
  EXPECT_EQ(32, maze16->width());
  EXPECT_EQ(9, maze16->goalAreaSize());
  EXPECT_TRUE(maze16->goalContains(maze16->cellID(6, 5)));
  EXPECT_TRUE(maze16->goalContains(maze16->cellID(7, 6)));
  EXPECT_TRUE(maze16->goalContains(maze16->cellID(8, 7)));
}

