#include "gtest/gtest.h"
#include "maze.h"



TEST(Walls,WallsGetBlank_Gets_No_Walls_No_Visibility){
    walls_t wallData = WallsGetBlank();
  EXPECT_FALSE (WallIsSet (wallData, NORTH));
  EXPECT_FALSE (WallIsSet (wallData, EAST));
  EXPECT_FALSE (WallIsSet (wallData, SOUTH));
  EXPECT_FALSE (WallIsSet (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}

TEST (Walls, WallResetData_noWalls_noSeen)
{
  walls_t wallData = WallsGetBlank();
  EXPECT_FALSE (WallIsSet (wallData, NORTH));
  EXPECT_FALSE (WallIsSet (wallData, EAST));
  EXPECT_FALSE (WallIsSet (wallData, SOUTH));
  EXPECT_FALSE (WallIsSet (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}

TEST (Walls, WallSetNORTH_get_wallIsSet_AND_wallIsSeen)
{
  walls_t wallData = WallsGetBlank();
  WallSet (&wallData, NORTH);
  EXPECT_TRUE (WallIsSet (wallData, NORTH));
  EXPECT_FALSE (WallIsSet (wallData, EAST));
  EXPECT_FALSE (WallIsSet (wallData, SOUTH));
  EXPECT_FALSE (WallIsSet (wallData, WEST));
  EXPECT_TRUE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}
TEST (Walls, WallSetEAST_get_wallIsSet_AND_wallIsSeen)
{
  walls_t wallData = WallsGetBlank();
  WallSet (&wallData, EAST);
  EXPECT_FALSE (WallIsSet (wallData, NORTH));
  EXPECT_TRUE (WallIsSet (wallData, EAST));
  EXPECT_FALSE (WallIsSet (wallData, SOUTH));
  EXPECT_FALSE (WallIsSet (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_TRUE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}
TEST (Walls, WallSetSOUTH_get_wallIsSet_AND_wallIsSeen)
{
  walls_t wallData = WallsGetBlank();
  WallSet (&wallData, SOUTH);
  EXPECT_FALSE (WallIsSet (wallData, NORTH));
  EXPECT_FALSE (WallIsSet (wallData, EAST));
  EXPECT_TRUE (WallIsSet (wallData, SOUTH));
  EXPECT_FALSE (WallIsSet (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_TRUE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}

TEST (Walls, WallSetWEST_get_wallIsSet_AND_wallIsSeen)
{
  walls_t wallData = WallsGetBlank();;
  WallSet (&wallData, WEST);
  EXPECT_FALSE (WallIsSet (wallData, NORTH));
  EXPECT_FALSE (WallIsSet (wallData, EAST));
  EXPECT_FALSE (WallIsSet (wallData, SOUTH));
  EXPECT_TRUE (WallIsSet (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_TRUE (WallIsSeen (wallData, WEST));
}

TEST (Walls, WallClearNORTH_get_wallIsClear_AND_wallIsSeen)
{
  walls_t wallData = WallsGetBlank();
  WallClear (&wallData, NORTH);
  EXPECT_FALSE (WallIsSet (wallData, NORTH));
  EXPECT_FALSE (WallIsSet (wallData, EAST));
  EXPECT_FALSE (WallIsSet (wallData, SOUTH));
  EXPECT_FALSE (WallIsSet (wallData, WEST));
  EXPECT_TRUE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}
TEST (Walls, WallClearEAST_get_wallIsClear_AND_wallIsSeen)
{
  walls_t wallData = WallsGetBlank();
  WallClear (&wallData, EAST);
  EXPECT_FALSE (WallIsSet (wallData, NORTH));
  EXPECT_FALSE (WallIsSet (wallData, EAST));
  EXPECT_FALSE (WallIsSet (wallData, SOUTH));
  EXPECT_FALSE (WallIsSet (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_TRUE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}
TEST (Walls, WallClearSOUTH_get_wallIsClear_AND_wallIsSeen)
{
  walls_t wallData = WallsGetBlank();
  WallClear (&wallData, SOUTH);
  EXPECT_FALSE (WallIsSet (wallData, NORTH));
  EXPECT_FALSE (WallIsSet (wallData, EAST));
  EXPECT_FALSE (WallIsSet (wallData, SOUTH));
  EXPECT_FALSE (WallIsSet (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_TRUE (WallIsSeen (wallData, SOUTH));
  EXPECT_FALSE (WallIsSeen (wallData, WEST));
}

TEST (Walls, WallClearWEST_get_wallIsClear_AND_wallIsSeen)
{
  walls_t wallData = WallsGetBlank();
  WallClear (&wallData, WEST);
  EXPECT_FALSE (WallIsSet (wallData, NORTH));
  EXPECT_FALSE (WallIsSet (wallData, EAST));
  EXPECT_FALSE (WallIsSet (wallData, SOUTH));
  EXPECT_FALSE (WallIsSet (wallData, WEST));
  EXPECT_FALSE (WallIsSeen (wallData, NORTH));
  EXPECT_FALSE (WallIsSeen (wallData, EAST));
  EXPECT_FALSE (WallIsSeen (wallData, SOUTH));
  EXPECT_TRUE (WallIsSeen (wallData, WEST));
}


