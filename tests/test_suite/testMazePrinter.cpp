#include "gtest/gtest.h"


#include "maze.h"
#include "mazedata.h"
#include "mazeprinter.h"


class TestMazePrinter : public ::testing::Test {
 protected:
  Maze *maze;
  MazePrinter* printer;

  virtual void SetUp() {
    maze = new Maze(16);
    maze->resetToEmptyMaze();
  }

  virtual void TearDown() {
    delete maze;
  }

  virtual void copyClassicMaze(const uint8_t *mazeData) const {
    for (int cell = 0; cell < this->maze->numCells(); ++cell) {
      maze->copyCellFromFileData(cell, mazeData[cell]);
    }
  }
};

TEST_F (TestMazePrinter, PrintForCoverageTesting)
{
  copyClassicMaze(japan2007);
  maze->flood(maze->goal());
  maze->updateDirections();
  MazePrinter::printCDecl(maze,"julian");
  MazePrinter::printDirs(maze);
  MazePrinter::printPlain(maze);
}

