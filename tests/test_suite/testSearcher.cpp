#include "gtest/gtest.h"

#include "mazeprinter.h"
#include "mazesearcher.h"
#include "mazedata.h"
#include "maze.h"

class SearcherTest : public ::testing::Test {

  /* This gets run before each test */
  virtual void SetUp() {
    maze = new Maze(16);
    maze->copyMazeFromFileData(japan2007, 256);

    barney = new MazeSearcher;

//    MazePrinter::printPlain(&testMaze);
//    char testMazeName[] = "../mazefiles/minos03f.maz";
//    MazeResetWalls();
//    SetGoal (DefaultGoal());
//    FloodMazeClassic (DefaultGoal());
//    ReadRealWallsFromFile (testMazeName);
//    UpdateEntireMazeFromRealWalls ();
//    FloodMazeClassic (DefaultGoal());
//    MazeRemoveWall (Location (2, 0), NORTH);
//    EXPECT_EQ (0, Cost (DefaultGoal()));
//    EXPECT_EQ (46, Cost (Home()));
//    EXPECT_EQ (EAST, Direction (Location (2, 0)));
//    MouseInit();
  }

  virtual void TearDown() {
    delete barney;
    delete maze;
  }

 protected:
  MazeSearcher *barney;
  Maze *maze;
};

TEST_F (SearcherTest, Constructor) {
  EXPECT_EQ(0, barney->location());
  EXPECT_EQ(NORTH, barney->heading());
  EXPECT_EQ(NULL, barney->realMaze());
}

TEST_F (SearcherTest, MouseSetPosition_PositionAsSet) {
  barney->setLocation(0x99);
  EXPECT_EQ(0x99, barney->location());
}

TEST_F (SearcherTest, MouseSetHeading_HeadingAsSet) {
  barney->setHeading(EAST);
  EXPECT_EQ(EAST, barney->heading());
}


TEST_F (SearcherTest, moveWithMaze_ChangeLocationOnly) {
  barney->setMazeWalls(japan2007, 256);
  barney->setLocation(0x00);
  barney->setHeading(NORTH);
  barney->move();
  EXPECT_EQ(0x01, barney->location());
  EXPECT_EQ(NORTH,barney->heading());
}

TEST_F (SearcherTest, moveWithMaze_smallCircuitReturnToStart) {
  barney->setMazeWalls(japan2007, 256);
  barney->setLocation(0x39);
  barney->move();
  barney->setHeading(EAST);
  barney->move();
  barney->setHeading(SOUTH);
  barney->move();
  barney->setHeading(WEST);
  barney->move();
  barney->setHeading(NORTH);
  EXPECT_EQ(0x39, barney->location());
  EXPECT_EQ(NORTH,barney->heading());
}



/*
 * Tests whether the mouse can successfully follow a correctly setup
 * direction array and stop at the appropriate mLocation
 */
TEST_F (SearcherTest, MouseRunTo_EmptyMaze_StartToGoal_MouseAtGoal) {
  barney->setMazeWalls(emptyMaze, 256);
  int steps = barney->runTo(0x77);
  EXPECT_EQ(14,steps);
  EXPECT_EQ(0x77,barney->location()) << "{" << barney->location() << ", " << +barney->heading() << "}";
}

/*
 * Tests whether the mouse can successfully follow a correctly setup
 * direction array and stop at the appropriate mLocation
 */
TEST_F (SearcherTest, MouseRunTo_EmptyMaze_ToGoalFromAnywhere) {
  barney->setMazeWalls(japan2007, 256);
  maze->copyMazeFromFileData(japan2007,256);
  maze->flood(0x77);
  int steps = barney->runTo(0x77);
  EXPECT_EQ(72,steps);
  for(uint16_t loc = 0; loc < maze->numCells(); loc++) {
    barney->setLocation(loc);
    barney->setHeading(WEST);
    barney->runTo(0x77);
    EXPECT_EQ(0x77, barney->location()) << "{" << barney->location() << ", " << +barney->heading() << "}";
  }
}

/*
 * Tests whether the mouse can successfully follow a correctly setup
 * direction array and stop at the appropriate mLocation
 */
TEST_F (SearcherTest, MouseRunTo_EmptyMaze_ToStartFromAnywhere) {
  barney->setMazeWalls(japan2007, 256);
  maze->copyMazeFromFileData(japan2007,256);
  maze->flood(maze->home());
  barney->setLocation(0x01);
  int steps = barney->runTo(maze->home());
  EXPECT_EQ(1,steps);
  for(uint16_t loc = 1; loc < maze->numCells(); loc++) {
    barney->setLocation(loc);
    barney->setHeading(WEST);
    int steps = barney->runTo(maze->home());
    EXPECT_EQ(maze->home(), barney->location()) << "{" << barney->location() << ", " << +barney->heading() << "}";
    EXPECT_GT(steps,0);
  }
}

/*
 * Tests mouse getting lost in a cell with invalid direction
 * Taiwan2015 maze has closed in cells at 0x5C and 0x5D
 */
TEST_F (SearcherTest, MouseRunTo_RunToGoal_StartClosedIn_Error) {
  barney->setMazeWalls(taiwan2015, 256);
  barney->setLocation(0x5D);
  int steps = barney->runTo(maze->goal());
  EXPECT_EQ(int(MazeSearcher::E_NO_ROUTE),steps);
}

/*
 * Tests mouse getting lost in a cell with invalid direction
 * Taiwan2015 maze has closed in cells at 0x5C and 0x5D
 */
