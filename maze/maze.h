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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/*
 * this is a maximum for data allocation
 * the working size of the maze could be up to this value
 */
#define MAZE_ROWS  16
#define MAZE_COLS 16

/* used for directions and wall identification */
#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3
#define INVALID 4


/* TODO: hide all these macros by creating functions in maze.c */
/* bit masks for the wall data */
#define WALL       ((walls_t)0x01)
#define NO_WALLS   ((walls_t)0x00)
#define NORTH_WALL (WALL << NORTH)
#define EAST_WALL  (WALL << EAST)
#define SOUTH_WALL (WALL << SOUTH)
#define WEST_WALL  (WALL << WEST)
#define ALL_WALLS (NORTH_WALL + EAST_WALL + SOUTH_WALL + WEST_WALL)
#define WALL_SEEN  ((walls_t)0x10)
#define NORTH_SEEN (WALL_SEEN << NORTH)
#define EAST_SEEN  (WALL_SEEN << EAST)
#define SOUTH_SEEN (WALL_SEEN << SOUTH)
#define WEST_SEEN  (WALL_SEEN << WEST)

#define ALL_SEEN (NORTH_SEEN + EAST_SEEN + SOUTH_SEEN + WEST_SEEN)
#define VISITED ALL_SEEN



/* one day diagonals may make this 8 */
#define DIRECTION_COUNT 4
typedef uint8_t walls_t;

typedef uint8_t direction_t;

typedef uint16_t cost_t;
#define MAX_COST UINT16_MAX

typedef struct {
  int8_t row;
  int8_t col;
} location_t;

/* ========== manipulating the maze ==============*/

uint8_t MazeWidth (void);
uint8_t MazeHeight (void);

/*
 * Set up the working maze with wall information for a classic 16x16 empty
 * maze. That is, walls around the outsides and to the East of the home
 * cell
 */
void MazeInit (void);

/*
 * clear the costs and directions
 * set the walls to the outside and start cell walls only
 */
void MazeResetWalls (void);

/* set a single wall - looks after neighbours - set seen*/
void MazeAddWall (location_t location, direction_t direction);

/* set all four walls for a location - updates neighbours - set seen*/
void UpdateCellFromWallData (location_t location, walls_t walls);

/* clear a single wall - looks after neighbours - set seen*/
void MazeRemoveWall (location_t location, direction_t direction);


/* return all the walls for a given location */
walls_t Walls (location_t location);

bool Visited (location_t location);

/* return true if there is no wall in the given direction */
bool HasExit (location_t location, direction_t direction);


/* ========== manipulating the cost ==============*/
cost_t Cost (location_t location);
void SetCost (location_t location, cost_t cost);
void MazeResetCosts (void);


/* ========== manipulating the locations ==============*/
void SetGoal (location_t location);
location_t Location (uint8_t row, uint8_t col);
location_t DefaultGoal (void);
location_t Goal (void);
location_t Home (void);
location_t Neighbour (location_t location, direction_t direction);
bool IsGoal (location_t location);
bool IsHome (location_t location);

/* ========== manipulating the walls ==============*/
bool WallIsSeen (walls_t walls, direction_t direction);
bool WallExists (walls_t walls, direction_t direction);

/* setting and clearing always sets the seen bits */
/* clear all the walls and the seen bits */
walls_t WallsNone (void);
void WallSet (walls_t * walls, direction_t direction);
void WallClear (walls_t * walls, direction_t direction);



/* ========== manipulating the directions ==============*/
void MazeResetDirections (void);
void SetDirection (location_t location, direction_t direction);
direction_t Direction (location_t location);
/* handy utilities for directions */
direction_t LeftFrom (direction_t direction);
direction_t RightFrom (direction_t direction);
direction_t Behind (direction_t direction);

direction_t SmallestNeighbourDirection (location_t loc);

#ifdef __cplusplus
}
#endif

#endif /* MAZE_H */

