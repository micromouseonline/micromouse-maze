/*
 * File:   mazeprinter.h
 * Author: peterharrison
 *
 * Created on 13 February 2016, 19:53
 */

#ifndef MAZEPRINTER_H
#define MAZEPRINTER_H

#include "maze.h"

class MazePrinter {
 public:
  static void printCDecl(Maze * maze, const char * name) ;
  static void printPlain(Maze * maze) ;
  static void printDirs(Maze * maze) ;
 private:
  MazePrinter() {}                             // Private constructor
  ~MazePrinter() {}
  MazePrinter(const MazePrinter&);             // Prevent copy-construction
  MazePrinter& operator=(const MazePrinter&);  // Prevent assignment
};

#endif /* MAZEPRINTER_H */

