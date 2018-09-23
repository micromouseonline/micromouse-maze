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
    EXPECT_EQ(0xF0, maze.getXWalls(i));
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
  EXPECT_EQ(0x0F, maze.getXWalls(cell));

  nextCell = maze.cellNorth(cell);
  EXPECT_EQ(0xB4, maze.getXWalls(nextCell));


  nextCell = maze.cellEast(cell);
  EXPECT_EQ(0x78, maze.getXWalls(nextCell));


  nextCell = maze.cellSouth(cell);
  EXPECT_EQ(0xE1, maze.getXWalls(nextCell));

  nextCell = maze.cellWest(cell);
  EXPECT_EQ(0xD2, maze.getXWalls(nextCell));

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
  EXPECT_EQ(0x00, maze.getXWalls(cell));

  nextCell = maze.cellNorth(cell);
  EXPECT_EQ(0xB0, maze.getXWalls(nextCell));


  nextCell = maze.cellEast(cell);
  EXPECT_EQ(0x70, maze.getXWalls(nextCell));


  nextCell = maze.cellSouth(cell);
  EXPECT_EQ(0xE0, maze.getXWalls(nextCell));

  nextCell = maze.cellWest(cell);
  EXPECT_EQ(0xD0, maze.getXWalls(nextCell));
}


TEST_F(MazeMaskTest, isVisited) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  maze.setVisited(cell);
  EXPECT_EQ(0, maze.getXWalls(cell));
  EXPECT_TRUE(maze.isVisited(cell));
  maze.clearVisited(cell);
  EXPECT_EQ(0xF0, maze.getXWalls(cell));
  EXPECT_FALSE(maze.isVisited(cell));

}


TEST_F(MazeMaskTest, isSeen) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  EXPECT_FALSE(maze.isSeen(cell, NORTH));
  EXPECT_FALSE(maze.isSeen(cell, EAST));
  EXPECT_FALSE(maze.isSeen(cell, SOUTH));
  EXPECT_FALSE(maze.isSeen(cell, WEST));
  maze.setVisited(cell);
  EXPECT_TRUE(maze.isSeen(cell, NORTH));
  EXPECT_TRUE(maze.isSeen(cell, EAST));
  EXPECT_TRUE(maze.isSeen(cell, SOUTH));
  EXPECT_TRUE(maze.isSeen(cell, WEST));
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.isSeen(cell, NORTH));
  EXPECT_FALSE(maze.isSeen(cell, EAST));
  EXPECT_FALSE(maze.isSeen(cell, SOUTH));
  EXPECT_FALSE(maze.isSeen(cell, WEST));

}



TEST_F(MazeMaskTest, isExit) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  maze.clearVisited(cell);
  EXPECT_TRUE(maze.hasExit(cell, NORTH));
  EXPECT_TRUE(maze.hasExit(cell, EAST));
  EXPECT_TRUE(maze.hasExit(cell, SOUTH));
  EXPECT_TRUE(maze.hasExit(cell, WEST));
  maze.setVisited(cell);
  EXPECT_TRUE(maze.hasExit(cell, NORTH));
  EXPECT_TRUE(maze.hasExit(cell, EAST));
  EXPECT_TRUE(maze.hasExit(cell, SOUTH));
  EXPECT_TRUE(maze.hasExit(cell, WEST));
  maze.setWall(cell, NORTH);
  EXPECT_FALSE(maze.hasExit(cell, NORTH));
  maze.setVisited(cell);
  EXPECT_FALSE(maze.hasExit(cell, NORTH));
}


TEST_F(MazeMaskTest, isWall) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.hasWall(cell, NORTH));
  EXPECT_FALSE(maze.hasWall(cell, EAST));
  EXPECT_FALSE(maze.hasWall(cell, SOUTH));
  EXPECT_FALSE(maze.hasWall(cell, WEST));
  maze.setVisited(cell);
  EXPECT_FALSE(maze.hasWall(cell, NORTH));
  EXPECT_FALSE(maze.hasWall(cell, EAST));
  EXPECT_FALSE(maze.hasWall(cell, SOUTH));
  EXPECT_FALSE(maze.hasWall(cell, WEST));
  maze.setWall(cell, NORTH);
  EXPECT_TRUE(maze.hasWall(cell, NORTH));
  maze.setVisited(cell);
  EXPECT_TRUE(maze.hasWall(cell, NORTH));
}


TEST_F(MazeMaskTest, hasRealWall) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.hasRealWall(cell, NORTH));
  EXPECT_FALSE(maze.hasRealWall(cell, EAST));
  EXPECT_FALSE(maze.hasRealWall(cell, SOUTH));
  EXPECT_FALSE(maze.hasRealWall(cell, WEST));
  maze.setVisited(cell);
  EXPECT_FALSE(maze.hasRealWall(cell, NORTH));
  EXPECT_FALSE(maze.hasRealWall(cell, EAST));
  EXPECT_FALSE(maze.hasRealWall(cell, SOUTH));
  EXPECT_FALSE(maze.hasRealWall(cell, WEST));
  maze.setWall(cell, NORTH);
  EXPECT_TRUE(maze.hasRealWall(cell, NORTH));
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.hasRealWall(cell, NORTH));
}


TEST_F(MazeMaskTest, hasRealExit) {
  Maze maze(16);
  maze.clearData();
  int cell = 34;
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.hasRealExit(cell, NORTH));
  EXPECT_FALSE(maze.hasRealExit(cell, EAST));
  EXPECT_FALSE(maze.hasRealExit(cell, SOUTH));
  EXPECT_FALSE(maze.hasRealExit(cell, WEST));
  maze.setVisited(cell);
  EXPECT_TRUE(maze.hasRealExit(cell, NORTH));
  EXPECT_TRUE(maze.hasRealExit(cell, EAST));
  EXPECT_TRUE(maze.hasRealExit(cell, SOUTH));
  EXPECT_TRUE(maze.hasRealExit(cell, WEST));
  maze.clearWall(cell, NORTH);
  EXPECT_TRUE(maze.hasRealExit(cell, NORTH));
  maze.clearVisited(cell);
  EXPECT_FALSE(maze.hasRealExit(cell, NORTH));
}
