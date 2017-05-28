#include "gtest/gtest.h"

#include "maze.h"



TEST (Walls, DefaultWalls){
  Maze maze;
  maze.clearMaze();
  EXPECT_EQ(0x00, maze.toFileFormat(maze.walls(2,2)));
  // check the corners
  EXPECT_EQ(0x0E, maze.toFileFormat(maze.walls(0)));
  EXPECT_EQ(0x03, maze.toFileFormat(maze.walls(15,15)));
  EXPECT_EQ(0x06, maze.toFileFormat(maze.walls(15,0)));
  EXPECT_EQ(0x09, maze.toFileFormat(maze.walls(0,15)));
}

TEST(Walls, HasExit){
  Maze maze;
  maze.clearMaze();
  EXPECT_TRUE(maze.hasExit(0x22,EAST));
  EXPECT_TRUE(maze.hasExit(0x22,SOUTH));
  EXPECT_TRUE(maze.hasExit(0x22,WEST));
  EXPECT_TRUE(maze.hasExit(0x22,NORTH));

  EXPECT_FALSE(maze.hasExit(0x0F,WEST));
  EXPECT_FALSE(maze.hasExit(0x0F,NORTH));
  EXPECT_FALSE(maze.hasExit(0xF0,EAST));
  EXPECT_FALSE(maze.hasExit(0xF0,SOUTH));
}

TEST(Walls, SetGetWalls){
  Maze maze;
  maze.clearMaze();
  maze.setWall(0x22,NORTH);
  EXPECT_TRUE(maze.hasExit(0x22,EAST));
  EXPECT_TRUE(maze.hasExit(0x32,WEST));
  EXPECT_TRUE(maze.hasExit(0x22,SOUTH));
  EXPECT_TRUE(maze.hasExit(0x21,NORTH));
  EXPECT_TRUE(maze.hasExit(0x22,WEST));
  EXPECT_TRUE(maze.hasExit(0x12,EAST));
  EXPECT_FALSE(maze.hasExit(0x22,NORTH));
  EXPECT_FALSE(maze.hasExit(0x23,SOUTH));
}
