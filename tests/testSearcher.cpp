#include "gtest/gtest.h"
#include "maze.h"
#include "mazeflooder.h"
#include "mazereader.h"
#include "mazeprinter.h"


class SearcherTest : public ::testing::Test
{

  virtual void SetUp()
  {
    MazeResetWalls();
    FloodMazeClassic (DefaultGoal());
    LoadMAZFile ("mazefiles/minos03f.maz");
    FloodMazeClassic (DefaultGoal());
    MazeRemoveWall (Location (2, 0), NORTH);
    EXPECT_EQ (0, Cost (DefaultGoal()));
    EXPECT_EQ (46, Cost (Home()));
    EXPECT_EQ (EAST, Direction (Location (2, 0)));
  }

  virtual void TearDown() { }
};

TEST_F (SearcherTest, SetupTest)
{
  /* maze is loaded and flooded by the setup */
  SetCost(Location(0,0),100);
  EXPECT_EQ(100,Cost(Location(0,0)));

}


TEST_F(SearcherTest,test){
  EXPECT_EQ(100,Cost(Location(0,0)));
  
  
}