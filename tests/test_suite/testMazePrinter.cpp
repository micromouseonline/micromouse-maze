/************************************************************************
*
* Copyright (C) 2017 by Peter Harrison. www.micromouseonline.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without l> imitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
************************************************************************/



#include "gtest/gtest.h"


#include "maze.h"
#include "mazedata.h"
#include "mazeprinter.h"
#include "mazefiler.h"



class TestMazePrinter : public ::testing::Test {
protected:
  Maze *maze;


  virtual void SetUp() {
    maze = new Maze(16);
    maze->reset_to_empty();

  }

  virtual void TearDown() {
    delete maze;
  }

};

/*
 * It is not clear how best to test the results of the libMaze printing
 * except by visual inspection.
 */
TEST_F(TestMazePrinter, PrintForCoverageTesting) {
  //  return;
  //  MazePrinter::printVisitedDirs(libMaze);
  //  copyClassicMaze(japan2007ef);
  maze->set_from_file_data(japan2007ef, 256);
  maze->flood(maze->goal(), MASK_OPEN);
  //  MazePrinter::printDirs(maze);
  //  MazePrinter::printPlain(maze);
  //  MazePrinter::printCDecl(maze, "julian");
  //  MazePrinter::printCosts(maze);
  //  MazePrinter::printVisitedDirs(maze);
}
TEST_F(TestMazePrinter, PrintClassicWithGoal) {
  MazeFiler filer;
  char name[] = "mazefiles/classic/japan2013ef.txt";
  filer.readMaze(maze, name);
  //  MazePrinter::printPlain(maze);
  //  MazePrinter::printCDecl(maze, "japan2013");

}

