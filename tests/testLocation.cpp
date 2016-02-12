#include "gtest/gtest.h"
#include "maze.h"


TEST(Location,Initialising_SetToRow7Col8){
  location_t loc = MazeGetGoal();
  EXPECT_EQ(7,loc.row);
  EXPECT_EQ(8,loc.col);
}

TEST(Location,SetAndFetchFGoal_SetGoal_ReturnGoal){
  location_t newGoal;
  newGoal.row = 3;
  newGoal.col = 4;
  location_t goal;
  MazeSetGoal(newGoal);
  goal = MazeGetGoal();
  EXPECT_EQ(newGoal.row,goal.row);
  EXPECT_EQ(newGoal.col,goal.col);
}

TEST(Location,FindNeighbour_SeekNORTHNeighbour_GetRowPlus1){
  location_t loc;
  loc.row = 5;
  loc.col = 8;
  location_t neighbour;
  neighbour = LocationGetNeighbour(loc, NORTH);
  EXPECT_EQ(loc.row+1,neighbour.row);
  EXPECT_EQ(loc.col,neighbour.col);
}

TEST(Location,FindNeighbour_SeekEASTNeighbour_GetColPlus1){
  location_t loc;
  loc.row = 5;
  loc.col = 8;
  location_t neighbour;
  neighbour = LocationGetNeighbour(loc, EAST);
  EXPECT_EQ(loc.row,neighbour.row);
  EXPECT_EQ(loc.col+1,neighbour.col);
}

TEST(Location,FindNeighbour_SeekSOUTHNeighbour_GetRowMinus1){
  location_t loc;
  loc.row = 5;
  loc.col = 8;
  location_t neighbour;
  neighbour = LocationGetNeighbour(loc, SOUTH);
  EXPECT_EQ(loc.row-1,neighbour.row);
  EXPECT_EQ(loc.col,neighbour.col);
}

TEST(Location,FindNeighbour_SeekWESTNeighbour_GetColMinus1){
  location_t loc;
  loc.row = 5;
  loc.col = 8;
  location_t neighbour;
  neighbour = LocationGetNeighbour(loc, WEST);
  EXPECT_EQ(loc.row,neighbour.row);
  EXPECT_EQ(loc.col-1,neighbour.col);
}


TEST(Location,LocationInGoal){
  location_t goal = {12,13};
  MazeSetGoal(goal);
  location_t inGoal = goal;
  location_t notInGoal = {0,0};
  EXPECT_TRUE(LocationIsInGoal(inGoal));
  EXPECT_FALSE(LocationIsInGoal(notInGoal)); 
}

TEST(Location,LocationInHome){
  location_t inHome = {0,0};
  location_t notInHome = {0,1};
  EXPECT_TRUE(LocationIsInHome(inHome));
  EXPECT_FALSE(LocationIsInHome(notInHome)); 
}

