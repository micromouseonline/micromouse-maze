/***********************************************************************
 * Created by Peter Harrison on 08/10/2018.
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


#include <vector>
#include <mazedata.h>
#include "gtest/gtest.h"
#include "mazeprinter.h"
#include "mazedata.h"
#include "maze.h"
#include "mazefiler.h"

/////////////////////

class TestGoalArea : public ::testing::Test {
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


TEST_F(TestGoalArea, defaultGoal) {
  EXPECT_EQ(4, maze->goalAreaSize());
  GoalArea_t goalArea = maze->getGoalArea();
  EXPECT_EQ(4, goalArea.size());
  EXPECT_TRUE(maze->goalContains(0x77));
  EXPECT_TRUE(maze->goalContains(0x78));
  EXPECT_TRUE(maze->goalContains(0x87));
  EXPECT_TRUE(maze->goalContains(0x88));

}


TEST_F(TestGoalArea, setGoalArea) {
  GoalArea_t area = {2, 3, 4, 5, 6};
  maze->setGoalArea(area);
  EXPECT_EQ(5, maze->goalAreaSize());
  EXPECT_TRUE(maze->goalContains(2));
  EXPECT_TRUE(maze->goalContains(3));
  EXPECT_TRUE(maze->goalContains(4));
  EXPECT_TRUE(maze->goalContains(5));
  EXPECT_TRUE(maze->goalContains(6));
  EXPECT_FALSE(maze->goalContains(7));
}


TEST_F(TestGoalArea, SetAndGetGoal) {
  EXPECT_EQ(maze->cellID(7, 7), maze->goal());
  maze->setGoal(99);
  EXPECT_EQ(99, maze->goal());
}


TEST_F(TestGoalArea, GoalAreaInitialisDefault) {
  Maze maze16(16);
  EXPECT_EQ(4, maze16.goalAreaSize());
}


TEST_F(TestGoalArea, GoalAreaClearsEmpty) {
  Maze maze16(16);
  maze16.clearGoalArea();
  EXPECT_EQ(0, maze16.goalAreaSize());
}


TEST_F(TestGoalArea, GoalAreaFindCellInGoal) {
  Maze maze16(16);
  maze16.resetToEmptyMaze();
  EXPECT_TRUE(maze16.goalContains(7, 7));
  EXPECT_TRUE(maze16.goalContains(7, 8));
  EXPECT_TRUE(maze16.goalContains(8, 7));
  EXPECT_TRUE(maze16.goalContains(8, 8));
}



