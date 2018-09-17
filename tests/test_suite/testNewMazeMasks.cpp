/***********************************************************************
 * Created by Peter Harrison on 15/09/2018.
 * Copyright (c) 2018 Peter Harrison
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



#include "gtest/gtest.h"
#include "mazeprinter.h"
#include "mazedata.h"
#include "maze.h"
/////////////////////

#define EXPECT_ISWALL(x) EXPECT_TRUE((x) != 0)
#define EXPECT_ISEXIT(x) EXPECT_TRUE((x) == 0)

class MazeMaskTest : public ::testing::Test {
protected:
  Maze *maze;

  virtual void SetUp() {
    maze = new Maze(16);
    maze->resetToEmptyMaze();
  }

  virtual void TearDown() {
    delete maze;
  }

};

TEST_F(MazeMaskTest, xWall_Initialisation) {
  // closed maze has no exits
  // open maze is all exits
  Maze maze(16);
  maze.clearData(); // sets xWalls to all unseen exits
  for (int i = 0; i < maze.numCells(); i++) {
    EXPECT_EQ(0xF0, maze.xWalls[i]);
  }
}

TEST_F(MazeMaskTest, setWall) {
  Maze maze(16);
  maze.clearData();
  int cell = 22;
  int nextCell;
  maze.setWall(cell, NORTH);
  maze.setWall(cell, EAST);
  maze.setWall(cell, SOUTH);
  maze.setWall(cell, WEST);
  EXPECT_EQ(0x0F, maze.xWalls[cell]);

  nextCell = maze.cellNorth(cell);
  EXPECT_EQ(0xB4, maze.xWalls[nextCell]);


  nextCell = maze.cellEast(cell);
  EXPECT_EQ(0x78, maze.xWalls[nextCell]);


  nextCell = maze.cellSouth(cell);
  EXPECT_EQ(0xE1, maze.xWalls[nextCell]);

  nextCell = maze.cellWest(cell);
  EXPECT_EQ(0xD2, maze.xWalls[nextCell]);

}


TEST_F(MazeMaskTest, clearWall) {
  Maze maze(16);
  maze.clearData();
  int cell = 22;
  int nextCell;
  // we know this works
  maze.setWall(cell, NORTH);
  maze.setWall(cell, EAST);
  maze.setWall(cell, SOUTH);
  maze.setWall(cell, WEST);
  // now undo them
  maze.clearWall(cell, NORTH);
  maze.clearWall(cell, EAST);
  maze.clearWall(cell, SOUTH);
  maze.clearWall(cell, WEST);
  EXPECT_EQ(0x00, maze.xWalls[cell]);

  nextCell = maze.cellNorth(cell);
  EXPECT_EQ(0xB0, maze.xWalls[nextCell]);


  nextCell = maze.cellEast(cell);
  EXPECT_EQ(0x70, maze.xWalls[nextCell]);


  nextCell = maze.cellSouth(cell);
  EXPECT_EQ(0xE0, maze.xWalls[nextCell]);

  nextCell = maze.cellWest(cell);
  EXPECT_EQ(0xD0, maze.xWalls[nextCell]);
}


TEST_F(MazeMaskTest, isCellSeen) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  maze.setVisited(cell);
  EXPECT_EQ(0, maze.xWalls[cell]);
  EXPECT_TRUE(maze.isCellSeen(cell));
  maze.clearVisited(cell);
  EXPECT_EQ(0xF0, maze.xWalls[cell]);
  EXPECT_FALSE(maze.isCellSeen(cell));

}


TEST_F(MazeMaskTest, isWallSeen) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  EXPECT_FALSE(maze.isWallSeen(cell, NORTH));
  EXPECT_FALSE(maze.isWallSeen(cell, EAST));
  EXPECT_FALSE(maze.isWallSeen(cell, SOUTH));
  EXPECT_FALSE(maze.isWallSeen(cell, WEST));
  maze.setVisited(cell);
  EXPECT_TRUE(maze.isWallSeen(cell, NORTH));
  EXPECT_TRUE(maze.isWallSeen(cell, EAST));
  EXPECT_TRUE(maze.isWallSeen(cell, SOUTH));
  EXPECT_TRUE(maze.isWallSeen(cell, WEST));
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.isWallSeen(cell, NORTH));
  EXPECT_FALSE(maze.isWallSeen(cell, EAST));
  EXPECT_FALSE(maze.isWallSeen(cell, SOUTH));
  EXPECT_FALSE(maze.isWallSeen(cell, WEST));

}



TEST_F(MazeMaskTest, isExit) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  maze.clearVisited(cell);
  EXPECT_TRUE(maze.isExit(cell, NORTH));
  EXPECT_TRUE(maze.isExit(cell, EAST));
  EXPECT_TRUE(maze.isExit(cell, SOUTH));
  EXPECT_TRUE(maze.isExit(cell, WEST));
  maze.setVisited(cell);
  EXPECT_TRUE(maze.isExit(cell, NORTH));
  EXPECT_TRUE(maze.isExit(cell, EAST));
  EXPECT_TRUE(maze.isExit(cell, SOUTH));
  EXPECT_TRUE(maze.isExit(cell, WEST));
  maze.setWall(cell, NORTH);
  EXPECT_FALSE(maze.isExit(cell, NORTH));
  maze.setVisited(cell);
  EXPECT_FALSE(maze.isExit(cell, NORTH));
}


TEST_F(MazeMaskTest, isWall) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.isWall(cell, NORTH));
  EXPECT_FALSE(maze.isWall(cell, EAST));
  EXPECT_FALSE(maze.isWall(cell, SOUTH));
  EXPECT_FALSE(maze.isWall(cell, WEST));
  maze.setVisited(cell);
  EXPECT_FALSE(maze.isWall(cell, NORTH));
  EXPECT_FALSE(maze.isWall(cell, EAST));
  EXPECT_FALSE(maze.isWall(cell, SOUTH));
  EXPECT_FALSE(maze.isWall(cell, WEST));
  maze.setWall(cell, NORTH);
  EXPECT_TRUE(maze.isWall(cell, NORTH));
  maze.setVisited(cell);
  EXPECT_TRUE(maze.isWall(cell, NORTH));
}


TEST_F(MazeMaskTest, isSeenWall) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.isSeenWall(cell, NORTH));
  EXPECT_FALSE(maze.isSeenWall(cell, EAST));
  EXPECT_FALSE(maze.isSeenWall(cell, SOUTH));
  EXPECT_FALSE(maze.isSeenWall(cell, WEST));
  maze.setVisited(cell);
  EXPECT_FALSE(maze.isSeenWall(cell, NORTH));
  EXPECT_FALSE(maze.isSeenWall(cell, EAST));
  EXPECT_FALSE(maze.isSeenWall(cell, SOUTH));
  EXPECT_FALSE(maze.isSeenWall(cell, WEST));
  maze.setWall(cell, NORTH);
  EXPECT_TRUE(maze.isSeenWall(cell, NORTH));
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.isSeenWall(cell, NORTH));
}


TEST_F(MazeMaskTest, isSeenExit) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.isSeenExit(cell, NORTH));
  EXPECT_FALSE(maze.isSeenExit(cell, EAST));
  EXPECT_FALSE(maze.isSeenExit(cell, SOUTH));
  EXPECT_FALSE(maze.isSeenExit(cell, WEST));
  maze.setVisited(cell);
  EXPECT_TRUE(maze.isSeenExit(cell, NORTH));
  EXPECT_TRUE(maze.isSeenExit(cell, EAST));
  EXPECT_TRUE(maze.isSeenExit(cell, SOUTH));
  EXPECT_TRUE(maze.isSeenExit(cell, WEST));
  maze.clearWall(cell, NORTH);
  EXPECT_TRUE(maze.isSeenExit(cell, NORTH));
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.isSeenExit(cell, NORTH));
}
