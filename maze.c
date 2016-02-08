/* 
 * File:   maze.c
 * Author: peterharrison
 *
 * Created on 08 February 2016, 00:09
 */

#include <stdint.h>
#include "maze.h"

walls_t walls[MAZE_WIDTH * MAZE_WIDTH];
cost_t cost[MAZE_WIDTH * MAZE_WIDTH];
direction_t direction[MAZE_WIDTH * MAZE_WIDTH];

