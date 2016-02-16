/*
 * File:   mazeprinter.h
 * Author: peterharrison
 *
 * Created on 13 February 2016, 19:53
 */

#ifndef MAZEPRINTER_H
#define MAZEPRINTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
  
typedef enum {
  COSTS = 1,
  DIRS = 2
} print_options_t;

void PrintMaze (print_options_t option);


#ifdef __cplusplus
}
#endif

#endif /* MAZEPRINTER_H */

