/*
 * File:   mazeprinter.h
 * Author: peterharrison
 *
 * Created on 13 February 2016, 19:53
 */

#ifndef MAZEPRINTER_H
#define MAZEPRINTER_H
#include "maze.h"


typedef enum {
  WALLS = 0,
  COSTS = 1,
  DIRS = 2
} print_options_t;

void PrintMaze (print_options_t option);
void PrintMaze (Maze * maze,print_options_t option);



#endif /* MAZEPRINTER_H */

