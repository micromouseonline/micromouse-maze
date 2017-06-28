#include <iostream>
#include "gtest/gtest.h"
#include "mazeprinter.h"
#include "mazepathfinder.h"
#include "maze.h"
#include "mazedata.h"

class PathFinderTest : public ::testing::Test {


  /* This gets run before each test */
  virtual void SetUp() {
    maze = new Maze(16);
    maze->copyMazeFromFileData(japan2007, 256);
    maze->flood(0x77);
    path = new PathFinder(maze);
  }

  virtual void TearDown() {
    std::cout << path->toString() <<  "\n" << std::endl;
    delete path;
    delete maze;
  }

 protected:
  PathFinder *path;
  Maze *maze;
};

TEST_F(PathFinderTest,constructor){
  EXPECT_NE(nullptr,path);
  EXPECT_EQ(0,strlen(path->toString()));
  EXPECT_EQ(0,path->length());
  EXPECT_EQ(INVALID_DIRECTION, path->endHeading());
  EXPECT_EQ(0,path->endCell());
  EXPECT_FALSE(path->reachesTarget());
}

TEST_F(PathFinderTest,generate_EmptyMaze_ManhattanFlood){
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze,256);
  maze->flood(0x77);
  path->generate(maze,0,0x77);
  EXPECT_EQ(16,strlen(path->toString()));
  EXPECT_STREQ("BFFFFFFFRFFFFFFS",path->data());
  EXPECT_EQ(15,path->length());
  EXPECT_EQ(EAST, path->endHeading());
  EXPECT_EQ(0x77,path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest,generate_EmptyMaze_AtDestination){
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze,256);
  maze->flood(0x77);
  path->generate(maze,0x77,0x77);
  EXPECT_EQ(2,strlen(path->toString()));
  EXPECT_STREQ("BS",path->data());
  EXPECT_EQ(NORTH, path->endHeading());
  EXPECT_EQ(0x77,path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest,generate_EmptyMaze_OneCellAhead){
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze,256);
  maze->flood(0x77);
  path->generate(maze,0x76,0x77);
  EXPECT_EQ(3,strlen(path->toString()));
  EXPECT_STREQ("BFS",path->data());
  EXPECT_EQ(NORTH, path->endHeading());
  EXPECT_EQ(0x77,path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}

TEST_F(PathFinderTest,generate_EmptyMaze_OneCellBehind){
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze,256);
  maze->flood(0x77);
  path->generate(maze,0x78,0x77);
  EXPECT_EQ(3,strlen(path->toString()));
  EXPECT_STREQ("BFS",path->data()) ;
  EXPECT_EQ(SOUTH, path->endHeading());
  EXPECT_EQ(0x77,path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}


TEST_F(PathFinderTest,generate_NoExitCurrentCell){
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze,256);
  maze->setWall(0x00,NORTH);
  maze->flood(0x77);
  path->generate(maze,0,0x77);
  EXPECT_EQ(2,strlen(path->toString()));
  EXPECT_STREQ("BS",path->data());
  EXPECT_EQ(INVALID_DIRECTION, path->endHeading());
  EXPECT_EQ(0,path->endCell());
  EXPECT_FALSE(path->reachesTarget());
}

TEST_F(PathFinderTest,generate_NoRoute){
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(emptyMaze,256);
  maze->setWall(0x01,NORTH);
  maze->setWall(0x01,EAST);
  maze->flood(0x77);
  path->generate(maze,0,0x77);
  EXPECT_EQ(2,strlen(path->toString()));
  EXPECT_STREQ("BS",path->data());
  EXPECT_EQ(INVALID_DIRECTION, path->endHeading());
  EXPECT_EQ(0,path->endCell());
  EXPECT_FALSE(path->reachesTarget());
}



TEST_F(PathFinderTest,generate_Japan2007_ManHattan_CorrectPAth){
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  maze->copyMazeFromFileData(japan2007,256);
  maze->flood(0x77);
  path->generate(maze,0,0x77);
  EXPECT_EQ(74,strlen(path->toString()));
  char result[] = "BFFFRLLRRLLRRLLRFFRRFLLFFLRFRRLLRRLLRFFFFFFFFFRFFFFFRLRLLRRLLRRFFRFFFLFFFS";
  EXPECT_STREQ(result,path->data());
  EXPECT_EQ(WEST, path->endHeading());
  EXPECT_EQ(0x77,path->endCell());
  EXPECT_TRUE(path->reachesTarget());
}


