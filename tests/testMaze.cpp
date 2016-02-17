#include "gtest/gtest.h"
#include "maze.h"


TEST (Maze, MazeResetWalls_blankWalls)
{
  MazeResetWalls();
  location_t loc;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      EXPECT_EQ (WallsNone(), MazeGetWalls (loc));
    }
  }
}

TEST (Maze, MazeResetCosts_ZeroCosts)
{
  MazeResetCosts();
  location_t loc;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      EXPECT_EQ (0, Cost (loc));
    }
  }
}

void testSetWall (location_t loc, direction_t dir)
{
  MazeResetWalls();
  MazeSetWall (loc, dir);
  walls_t walls = MazeGetWalls (loc);
  EXPECT_TRUE (HaveWall (walls, dir));
  EXPECT_FALSE (HaveWall (walls, LeftFrom (dir)));
  EXPECT_FALSE (HaveWall (walls, RightFrom (dir)));
  EXPECT_FALSE (HaveWall (walls, Behind (dir)));

  EXPECT_TRUE (WallIsSeen (walls, dir));
  EXPECT_FALSE (WallIsSeen (walls, LeftFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, RightFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, Behind (dir)));
  loc = Neighbour (loc, dir);
  dir = Behind (dir);
  walls = MazeGetWalls (loc);
  EXPECT_TRUE (HaveWall (walls, dir));
  EXPECT_FALSE (HaveWall (walls, LeftFrom (dir)));
  EXPECT_FALSE (HaveWall (walls, RightFrom (dir)));
  EXPECT_FALSE (HaveWall (walls, Behind (dir)));
  EXPECT_TRUE (WallIsSeen (walls, dir));
  EXPECT_FALSE (WallIsSeen (walls, LeftFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, RightFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, Behind (dir)));
}

void testClearWall (location_t loc, direction_t dir)
{
  MazeResetWalls();
  MazeSetWall (loc, NORTH);
  MazeSetWall (loc, EAST);
  MazeSetWall (loc, SOUTH);
  MazeSetWall (loc, WEST);
  MazeClearWall (loc, dir);
  walls_t walls = MazeGetWalls (loc);
  EXPECT_FALSE (HaveWall (walls, dir));
  EXPECT_TRUE (WallIsSeen (walls, dir));
  loc = Neighbour (loc, dir);
  dir = Behind (dir);
  walls = MazeGetWalls (loc);
  EXPECT_FALSE (HaveWall (walls, dir));
  EXPECT_TRUE (WallIsSeen (walls, dir));
}

TEST (Maze, SetWall_SetWall_GetLocPlusNeighbours)
{
  location_t loc = {3, 4};
  testSetWall (loc, NORTH);
  testSetWall (loc, SOUTH);
  testSetWall (loc, EAST);
  testSetWall (loc, WEST);
}

TEST (Maze, ClearWall_ClearWall_GetLocPlusNeighbours)
{
  location_t loc = {3, 4};
  testClearWall (loc, NORTH);
  testClearWall (loc, SOUTH);
  testClearWall (loc, EAST);
  testClearWall (loc, WEST);
}


TEST (Maze, SetWall_SetAtEdges_IgnoreOverflow)
{
  location_t loc;
  loc.row = 0;
  loc.col = 0;
  testSetWall (loc, WEST);
  testSetWall (loc, SOUTH);
  loc.row = MazeHeight() - 1;
  loc.col = MazeWidth() - 1;
  testSetWall (loc, NORTH);
  testSetWall (loc, EAST);
}

TEST (Maze, MazeUpdateFromWallData_AllWalls)
{
  location_t loc = {2, 4};
  walls_t wallData = 0x0f;  // all walls
  MazeResetWalls();
  MazeUpdateFromWallData (loc, wallData);
  walls_t walls;
  walls = MazeGetWalls (loc);
  EXPECT_TRUE (HaveWall (walls, NORTH));
  EXPECT_TRUE (HaveWall (walls, EAST));
  EXPECT_TRUE (HaveWall (walls, SOUTH));
  EXPECT_TRUE (HaveWall (walls, WEST));
  //no need to check neighbours - that is tested elsewhere
}

TEST (Maze, MazeUpdateFromWallData_SomeWalls)
{
  location_t loc = {2, 4};
  walls_t wallData = 0x03;  // North and East Only
  MazeResetWalls();
  MazeUpdateFromWallData (loc, wallData);
  walls_t walls;
  walls = MazeGetWalls (loc);
  EXPECT_TRUE (HaveWall (walls, NORTH));
  EXPECT_TRUE (HaveWall (walls, EAST));
  EXPECT_FALSE (HaveWall (walls, SOUTH));
  EXPECT_FALSE (HaveWall (walls, WEST));
  //no need to check neighbours - that is tested elsewhere
}

TEST (Maze, MazeUpdateFromWallData_NoWalls)
{
  location_t loc = {2, 4};
  walls_t wallData = 0x00;  // No walls
  MazeResetWalls();
  MazeUpdateFromWallData (loc, wallData);
  walls_t walls;
  walls = MazeGetWalls (loc);
  EXPECT_FALSE (HaveWall (walls, NORTH));
  EXPECT_FALSE (HaveWall (walls, EAST));
  EXPECT_FALSE (HaveWall (walls, SOUTH));
  EXPECT_FALSE (HaveWall (walls, WEST));
  //no need to check neighbours - that is tested elsewhere
}

TEST (Maze, Has_Exit_AllWalls)
{
  location_t loc = {2, 4};
  MazeResetWalls();
  EXPECT_TRUE (HasExit (loc, NORTH));
  EXPECT_TRUE (HasExit (loc, EAST));
  EXPECT_TRUE (HasExit (loc, SOUTH));
  EXPECT_TRUE (HasExit (loc, WEST));
  MazeSetWall (loc, NORTH);
  MazeSetWall (loc, EAST);
  MazeSetWall (loc, SOUTH);
  MazeSetWall (loc, WEST);
  EXPECT_FALSE (HasExit (loc, NORTH));
  EXPECT_FALSE (HasExit (loc, EAST));
  EXPECT_FALSE (HasExit (loc, SOUTH));
  EXPECT_FALSE (HasExit (loc, WEST));
}
