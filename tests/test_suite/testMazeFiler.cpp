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
#include "mazedata.h"
#include "mazeprinter.h"

class MazeFilerTest : public ::testing::Test {
protected:
  Maze *classicMaze;
  Maze *halfSizeMaze;


  virtual void SetUp() {
    classicMaze = new Maze(16);
    classicMaze->resetToEmptyMaze();
    halfSizeMaze = new Maze(32);
    halfSizeMaze->resetToEmptyMaze();
  }

  virtual void TearDown() {
    delete classicMaze;
    delete halfSizeMaze;
  }

  virtual void copyMaze(Maze *maze, const uint8_t *mazeData) const {
    if (!maze || !mazeData) {
      return;
    }
    maze->loadFromFileData(mazeData);
  }
};


TEST_F(MazeFilerTest, LoadClassicMazeFileNotFound) {
  char fileName[] = "mazefiles/classic/missing.txt";
  MazeFiler filer;
  Maze testMaze(16);
  int err = filer.readMaze(&testMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_NOT_FOUND, err);
}

TEST_F(MazeFilerTest, LoadClassicMazeFileFound) {
  char fileName[] = "mazefiles/classic/empty.txt";
  MazeFiler filer;
  Maze testMaze(16);
  int err = filer.readMaze(&testMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
}


TEST_F(MazeFilerTest, LoadClassicMazeFromTextFile) {
  char fileName[] = "mazefiles/classic/alljapan-028-2007-exp-fin.txt";
  MazeFiler filer;
  Maze testMaze(16);
  copyMaze(classicMaze, japan2007ef);
  int err = filer.readMaze(&testMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  for (uint16_t cell = 0; cell < classicMaze->numCells(); cell++) {
    EXPECT_EQ(classicMaze->fwalls(cell), testMaze.fwalls(cell));
    EXPECT_TRUE(testMaze.isVisited(cell));
  }
}



TEST_F(MazeFilerTest, LoadClassicMazeFromBinaryFile) {
  char fileName[] = "japan2007ef_classic.maz";
  MazeFiler filer;
  Maze testMaze(16);
  copyMaze(classicMaze, japan2007ef);
  int err = filer.readMaze(&testMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);

  for (uint16_t cell = 0; cell < classicMaze->numCells(); cell++) {
    EXPECT_EQ(classicMaze->fwalls(cell), testMaze.fwalls(cell));
    EXPECT_TRUE(testMaze.isVisited(cell));
  }
}



TEST_F(MazeFilerTest, SaveClassicMazeToTextFile) {
  char fileName[] = "japan2007ef_classic.txt";
  MazeFiler filer;
  Maze testMaze(16);
  copyMaze(classicMaze, japan2007ef);
  int err = filer.writeTextMaze(classicMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  // now load it back in and compare
  err = filer.readMaze(&testMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  for (uint16_t cell = 0; cell < classicMaze->numCells(); cell++) {
    EXPECT_EQ(classicMaze->fwalls(cell), testMaze.fwalls(cell));
  }
}



TEST_F(MazeFilerTest, SaveClassicMazeToBinaryFile) {
  char fileName[] = "japan2007ef_classic.maz";
  MazeFiler filer;
  Maze testMaze(16);
  copyMaze(classicMaze, japan2007ef);
  int err = filer.writeBinaryMaze(classicMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  // now load it back in and compare
  err = filer.readMaze(&testMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  for (uint16_t cell = 0; cell < classicMaze->numCells(); cell++) {
    EXPECT_EQ(classicMaze->fwalls(cell), testMaze.fwalls(cell));
  }
}





TEST_F(MazeFilerTest, SaveClassicMazeToDeclarations) {
  char fileName[] = "japan2007ef_classic.c";
  MazeFiler filer;
  copyMaze(classicMaze, japan2007ef);
  int err = filer.writeDeclarationMaze(classicMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  // need to visually inspect the file. Sorry - can't think of a good way to test
}



// half size tests

TEST_F(MazeFilerTest, LoadHalfSizeMazeFromTextFile) {
  char fileName[] = "mazefiles/halfsize/japan2014ef.txt";
  MazeFiler filer;
  Maze * testMaze = new Maze(32);

  copyMaze(halfSizeMaze, japan2014ef_half);
  int err = filer.readMaze(testMaze, fileName);
  EXPECT_EQ((int)MazeFiler::MAZE_FILER_SUCCESS, err);
  halfSizeMaze->setGoal(testMaze->goal());

  for (uint16_t cell = 0; cell < halfSizeMaze->numCells(); cell++) {
    EXPECT_EQ(halfSizeMaze->fwalls(cell), testMaze->fwalls(cell));
    EXPECT_TRUE(testMaze->isVisited(cell));
  }
}



TEST_F(MazeFilerTest, LoadHalfSizeMazeFromBinaryFile) {
  char fileName[] = "japan2014ef_half.maz";
  MazeFiler filer;
  Maze * testMaze = new Maze(32);
  copyMaze(halfSizeMaze, japan2014ef_half);
  int err = filer.readMaze(testMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);

  for (uint16_t cell = 0; cell < halfSizeMaze->numCells(); cell++) {
    EXPECT_EQ(halfSizeMaze->fwalls(cell), testMaze->fwalls(cell));
    EXPECT_TRUE(testMaze->isVisited(cell));
  }
}



TEST_F(MazeFilerTest, SaveHalfSizeMazeToTextFile) {
  char fileName[] = "japan2014ef_half.txt";
  MazeFiler filer;
  Maze testMaze(32);
  copyMaze(halfSizeMaze, japan2014ef_half);
  int err = filer.writeTextMaze(halfSizeMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  // now load it back in and compare
  err = filer.readMaze(&testMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  for (uint16_t cell = 0; cell < halfSizeMaze->numCells(); cell++) {
    EXPECT_EQ(halfSizeMaze->fwalls(cell), testMaze.fwalls(cell));
  }
}



TEST_F(MazeFilerTest, SaveHalfSizeMazeToBinaryFile) {
  char fileName[] = "japan2014ef_half.maz";
  MazeFiler filer;
  Maze testMaze(32);
  copyMaze(halfSizeMaze, japan2014ef_half);
  int err = filer.writeBinaryMaze(halfSizeMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  // now load it back in and compare
  err = filer.readMaze(&testMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  for (uint16_t cell = 0; cell < halfSizeMaze->numCells(); cell++) {
    EXPECT_EQ(halfSizeMaze->fwalls(cell), testMaze.fwalls(cell));
  }
}



TEST_F(MazeFilerTest, SavehalfsizeMazeToDeclarations) {
  char fileName[] = "japan2014ef_half.c";
  MazeFiler filer;
  copyMaze(halfSizeMaze, japan2014ef_half);
  int err = filer.writeDeclarationMaze(halfSizeMaze, fileName);
  EXPECT_EQ(MazeFiler::MAZE_FILER_SUCCESS, err);
  // need to visually inspect the file. Sorry - can't think of a good way to test
}