TEST_F (SearcherTest, MouseRunTo_RunToGoal_TargetClosedIn_Error) {
  barney->setMazeWalls(taiwan2015, 256);
  int steps = barney->runTo(0x5C);
  EXPECT_EQ(int(MazeSearcher::E_NO_ROUTE),steps);
}



/*
 * Tests mouse getting lost because path is too long
 * Simulate by setting target outside maze
 */
//TEST_F (SearcherTest, MouseRunTo_RunToGoal_TargetTooFar_Error) {
//  barney->setMazeWalls(taiwan2015, 256);
//  int steps = barney->runTo(0x200);
//  EXPECT_EQ(int(MazeSearcher::E_ROUTE_TOO_LONG),steps);
//}

/*
 * Tests mouse search
 */
TEST_F (SearcherTest, MouseSearchTo_EmptyMaze_Success) {
  Maze * testMaze = new Maze(16);
  testMaze->setWall(0x07,EAST);
  barney->setRealMaze(testMaze);
  maze->setFloodType(Maze::MANHATTAN_FLOOD);
  int steps = barney->searchTo(0x77);
  EXPECT_EQ(16,steps);
}


/*
 * verbose mode prints out the maze after each step.
 */
TEST_F (SearcherTest, MouseRunTo_SearchToTarget_VerboseMode) {
  Maze * testMaze = new Maze(16);
  barney->setRealMaze(testMaze);
  //barney->setVerbose(true);
  barney->maze()->setFloodType(Maze::MANHATTAN_FLOOD);
  int steps = barney->searchTo(0x7);
  EXPECT_EQ(7,steps);
}


/*
 *
 */
TEST_F (SearcherTest, MouseRunTo_SearchToTarget_ManhattanFlood) {
  barney->setRealMaze(maze);
  barney->maze()->setFloodType(Maze::MANHATTAN_FLOOD);
  int steps = barney->searchTo(0x77);
  EXPECT_EQ(130,steps);
//  MazePrinter::printVisitedDirs(barney->maze());
}


/*
 *
 */
TEST_F (SearcherTest, MouseSearchToTarget_RunLengthFlood) {
  barney->setRealMaze(maze);
  barney->maze()->setFloodType(Maze::RUNLENGTH_FLOOD);
  int steps = barney->searchTo(0x77);
  EXPECT_EQ(142,steps);
//  MazePrinter::printVisitedDirs(barney->maze());
}


/*
 *
 */
TEST_F (SearcherTest, MouseSearchToTarget_LeftWall_Fail) {
  maze->copyMazeFromFileData(emptyMaze,256);
  barney->setVerbose(false);
  barney->setRealMaze(maze);
  barney->maze()->setFloodType(Maze::RUNLENGTH_FLOOD);
  barney->setSearchMethod(MazeSearcher::SEARCH_LEFT_WALL);
  int steps = barney->searchTo(0x77);
  EXPECT_EQ(MazeSearcher::E_ROUTE_TOO_LONG,steps);
}

/*
 *
 */
TEST_F (SearcherTest, MouseSearchToTarget_LeftWall_Succeed) {
  maze->copyMazeFromFileData(japan2007,256);
  barney->setRealMaze(maze);
  barney->maze()->setFloodType(Maze::RUNLENGTH_FLOOD);
  barney->setSearchMethod(MazeSearcher::SEARCH_LEFT_WALL);
  int steps = barney->searchTo(0x77);
  EXPECT_EQ(84,steps);
}




/*
 *
 */
TEST_F (SearcherTest, MouseRunTo_SearchOutAndIn_RunLengthFlood) {
  barney->setRealMaze(maze);
  maze->copyMazeFromFileData(japan2007,256);
  int steps = 0;
  std::cout << "\n\nRunlength pass 0: ";
  barney->maze()->testForSolution();
  std::cout << barney->maze()->costDifference() << "  " << steps << " steps" << std::endl;
  barney->maze()->setFloodType(Maze::RUNLENGTH_FLOOD);
  steps += barney->searchTo(0x77);
  steps += barney->searchTo(0x00);
  EXPECT_EQ(228,steps) << "The solution is not always correct. This is not right";
  barney->maze()->testForSolution();
  std::cout << "Runlength pass 1: ";
  std::cout << barney->maze()->costDifference() << "  " << steps << " steps" << std::endl;
  steps += barney->searchTo(0x77);
  steps += barney->searchTo(0x00);
  barney->maze()->testForSolution();
  std::cout << "Runlength pass 2: ";
  std::cout << barney->maze()->costDifference() << "  " << steps << " steps" << std::endl;
}


/*
 *
 */
TEST_F (SearcherTest, MouseRunTo_SearchOutAndIn_ManhattanFlood) {
  barney->setRealMaze(maze);
  barney->maze()->setFloodType(Maze::MANHATTAN_FLOOD);
  int steps=0;
  std::cout << "\n\nManhattan pass 0: ";
  barney->maze()->testForSolution();
  std::cout << barney->maze()->costDifference() << "  " << steps << " steps" << std::endl;
  steps += barney->searchTo(0x77);
  steps += barney->searchTo(0x00);
  EXPECT_EQ(208,steps) << "The solution is not always correct. This is not right";
  //MazePrinter::printVisitedDirs(barney->maze());
  barney->maze()->testForSolution();
  std::cout << "Manhattan pass 1: ";
  std::cout << barney->maze()->costDifference() << "  " << steps << " steps" << std::endl;
  steps += barney->searchTo(0x77);
  steps += barney->searchTo(0x00);
  barney->maze()->testForSolution();
  std::cout << "Manhattan pass 2: ";
  std::cout << barney->maze()->costDifference() << "  " << steps << " steps" << std::endl;
}





