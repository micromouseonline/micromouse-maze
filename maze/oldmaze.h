/*
 * File:   maze.h
 * Author: peterharrison
 *
 * Created on 08 February 2016, 00:09
 *
 * This module concerns itself only with the direct manipulation of the maze
 * data structures:
 *  - setting and clearing walls
 *  - testing walls
 *  - setting and getting costs
 *  - setting and getting directions
 *  - providing utilities like finding a neighbour location
 *
 * There should be no global variables in here,
 * only functions, types and constants
 * instance variables will be declared static in maze.c allowing implemenation
 * to be changed without affecting API
 */

#ifndef MAZE_H
#define MAZE_H

#include <stdint.h>
#include <stdbool.h>
#include "mazeconstants.h"
#include "mazedata.h"


const uint16_t MAZEWIDTH = 16;
const uint16_t MAZE_ROWS = 16;
const uint16_t MAZE_COLS = 16;
const uint16_t NUMCELLS = (MAZE_ROWS * MAZE_COLS);


const uint8_t DIRECTION_COUNT = 4;



typedef struct {
  int8_t row;
  int8_t col;
} location_t;



/* ========== manipulating the maze ==============*/

uint8_t MazeWidth(void);
uint8_t MazeHeight(void);

/*
 * Set up the working maze with wall information for a classic 16x16 empty
 * maze. That is, walls around the outsides and to the East of the home
 * cell
 */
void MazeInit(void);

/*
 * clear the costs and directions
 * set the walls to the outside and start cell walls only
 */
void MazeResetWalls(void);

/* set a single wall - looks after neighbours - set seen*/
void MazeAddWall(location_t location, direction_t direction);

/* set all four walls for a location - updates neighbours - set seen*/
void UpdateCellFromWallData(location_t location, walls_t walls);

/* clear a single wall - looks after neighbours - set seen*/
void MazeRemoveWall(location_t location, direction_t direction);

/* return a pointer to the walldata at a given location */
walls_t *wallsPointer(location_t location);

/* return the actual wall data for a given location */
walls_t Walls(location_t location);

bool Visited(location_t location);

/* return true if there is no wall in the given direction */
bool HasExit(location_t location, direction_t direction);


/* ========== manipulating the cost ==============*/
cost_t Cost(location_t location);
void SetCost(location_t location, cost_t cost);
void MazeResetCosts(void);


/* ========== manipulating the locations ==============*/
void SetGoal(location_t location);
location_t Location(uint8_t row, uint8_t col);
location_t DefaultGoal(void);
location_t Goal(void);
location_t Home(void);
location_t Neighbour(location_t location, direction_t direction);
bool IsGoal(location_t location);
bool IsHome(location_t location);

/* ========== manipulating the walls ==============*/
bool WallIsSeen(walls_t walls, direction_t direction);
bool WallExists(walls_t walls, direction_t direction);

/* setting and clearing always sets the seen bits */
/* clear all the walls and the seen bits */
walls_t WallsNone(void);
void WallSet(walls_t *walls, direction_t direction);
void WallClear(walls_t *walls, direction_t direction);


/* ========== manipulating the directions ==============*/
void MazeResetDirections(void);
void SetDirection(location_t location, direction_t direction);
direction_t Direction(location_t location);
/* handy utilities for directions */
direction_t LeftFrom(direction_t direction);
direction_t RightFrom(direction_t direction);
direction_t Behind(direction_t direction);

direction_t SmallestNeighbourDirection(location_t loc);

#endif /* MAZE_H */

