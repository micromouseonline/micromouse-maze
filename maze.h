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
#define MAZE_WIDTH  16
#define MAZE_HEIGHT 16

  /* used for directions and wall identification */
#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3
  /* one day diagonals may make this 8 */
#define DIRECTION_COUNT 4

  /* bit masks for the wall data */
#define NORTH_WALL (1 << NORTH)
#define EAST_WALL  (1 << EAST)
#define SOUTH_WALL (1 << SOUTH)
#define WEST_WALL  (1 << WEST)
#define ALL_WALLS (NORTH_WALL + EAST_WALL + SOUTH_WALL + WEST_WALL)
#define WALL_SEEN 4  
#define NORTH_WALL_SEEN (1 << (NORTH + WALL_SEEN))
#define EAST_WALL_SEEN  (1 << (EAST  + WALL_SEEN))
#define SOUTH_WALL_SEEN (1 << (SOUTH + WALL_SEEN)
#define WEST_WALL_SEEN  (1 << (WEST  + WALL_SEEN))

#define ALL_WALLS_SEEN (ALL_WALLS << WALL_SEEN)
#define VISITED ALL_WALLS_SEEN

  typedef uint8_t walls_t;
  typedef uint8_t direction_t;
  typedef uint16_t cost_t;
  typedef uint16_t location_t;

  /* ========== manipulating the maze ==============*/

  void MazeSetWidth(uint8_t width);
  uint8_t MazeWidth(void);

  /* 
   * clear the costs and directions
   * set the walls to the outside and start cell walls only
   */
  void MazeResetData(void);

  /* set a single wall - looks after neighbours - set seen*/
  void MazeSetWall(location_t location, direction_t direction);

  /* set all four walls for a location - updates neighbours - set seen*/
  void MazeSetAllWalls(location_t location, walls_t walls);

  /* clear a single wall - looks after neighbours - set seen*/
  void MazeClearWall(location_t location, direction_t direction);

  /* set all four walls for a location  - updates neighbours - set seen*/
  void MazeClearAllWalls(location_t location, walls_t walls);

  /* return all the walls for a given location */
  walls_t MazeGetWalls(location_t location);

  /* ========== manipulating the locations ==============*/
  void MazeSetGoal(location_t location);
  location_t MazeGetGoal(void);
  location_t LocationGetNeighbour(location_t location, direction_t direction);
  bool LocationIsInGoal(location_t location);
  bool LocationIsInHome(location_t location);
  
  /* ========== manipulating the cost ==============*/
  cost_t MazeGetCost(location_t location);
  void MazeSetCost(location_t location, cost_t cost);
  
  /* ========== manipulating the walls ==============*/
  bool WallIsSeen(walls_t walls, direction_t direction);
  bool WallIsSet(walls_t walls, direction_t direction);
  
  /* setting and clearing always sets the seen bits */
  void WallSet(walls_t * walls, direction_t direction);
  void WallClear(walls_t * walls, direction_t direction);
  
  /* ========== manipulating the directions ==============*/
  void MazeSetDirection(location_t location, direction_t direction);
  direction_t MazeGetDirection(location_t location);
  /* handy utilities for directions */
  direction_t DirectionGetLeftFrom(direction_t direction);
  direction_t DirectionGetRightFrom(direction_t direction);
  direction_t DirectionGetBehindFrom(direction_t direction);

#ifdef __cplusplus
}
#endif

#endif /* MAZE_H */

