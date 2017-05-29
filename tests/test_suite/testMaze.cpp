#include "gtest/gtest.h"
#include "oldmaze.h"
#include "mazeprinter.h"
#include "mazedata.h"
#include "maze.h"
/////////////////////

class MazeTest : public ::testing::Test {
protected:
  Maze *maze;

  virtual void SetUp() {
    maze = new Maze();
    maze->resetData();
  }

  virtual void TearDown() {
    delete maze;
  }

};

TEST_F(MazeTest,SetAndGetGoal){
  EXPECT_EQ(DEFAULT_GOAL,maze->goal());
  maze->setGoal(99);
  EXPECT_EQ(99,maze->goal());
}

TEST_F (MazeTest, ClearMaze_AllWallsAbsent)
{
  maze->clearMaze();
  for(int i = 0; i < maze->numCells(); i++){
      EXPECT_EQ (0, maze->walls(i));
    }
}

TEST_F (MazeTest, ResetData_16x16_SetsEmptyMaze){
  maze->resetData();
  EXPECT_EQ(256,maze->numCells());
  for(int i = 0; i < maze->numCells(); i++){
    EXPECT_EQ(emptyMaze[i], maze->walls(i));
  }
}

TEST_F (MazeTest, ResetData_DefaultCostsAreUINT16_MAX)
{
  maze->resetData();
  for(int i = 0; i < maze->numCells(); i++){
    EXPECT_EQ (UINT16_MAX, maze->cost(i));
  }
}


TEST_F(MazeTest, SetClearAndGetWalls){
  maze->resetData();
  maze->setWall(0x22,NORTH);
  maze->setWall(0x22,EAST);
  maze->setWall(0x22,SOUTH);
  maze->setWall(0x22,WEST);
  EXPECT_FALSE(maze->hasExit(0x22,EAST));
  EXPECT_FALSE(maze->hasExit(0x32,WEST));
  EXPECT_FALSE(maze->hasExit(0x22,SOUTH));
  EXPECT_FALSE(maze->hasExit(0x21,NORTH));
  EXPECT_FALSE(maze->hasExit(0x22,WEST));
  EXPECT_FALSE(maze->hasExit(0x12,EAST));
  EXPECT_FALSE(maze->hasExit(0x22,NORTH));
  EXPECT_FALSE(maze->hasExit(0x23,SOUTH));
  EXPECT_TRUE(maze->hasWall(0x22,EAST));
  EXPECT_TRUE(maze->hasWall(0x32,WEST));
  EXPECT_TRUE(maze->hasWall(0x22,SOUTH));
  EXPECT_TRUE(maze->hasWall(0x21,NORTH));
  EXPECT_TRUE(maze->hasWall(0x22,WEST));
  EXPECT_TRUE(maze->hasWall(0x12,EAST));
  EXPECT_TRUE(maze->hasWall(0x22,NORTH));
  EXPECT_TRUE(maze->hasWall(0x23,SOUTH));
  maze->clearWall(0x22,NORTH);
  maze->clearWall(0x22,EAST);
  maze->clearWall(0x22,SOUTH);
  maze->clearWall(0x22,WEST);
  EXPECT_TRUE(maze->hasExit(0x22,EAST));
  EXPECT_TRUE(maze->hasExit(0x32,WEST));
  EXPECT_TRUE(maze->hasExit(0x22,SOUTH));
  EXPECT_TRUE(maze->hasExit(0x21,NORTH));
  EXPECT_TRUE(maze->hasExit(0x22,WEST));
  EXPECT_TRUE(maze->hasExit(0x12,EAST));
  EXPECT_TRUE(maze->hasExit(0x22,NORTH));
  EXPECT_TRUE(maze->hasExit(0x23,SOUTH));
  EXPECT_FALSE(maze->hasWall(0x22,EAST));
  EXPECT_FALSE(maze->hasWall(0x32,WEST));
  EXPECT_FALSE(maze->hasWall(0x22,SOUTH));
  EXPECT_FALSE(maze->hasWall(0x21,NORTH));
  EXPECT_FALSE(maze->hasWall(0x22,WEST));
  EXPECT_FALSE(maze->hasWall(0x12,EAST));
  EXPECT_FALSE(maze->hasWall(0x22,NORTH));
  EXPECT_FALSE(maze->hasWall(0x23,SOUTH));
}

