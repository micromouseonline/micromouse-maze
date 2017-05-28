#include "gtest/gtest.h"
#include "oldmaze.h"
#include "mazeflooder.h"
#include "mazereader.h"
#include "mazeprinter.h"
#include "mazesearcher.h"

#include "maze.h"


class SearcherTest : public ::testing::Test
{

  /* This gets run before each test */
  virtual void SetUp()
  {
    char testMazeName[] = "../mazefiles/minos03f.maz";
    MazeResetWalls();
    SetGoal (DefaultGoal());
    FloodMazeClassic (DefaultGoal());
    ReadRealWallsFromFile (testMazeName);
    UpdateEntireMazeFromRealWalls ();
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

/*
 * Tests mouse getting lost in a cell with invalid direction
 */
TEST_F (SearcherTest, MouseRunTo_StartToGoal_LostAt10)
{
  MouseInit();
  SetGoal (DefaultGoal());
  SetDirection (Location (1, 0), INVALID);
  MouseRunTo (Goal());
  EXPECT_TRUE (1 == MousePosition().row) ;
  EXPECT_TRUE (0 == MousePosition().col) ;
}

/*
 * Tests mouse getting lost when direction array corrupt
 */
TEST_F (SearcherTest, MouseRunTo_StartToGoal_LostWithNoDirection)
{
  MouseInit();
  SetGoal (DefaultGoal());
  SetDirection (Location (1, 0), -1);
  MouseRunTo (Goal());
  EXPECT_TRUE (1 == MousePosition().row) ;
  EXPECT_TRUE (0 == MousePosition().col) ;
}



/*
 * Tests mouse search using full flood
 */
TEST_F (SearcherTest, MouseSearchTo_FullFlood_StartToGoal_Success)
{
  char fileName[] = "../mazefiles/minos03f.maz";
  int stepsTaken = 0;
  ReadRealWallsFromFile (fileName);
  MazeInit();
  FloodMazeClassic (DefaultGoal());	/* seed the costs and directions */
  MouseInit();
  SetGoal (DefaultGoal());
  stepsTaken = MouseSearchToFullFlood (DefaultGoal());
  EXPECT_GT (500, stepsTaken);
  EXPECT_TRUE (DefaultGoal().row == MousePosition().row) ;
  EXPECT_TRUE (DefaultGoal().col == MousePosition().col) ;
}


/*
 * Tests mouse search using Modified flood
 */
TEST_F (SearcherTest, MouseSearchTo_ModifiedFlood_StartToGoal_Success)
{
  char fileName[] = "../mazefiles/minos03f.maz";
  int stepsTaken = 0;
  ReadRealWallsFromFile (fileName);
  MazeInit();
  FloodMazeClassic (DefaultGoal());	/* seed the costs and directions */
  MouseInit();
  SetGoal (DefaultGoal());
  stepsTaken = MouseSearchToModifiedFlood (DefaultGoal());
  EXPECT_GT (500, stepsTaken);
  EXPECT_TRUE (DefaultGoal().row == MousePosition().row) ;
  EXPECT_TRUE (DefaultGoal().col == MousePosition().col) ;
}

/*
 * Tests mouse search using Modified flood with no route
 * The test maze has only two open cells at the start
 */
TEST_F (SearcherTest, MouseSearchTo_ModifiedFlood_StartToGoal_NORoute)
{
  char fileName[] = "../mazefiles/map-y7.maz";
  int stepsTaken = 0;
  ReadRealWallsFromFile (fileName);
  MazeInit();
  FloodMazeClassic (DefaultGoal());	/* seed the costs and directions */
  MouseInit();
  SetGoal (DefaultGoal());
  stepsTaken = MouseSearchToModifiedFlood (DefaultGoal());
  EXPECT_LT (500, stepsTaken);
  EXPECT_EQ (1, MousePosition().row) ;
  EXPECT_EQ (0, MousePosition().col) ;
}

/*
 * Tests mouse search using Modified flood with no route
 * The test maze has only two open cells at the start
 */
TEST_F (SearcherTest, MouseSearchTo_FullFlood_StartToGoal_NORoute)
{
  char fileName[] = "../mazefiles/map-y7.maz";
  int stepsTaken = 0;
  ReadRealWallsFromFile (fileName);
  MazeInit();
  FloodMazeClassic (DefaultGoal());	/* seed the costs and directions */
  MouseInit();
  SetGoal (DefaultGoal());
  stepsTaken = MouseSearchToFullFlood (DefaultGoal());
  EXPECT_EQ (1, stepsTaken);
  EXPECT_EQ (1, MousePosition().row) ;
  EXPECT_EQ (0, MousePosition().col) ;
}






