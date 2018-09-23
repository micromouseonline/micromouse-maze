/***********************************************************************
 * Created by Peter Harrison on 17/09/2018.
 * Copyright (c) 2018 Peter Harrison
 *
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
 **************************************************************************/



#include "gtest/gtest.h"
#include "mazeprinter.h"
#include "mazedata.h"
#include "maze.h"
/////////////////////

class MazeTestHalfSize : public ::testing::Test {
protected:
  Maze *maze;
  bool withPrint = false;
  virtual void SetUp() {
    maze = new Maze(32);
    maze->resetToEmptyMaze();
  }

  virtual void TearDown() {
    delete maze;
  }

};



TEST_F(MazeTestHalfSize, TestTemplate) {
}


TEST_F(MazeTestHalfSize, copyHalfSize) {
  maze->copyMazeFromFileData(japan2014ef_half, 1024);
  maze->setGoal(837);
  if (withPrint) {
    MazePrinter::printPlain(maze);
  }

}
TEST_F(MazeTestHalfSize, printHalfSize) {

  return;

  maze->copyMazeFromFileData(japan2011ef_half, 1024);
  printf("\n\nJapan 2011 Final Half Size");
  MazePrinter::printPlain(maze);




  maze->copyMazeFromFileData(japan2014ef_half, 1024);
  printf("\n\nJapan 2014 Final Half Size");
  MazePrinter::printPlain(maze);

  maze->copyMazeFromFileData(japan2015ef_half, 1024);
  printf("\n\nJapan 2015 Final Half Size");
  MazePrinter::printPlain(maze);


  maze->copyMazeFromFileData(japan2016ef_half, 1024);
  printf("\n\nJapan 2016 Final Half Size");
  MazePrinter::printPlain(maze);


  maze->copyMazeFromFileData(japan2017ef_half, 1024);
  printf("\n\nJapan 2017 Final Half Size");
  MazePrinter::printPlain(maze);


  maze->copyMazeFromFileData(japan2010ef_half, 1024);
  printf("\n\nSJ_H Japan 2010 Final Half Size");
  MazePrinter::printPlain(maze);

  maze->copyMazeFromFileData(japan2012ef_half, 1024);
  printf("\n\nSJ_H Japan 2012 Final Half Size");
  MazePrinter::printPlain(maze);


  maze->copyMazeFromFileData(taiwan2014ef_half, 1024);
  printf("\n\nSJ_H Taiwan 2014 Final Half Size");
  MazePrinter::printPlain(maze);

  maze->copyMazeFromFileData(taiwan2015ef_half, 1024);
  printf("\n\nSJ_H Taiwan 2015 Final Half Size");
  MazePrinter::printPlain(maze);

  maze->copyMazeFromFileData(taiwan2017ef_half, 1024);
  printf("\n\nSJ_H Taiwan 2017 Final Half Size");
  MazePrinter::printPlain(maze);



}

TEST_F(MazeTestHalfSize, FloodHalfSize) {
  maze->copyMazeFromFileData(japan2014ef_half, 1024);
  maze->setGoal(837);
  maze->flood(837);
  if (withPrint) {
    MazePrinter::printDirs(maze);
  }
  maze->copyMazeFromFileData(japan2011ef_half, 1024);
  maze->setGoal(827);
  maze->flood((maze->goal()));
  if (withPrint) {
    MazePrinter::printDirs(maze);
  }

}
