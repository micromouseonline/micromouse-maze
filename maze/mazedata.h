/**
 *  \file mazedata.h
 *  \brief contains sample mazes for testing
 * *
 *  \version
 *  \date 15 Apr 2017
 *  \author peterharrison
 *  \bug No known bugs.
 */

#ifndef MAZEDATA_H
#define MAZEDATA_H

#include <stdint.h>
extern const uint8_t testMaze8x8[];
extern const uint8_t testMaze5x5[];    // small pathfinder test maze
extern const uint8_t testMaze1[];      // simple single short route
extern const uint8_t testmaze2[];      // two routes - favours runlength flood
extern const uint8_t taiwan2015[];
extern const uint8_t practice_maze[];
extern const uint8_t emptyMaze[];
extern const uint8_t japan2007[];      // has a wall-following solution!
extern const uint8_t diag_test_maz[];
extern const uint8_t test1_maz[];
extern const uint8_t japan_2014_heat[];

#endif    /* MAZEDATA_H */

