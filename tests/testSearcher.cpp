#include "gtest/gtest.h"
#include "maze.h"
#include "mazeflooder.h"
#include "mazereader.h"
#include "mazeprinter.h"
#include "mazesearcher.h"


class SearcherTest : public ::testing::Test
{

  /* This gets run before each test */
  virtual void SetUp()
  {
    MazeResetWalls();
    SetGoal (DefaultGoal());
    FloodMazeClassic (DefaultGoal());
    LoadMAZFile ("mazefiles/minos03f.maz");
    FloodMazeClassic (DefaultGoal());
    MazeRemoveWall (Location (2, 0), NORTH);
    EXPECT_EQ (0, Cost (DefaultGoal()));
    EXPECT_EQ (46, Cost (Home()));
    EXPECT_EQ (EAST, Direction (Location (2, 0)));
    MouseInit();
  }

  virtual void TearDown() { }
};

TEST_F (SearcherTest, Mouse_Initialised)
{
  MouseInit();
  EXPECT_EQ (NORTH, MouseHeading());
  EXPECT_EQ (0, MousePosition().row);
  EXPECT_EQ (0, MousePosition().col);
}

TEST_F (SearcherTest, MouseSetPosition_PositionAsSet)
{
  MouseSetPosition (Location (3, 9));
  EXPECT_EQ (3, MousePosition().row);
  EXPECT_EQ (9, MousePosition().col);
}

TEST_F (SearcherTest, MouseSetHeading_HeadingAsSet)
{
  MouseSetHeading (WEST);
  EXPECT_EQ (WEST, MouseHeading());
}


TEST_F (SearcherTest, MouseMove_NewPosition_IsNeighbourFromHeading)
{

  MouseSetPosition (Location (9, 12));
  MouseSetHeading (EAST);
  MouseMove();
  EXPECT_EQ (9, MousePosition().row);
  EXPECT_EQ (13, MousePosition().col);

  MouseSetHeading (SOUTH);
  MouseMove();
  EXPECT_EQ (8, MousePosition().row);
  EXPECT_EQ (13, MousePosition().col);

  MouseSetHeading (WEST);
  MouseMove();
  EXPECT_EQ (8, MousePosition().row);
  EXPECT_EQ (12, MousePosition().col);

  MouseSetHeading (NORTH);
  MouseMove();
  EXPECT_EQ (9, MousePosition().row);
  EXPECT_EQ (12, MousePosition().col);

}
/*
 * Tests whether the mouse can successfully follow a correctly setup
 * direction array and stop at the appropriate location
 */
TEST_F (SearcherTest, MouseRunTo_StartToGoal_MouseAtGoal)
{
  MouseInit();
  SetGoal (DefaultGoal());
  MouseRunTo (Goal());
  EXPECT_TRUE (Goal().row == MousePosition().row) << "{" << MousePosition().row << ", " << MousePosition().col << "}";
  EXPECT_TRUE (Goal().col == MousePosition().col) << "{" << MousePosition().row << ", " << MousePosition().col << "}";
}