/////////////////////
TEST_F(MazeTest, HasExit){
  maze->resetData();
  EXPECT_FALSE(maze->hasExit(0x0F,WEST));
  EXPECT_FALSE(maze->hasExit(0x0F,NORTH));
  EXPECT_FALSE(maze->hasExit(0xF0,EAST));
  EXPECT_FALSE(maze->hasExit(0xF0,SOUTH));
}

TEST (Maze, MazeUpdateFromWallData_AllWalls)
{
//  location_t loc = {2, 4};
//  walls_t wallData = 0x0f;  // all walls
//  MazeResetWalls();
//  UpdateCellFromWallData (loc, wallData);
//  walls_t walls;
//  walls = Walls (loc);
//  EXPECT_TRUE (WallExists (walls, NORTH));
//  EXPECT_TRUE (WallExists (walls, EAST));
//  EXPECT_TRUE (WallExists (walls, SOUTH));
//  EXPECT_TRUE (WallExists (walls, WEST));
//  //no need to check neighbours - that is tested elsewhere
}

TEST (Maze, MazeUpdateFromWallData_SomeWalls)
{
//  location_t loc = {2, 4};
//  walls_t wallData = 0x03;  // North and East Only
//  MazeResetWalls();
//  UpdateCellFromWallData (loc, wallData);
//  walls_t walls;
//  walls = Walls (loc);
//  EXPECT_TRUE (WallExists (walls, NORTH));
//  EXPECT_TRUE (WallExists (walls, EAST));
//  EXPECT_FALSE (WallExists (walls, SOUTH));
//  EXPECT_FALSE (WallExists (walls, WEST));
//  //no need to check neighbours - that is tested elsewhere
}

TEST (Maze, MazeUpdateFromWallData_NoWalls)
{
//  location_t loc = {2, 4};
//  walls_t wallData = 0x00;  // No walls
//  MazeResetWalls();
//  UpdateCellFromWallData (loc, wallData);
//  walls_t walls;
//  walls = Walls (loc);
//  EXPECT_FALSE (WallExists (walls, NORTH));
//  EXPECT_FALSE (WallExists (walls, EAST));
//  EXPECT_FALSE (WallExists (walls, SOUTH));
//  EXPECT_FALSE (WallExists (walls, WEST));
//  //no need to check neighbours - that is tested elsewhere
}

TEST (Maze, Has_Exit_AllWalls)
{
//  location_t loc = {2, 4};
//  MazeResetWalls();
//  EXPECT_TRUE (HasExit (loc, NORTH));
//  EXPECT_TRUE (HasExit (loc, EAST));
//  EXPECT_TRUE (HasExit (loc, SOUTH));
//  EXPECT_TRUE (HasExit (loc, WEST));
//  MazeAddWall (loc, NORTH);
//  MazeAddWall (loc, EAST);
//  MazeAddWall (loc, SOUTH);
//  MazeAddWall (loc, WEST);
//  EXPECT_FALSE (HasExit (loc, NORTH));
//  EXPECT_FALSE (HasExit (loc, EAST));
//  EXPECT_FALSE (HasExit (loc, SOUTH));
//  EXPECT_FALSE (HasExit (loc, WEST));
}


TEST_F (MazeTest, MazeInit_CreatesBlankMaze)
{
  maze->resetData();
  EXPECT_TRUE(maze->hasWall(0,WEST));
  EXPECT_TRUE(maze->hasWall(0,EAST));
  EXPECT_TRUE(maze->hasWall(0,SOUTH));
  EXPECT_FALSE(maze->hasWall(0,NORTH));
  EXPECT_TRUE (maze->hasExit(0, NORTH)) ;
  EXPECT_FALSE (maze->hasExit(0,  EAST));
  EXPECT_FALSE (maze->hasExit(0,  SOUTH));
  EXPECT_FALSE (maze->hasExit(0,  WEST));
  EXPECT_EQ (UINT16_MAX, maze->cost(maze->home()));
  EXPECT_EQ (NORTH, maze->heading(maze->home()));
}

TEST_F (MazeTest, VisitedCells)
{
//  MazeInit();
//  EXPECT_FALSE (Visited (Location (0, 0)));
//  MazeAddWall (Location (0, 0), NORTH);
//  EXPECT_TRUE (Visited (Location (0, 0)));
}

