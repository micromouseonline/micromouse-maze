#include "gtest/gtest.h"
#include "maze.h"
#include "mazeprinter.h"


TEST (Maze, MazeResetWalls_blankWalls)
{
  MazeResetWalls();
  location_t loc;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      EXPECT_EQ (WallsNone(), Walls (loc));
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
  MazeAddWall (loc, dir);
  walls_t walls = Walls (loc);
  EXPECT_TRUE (WallExists (walls, dir));
  EXPECT_FALSE (WallExists (walls, LeftFrom (dir)));
  EXPECT_FALSE (WallExists (walls, RightFrom (dir)));
  EXPECT_FALSE (WallExists (walls, Behind (dir)));

  EXPECT_TRUE (WallIsSeen (walls, dir));
  EXPECT_FALSE (WallIsSeen (walls, LeftFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, RightFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, Behind (dir)));
  loc = Neighbour (loc, dir);
  dir = Behind (dir);
  walls = Walls (loc);
  EXPECT_TRUE (WallExists (walls, dir));
  EXPECT_FALSE (WallExists (walls, LeftFrom (dir)));
  EXPECT_FALSE (WallExists (walls, RightFrom (dir)));
  EXPECT_FALSE (WallExists (walls, Behind (dir)));
  EXPECT_TRUE (WallIsSeen (walls, dir));
  EXPECT_FALSE (WallIsSeen (walls, LeftFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, RightFrom (dir)));
  EXPECT_FALSE (WallIsSeen (walls, Behind (dir)));
}

void testClearWall (location_t loc, direction_t dir)
{
  MazeResetWalls();
  MazeAddWall (loc, NORTH);
  MazeAddWall (loc, EAST);
  MazeAddWall (loc, SOUTH);
  MazeAddWall (loc, WEST);
  MazeRemoveWall (loc, dir);
  walls_t walls = Walls (loc);
  EXPECT_FALSE (WallExists (walls, dir));
  EXPECT_TRUE (WallIsSeen (walls, dir));
  loc = Neighbour (loc, dir);
  dir = Behind (dir);
  walls = Walls (loc);
  EXPECT_FALSE (WallExists (walls, dir));
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
  walls = Walls (loc);
  EXPECT_TRUE (WallExists (walls, NORTH));
  EXPECT_TRUE (WallExists (walls, EAST));
  EXPECT_TRUE (WallExists (walls, SOUTH));
  EXPECT_TRUE (WallExists (walls, WEST));
  //no need to check neighbours - that is tested elsewhere
}

TEST (Maze, MazeUpdateFromWallData_SomeWalls)
{
  location_t loc = {2, 4};
  walls_t wallData = 0x03;  // North and East Only
  MazeResetWalls();
  MazeUpdateFromWallData (loc, wallData);
  walls_t walls;
  walls = Walls (loc);
  EXPECT_TRUE (WallExists (walls, NORTH));
  EXPECT_TRUE (WallExists (walls, EAST));
  EXPECT_FALSE (WallExists (walls, SOUTH));
  EXPECT_FALSE (WallExists (walls, WEST));
  //no need to check neighbours - that is tested elsewhere
}

TEST (Maze, MazeUpdateFromWallData_NoWalls)
{
  location_t loc = {2, 4};
  walls_t wallData = 0x00;  // No walls
  MazeResetWalls();
  MazeUpdateFromWallData (loc, wallData);
  walls_t walls;
  walls = Walls (loc);
  EXPECT_FALSE (WallExists (walls, NORTH));
  EXPECT_FALSE (WallExists (walls, EAST));
  EXPECT_FALSE (WallExists (walls, SOUTH));
  EXPECT_FALSE (WallExists (walls, WEST));
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
  MazeAddWall (loc, NORTH);
  MazeAddWall (loc, EAST);
  MazeAddWall (loc, SOUTH);
  MazeAddWall (loc, WEST);
  EXPECT_FALSE (HasExit (loc, NORTH));
  EXPECT_FALSE (HasExit (loc, EAST));
  EXPECT_FALSE (HasExit (loc, SOUTH));
  EXPECT_FALSE (HasExit (loc, WEST));
}


TEST (Maze, MazeInit)
{
  MazeInit();
  EXPECT_TRUE (HasExit (Location (0, 0), NORTH));
  EXPECT_FALSE (HasExit (Location (0, 0), EAST));
  EXPECT_FALSE (HasExit (Location (0, 0), SOUTH));
  EXPECT_FALSE (HasExit (Location (0, 0), WEST));
  EXPECT_EQ (0, Cost (Location (0, 0)));
  EXPECT_EQ (INVALID, Direction (Location (0, 0)));
  PrintMaze (DIRS);
  PrintMaze (COSTS);
}

TEST (Maze, Visited)
{
  MazeInit();
  EXPECT_FALSE (Visited (Location (0, 0)));
  MazeAddWall (Location (0, 0), NORTH);
  EXPECT_TRUE (Visited (Location (0, 0)));
}

