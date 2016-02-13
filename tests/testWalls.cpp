#include "gtest/gtest.h"
#include "maze.h"



TEST (Walls, WallsGetBlank_Gets_No_Walls_No_Visibility)
{
  walls_t wallData = WallsNone();
  EXPECT_FALSE (HasWall (wallData, NORTH));
  EXPECT_FALSE (HasWall (wallData, EAST));
  EXPECT_FALSE (HasWall (wallData, SOUTH));
  EXPECT_FALSE (HasWall (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}

TEST (Walls, WallResetData_noWalls_noSeen)
{
  walls_t wallData = WallsNone();
  EXPECT_FALSE (HasWall (wallData, NORTH));
  EXPECT_FALSE (HasWall (wallData, EAST));
  EXPECT_FALSE (HasWall (wallData, SOUTH));
  EXPECT_FALSE (HasWall (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}

TEST (Walls, WallSetNORTH_get_wallIsSet_AND_wallIsSeen)
{
  walls_t wallData = WallsNone();
  WallSet (&wallData, NORTH);
  EXPECT_TRUE (HasWall (wallData, NORTH));
  EXPECT_FALSE (HasWall (wallData, EAST));
  EXPECT_FALSE (HasWall (wallData, SOUTH));
  EXPECT_FALSE (HasWall (wallData, WEST));
  EXPECT_TRUE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}
TEST (Walls, WallSetEAST_get_wallIsSet_AND_wallIsSeen)
{
  walls_t wallData = WallsNone();
  WallSet (&wallData, EAST);
  EXPECT_FALSE (HasWall (wallData, NORTH));
  EXPECT_TRUE (HasWall (wallData, EAST));
  EXPECT_FALSE (HasWall (wallData, SOUTH));
  EXPECT_FALSE (HasWall (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_TRUE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}
TEST (Walls, WallSetSOUTH_get_wallIsSet_AND_wallIsSeen)
{
  walls_t wallData = WallsNone();
  WallSet (&wallData, SOUTH);
  EXPECT_FALSE (HasWall (wallData, NORTH));
  EXPECT_FALSE (HasWall (wallData, EAST));
  EXPECT_TRUE (HasWall (wallData, SOUTH));
  EXPECT_FALSE (HasWall (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_TRUE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}

TEST (Walls, WallSetWEST_get_wallIsSet_AND_wallIsSeen)
{
  walls_t wallData = WallsNone();;
  WallSet (&wallData, WEST);
  EXPECT_FALSE (HasWall (wallData, NORTH));
  EXPECT_FALSE (HasWall (wallData, EAST));
  EXPECT_FALSE (HasWall (wallData, SOUTH));
  EXPECT_TRUE (HasWall (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_TRUE (WallIsSeen (wallData, WEST));
}

TEST (Walls, WallClearNORTH_get_wallIsClear_AND_wallIsSeen)
{
  walls_t wallData = WallsNone();
  WallClear (&wallData, NORTH);
  EXPECT_FALSE (HasWall (wallData, NORTH));
  EXPECT_FALSE (HasWall (wallData, EAST));
  EXPECT_FALSE (HasWall (wallData, SOUTH));
  EXPECT_FALSE (HasWall (wallData, WEST));
  EXPECT_TRUE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}
TEST (Walls, WallClearEAST_get_wallIsClear_AND_wallIsSeen)
{
  walls_t wallData = WallsNone();
  WallClear (&wallData, EAST);
  EXPECT_FALSE (HasWall (wallData, NORTH));
  EXPECT_FALSE (HasWall (wallData, EAST));
  EXPECT_FALSE (HasWall (wallData, SOUTH));
  EXPECT_FALSE (HasWall (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_TRUE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}
TEST (Walls, WallClearSOUTH_get_wallIsClear_AND_wallIsSeen)
{
  walls_t wallData = WallsNone();
  WallClear (&wallData, SOUTH);
  EXPECT_FALSE (HasWall (wallData, NORTH));
  EXPECT_FALSE (HasWall (wallData, EAST));
  EXPECT_FALSE (HasWall (wallData, SOUTH));
  EXPECT_FALSE (HasWall (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_TRUE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}

TEST (Walls, WallClearWEST_get_wallIsClear_AND_wallIsSeen)
{
  walls_t wallData = WallsNone();
  WallClear (&wallData, WEST);
  EXPECT_FALSE (HasWall (wallData, NORTH));
  EXPECT_FALSE (HasWall (wallData, EAST));
  EXPECT_FALSE (HasWall (wallData, SOUTH));
  EXPECT_FALSE (HasWall (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_TRUE (WallIsSeen (wallData, WEST));
}


