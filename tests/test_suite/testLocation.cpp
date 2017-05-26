#include "gtest/gtest.h"
#include "maze.h"

#include "D5Maze.h"

TEST (Location, Location_constructor)
{
  location_t loc = Location (9, 10);
  EXPECT_EQ (9, loc.row);
  EXPECT_EQ (10, loc.col);
}

TEST (Location, DefaultValueOfHome)
{
  location_t loc = Home();
  EXPECT_EQ (0, loc.row);
  EXPECT_EQ (0, loc.col);
}

TEST (Location, DefaultGoal_77)
{
  location_t loc = DefaultGoal();
  EXPECT_EQ (7, loc.row);
  EXPECT_EQ (7, loc.col);
}

TEST (Location, InitialisingGoal_SetToRow7Col8)
{
  location_t loc = Goal();
  EXPECT_EQ (7, loc.row);
  EXPECT_EQ (7, loc.col);
}

TEST (Location, Width_DefaultReturnsMAZE_COLS)
{
  EXPECT_EQ (MAZE_COLS, MazeWidth());
}

TEST (Location, Height_DefaultReturnsMAZE_ROWS)
{
  EXPECT_EQ (MAZE_ROWS, MazeHeight());
}

TEST (Location, SetAndFetchFGoal_SetGoal_ReturnGoal)
{
  location_t newGoal;
  newGoal.row = 3;
  newGoal.col = 4;
  location_t goal;
  SetGoal (newGoal);
  goal = Goal();
  EXPECT_EQ (newGoal.row, goal.row);
  EXPECT_EQ (newGoal.col, goal.col);
}

TEST (Location, FindNeighbour_GiveInvalidDirection_GetSameLocationBack)
{
  location_t loc;
  loc.row = 11;
  loc.col = 12;
  location_t neighbour;
  neighbour = Neighbour (loc, INVALID);
  EXPECT_EQ (11, neighbour.row);
  EXPECT_EQ (12, neighbour.col);

}
TEST (Location, FindNeighbour_SeekNORTHNeighbour_GetRowPlus1)
{
  location_t loc;
  loc.row = 5;
  loc.col = 8;
  location_t neighbour;
  neighbour = Neighbour (loc, NORTH);
  EXPECT_EQ (loc.row + 1, neighbour.row);
  EXPECT_EQ (loc.col, neighbour.col);
}

TEST (Location, FindNeighbour_SeekEASTNeighbour_GetColPlus1)
{
  location_t loc;
  loc.row = 5;
  loc.col = 8;
  location_t neighbour;
  neighbour = Neighbour (loc, EAST);
  EXPECT_EQ (loc.row, neighbour.row);
  EXPECT_EQ (loc.col + 1, neighbour.col);
}

TEST (Location, FindNeighbour_SeekSOUTHNeighbour_GetRowMinus1)
{
  location_t loc;
  loc.row = 5;
  loc.col = 8;
  location_t neighbour;
  neighbour = Neighbour (loc, SOUTH);
  EXPECT_EQ (loc.row - 1, neighbour.row);
  EXPECT_EQ (loc.col, neighbour.col);
}

TEST (Location, FindNeighbour_SeekWESTNeighbour_GetColMinus1)
{
  location_t loc;
  loc.row = 5;
  loc.col = 8;
  location_t neighbour;
  neighbour = Neighbour (loc, WEST);
  EXPECT_EQ (loc.row, neighbour.row);
  EXPECT_EQ (loc.col - 1, neighbour.col);
}


TEST (Location, LocationInGoal)
{
  location_t goal = {12, 13};
  SetGoal (goal);
  location_t inGoal = goal;
  location_t notInGoal = {0, 0};
  EXPECT_TRUE (IsGoal (inGoal));
  EXPECT_FALSE (IsGoal (notInGoal));
}

TEST (Location, LocationInHome)
{
  location_t inHome = {0, 0};
  location_t notInHome = {0, 1};
  EXPECT_TRUE (IsHome (inHome));
  EXPECT_FALSE (IsHome (notInHome));
}

TEST (Location, Neighbour_WrapAroundEdges)
{
  location_t loc = Location (MazeWidth() - 1, MazeHeight() - 1);
  location_t neighbour;
  loc.col = MazeWidth() - 1;
  loc.row = MazeHeight() - 1;
  EXPECT_EQ (0, Neighbour (loc, NORTH).row);
  EXPECT_EQ (0, Neighbour (loc, EAST).col);
  loc.col = 0;
  loc.row = 0;
  EXPECT_EQ (MazeHeight() - 1, Neighbour (loc, SOUTH).row);
  EXPECT_EQ (MazeWidth() - 1, Neighbour (loc, WEST).col);
}

TEST (Location, Neighbour_BoundaryCases)
{
  location_t loc;
  location_t neighbour;
  int lastColumn = MazeWidth() - 1;
  int lastRow = MazeWidth() - 1;
  loc.col = lastColumn - 1;
  loc.row = lastRow - 1;
  EXPECT_EQ (lastRow, Neighbour (loc, NORTH).row);
  EXPECT_EQ (lastColumn, Neighbour (loc, EAST).col);
  loc.col = 1;
  loc.row = 1;
  EXPECT_EQ (0, Neighbour (loc, SOUTH).row);
  EXPECT_EQ (0, Neighbour (loc, WEST).col);
}

