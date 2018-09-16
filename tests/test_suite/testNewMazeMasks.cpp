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
    uint8_t closedWalls = maze.xWalls[i] & CLOSED_MASK;
    EXPECT_ISWALL(closedWalls & (WALL_MASK << NORTH));
    EXPECT_ISWALL(closedWalls & (WALL_MASK << EAST));
    EXPECT_ISWALL(closedWalls & (WALL_MASK << SOUTH));
    EXPECT_ISWALL(closedWalls & (WALL_MASK << WEST));

    uint8_t openWalls = maze.xWalls[i] & OPEN_MASK;
    EXPECT_ISEXIT(openWalls & (WALL_MASK << NORTH));
    EXPECT_ISEXIT(openWalls & (WALL_MASK << EAST));
    EXPECT_ISEXIT(openWalls & (WALL_MASK << SOUTH));
    EXPECT_ISEXIT(openWalls & (WALL_MASK << WEST));

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
  uint8_t closedWalls = maze.xWalls[cell] & CLOSED_MASK;
  uint8_t openWalls = maze.xWalls[cell] & OPEN_MASK;
  EXPECT_ISWALL(closedWalls & (WALL_MASK << NORTH));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << EAST));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << SOUTH));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << WEST));

  EXPECT_ISWALL(openWalls & (WALL_MASK << NORTH));
  EXPECT_ISWALL(openWalls & (WALL_MASK << EAST));
  EXPECT_ISWALL(openWalls & (WALL_MASK << SOUTH));
  EXPECT_ISWALL(openWalls & (WALL_MASK << WEST));

  nextCell = maze.cellNorth(cell);
  closedWalls = maze.xWalls[nextCell] & CLOSED_MASK;
  openWalls = maze.xWalls[nextCell] & OPEN_MASK;
  EXPECT_ISWALL(closedWalls & (WALL_MASK << NORTH));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << EAST));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << SOUTH));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << WEST));

  EXPECT_ISEXIT(openWalls & (WALL_MASK << NORTH));
  EXPECT_ISEXIT(openWalls & (WALL_MASK << EAST));
  EXPECT_ISWALL(openWalls & (WALL_MASK << SOUTH));
  EXPECT_ISEXIT(openWalls & (WALL_MASK << WEST));


  nextCell = maze.cellEast(cell);
  closedWalls = maze.xWalls[nextCell] & CLOSED_MASK;
  openWalls = maze.xWalls[nextCell] & OPEN_MASK;
  EXPECT_ISWALL(closedWalls & (WALL_MASK << NORTH));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << EAST));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << SOUTH));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << WEST));

  EXPECT_ISEXIT(openWalls & (WALL_MASK << NORTH));
  EXPECT_ISEXIT(openWalls & (WALL_MASK << EAST));
  EXPECT_ISEXIT(openWalls & (WALL_MASK << SOUTH));
  EXPECT_ISWALL(openWalls & (WALL_MASK << WEST));


  nextCell = maze.cellSouth(cell);
  closedWalls = maze.xWalls[nextCell] & CLOSED_MASK;
  openWalls = maze.xWalls[nextCell] & OPEN_MASK;
  EXPECT_ISWALL(closedWalls & (WALL_MASK << NORTH));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << EAST));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << SOUTH));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << WEST));

  EXPECT_ISWALL(openWalls & (WALL_MASK << NORTH));
  EXPECT_ISEXIT(openWalls & (WALL_MASK << EAST));
  EXPECT_ISEXIT(openWalls & (WALL_MASK << SOUTH));
  EXPECT_ISEXIT(openWalls & (WALL_MASK << WEST));

  nextCell = maze.cellWest(cell);
  closedWalls = maze.xWalls[nextCell] & CLOSED_MASK;
  openWalls = maze.xWalls[nextCell] & OPEN_MASK;
  EXPECT_ISWALL(closedWalls & (WALL_MASK << NORTH));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << EAST));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << SOUTH));
  EXPECT_ISWALL(closedWalls & (WALL_MASK << WEST));

  EXPECT_ISEXIT(openWalls & (WALL_MASK << NORTH));
  EXPECT_ISWALL(openWalls & (WALL_MASK << EAST));
  EXPECT_ISEXIT(openWalls & (WALL_MASK << SOUTH));
  EXPECT_ISEXIT(openWalls & (WALL_MASK << WEST));



}