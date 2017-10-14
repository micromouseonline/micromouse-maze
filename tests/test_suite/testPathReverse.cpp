/***********************************************************************
 * Created by Peter Harrison on 14/10/2017.
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


#include <algorithm>
#include "mazepathfinder.h"
#include "mazedata.h"
#include "path_test_data.h"
#include "gtest/gtest.h"


class PathFinderReverseTest : public ::testing::Test {

  /* This gets run before each test */
  virtual void SetUp() {
    maze = new Maze(16);
    maze->copyMazeFromFileData(japan2007ef, 256);
    maze->flood(0x77);
    path = new PathFinder();
  }

  virtual void TearDown() {
    delete path;
    delete maze;
  }

 protected:
  PathFinder *path;
  Maze *maze;
};


TEST_F(PathFinderReverseTest, emptyString) {
  char s[] = "";
  path->reversePath(s);
  EXPECT_STREQ(s, s);

}

TEST_F(PathFinderReverseTest,shortString) {
  char s[] = "a";
  path->reversePath(s);
  EXPECT_STREQ(s, s);
}


TEST_F(PathFinderReverseTest, shortPathExplore) {
  char s[] = "BX";
  path->reversePath(s);
  EXPECT_STREQ(s, s);
}

TEST_F(PathFinderReverseTest, shortPathRun) {
  char s[] = "BS";
  path->reversePath(s);
  EXPECT_STREQ(s, s);
}

TEST_F(PathFinderReverseTest, longEvenString) {
  char s[] = "BFFRLX";
  char r[] = "BRLFFX";
  path->reversePath(s);
  EXPECT_STREQ(s, r);

}

TEST_F(PathFinderReverseTest, longOddString) {
  char s[] = "BFRFRLS";
  char r[] = "BRLFLFS";
  path->reversePath(s);
  EXPECT_STREQ(s, r);
}

TEST_F(PathFinderReverseTest, emptyMaze_FromGoal){
  maze->setFloodType(Maze::RUNLENGTH_FLOOD);
  maze->copyMazeFromFileData(emptyMaze, 256);
  maze->flood(0x77);
  path->generateSafePath(0, 0x77, maze);
  EXPECT_EQ(16, strlen(path->path()));
  EXPECT_STREQ("BFFFFFFFRFFFFFFS", path->path());
  path->reversePath();
  EXPECT_STREQ("BFFFFFFLFFFFFFFS", path->path());
  }