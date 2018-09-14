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


#ifndef MAZEPRINTER_H
#define MAZEPRINTER_H

#include "maze.h"

class MazePrinter {
public:
  static void printCDecl(Maze *maze, const char *name);
  static void printRawDecl(Maze *maze, const char *name);
  static void printPlain(Maze *maze);
  static void printCosts(Maze *maze);
  static void printDirs(Maze *maze);
  static void printVisitedDirs(Maze *maze);
private:
  MazePrinter() = default;                             // Private constructor
  ~MazePrinter() = default;

  MazePrinter(const MazePrinter &);             // Prevent copy-construction
  MazePrinter &operator=(const MazePrinter &);  // Prevent assignment
};

#endif /* MAZEPRINTER_H */

