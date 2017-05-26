#include "gtest/gtest.h"
#include "newmaze.h"
#include "D5Maze.h"


TEST (Walls, SetWall){
  NewMaze newMaze;
  D5Maze oldMaze;
  newMaze.clearMaze();
  oldMaze.clearMaze();
  EXPECT_EQ(newMaze.goal(),oldMaze.goal());
  EXPECT_EQ(newMaze.walls(0),oldMaze.walls(0));
}
