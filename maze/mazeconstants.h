//
// Created by Peter Harrison on 26/05/2017.
//

#ifndef MAZE_MAZECONSTANTS_H
#define MAZE_MAZECONSTANTS_H

#include <stdint.h>


#define NOINIT


const uint8_t DEFAULT_GOAL = 0x77;
const uint16_t MAX_COST = UINT16_MAX;
const uint16_t UNREACHABLE = UINT16_MAX;
const uint8_t BAD_DIRECTION = UINT8_MAX;


typedef uint16_t cellref_t;
typedef uint16_t cost_t;
typedef uint8_t walldata_t;
typedef uint8_t direction_t;


#define NORTH         (uint8_t)0x00
#define EAST          (uint8_t)0x01
#define SOUTH         (uint8_t)0x02
#define WEST          (uint8_t)0x03

#define WALL_PRESENT    1
#define WALL_KNOWN      2

#define WALL_NORTH (WALL_PRESENT << (2*NORTH))
#define WALL_EAST  (WALL_PRESENT << (2*EAST))
#define WALL_SOUTH (WALL_PRESENT << (2*SOUTH))
#define WALL_WEST  (WALL_PRESENT << (2*WEST))

#define CHECKED_NORTH (WALL_KNOWN << (2*NORTH))
#define CHECKED_EAST  (WALL_KNOWN << (2*EAST))
#define CHECKED_SOUTH (WALL_KNOWN << (2*SOUTH))
#define CHECKED_WEST  (WALL_KNOWN << (2*WEST))

#define VISITED (CHECKED_NORTH + CHECKED_EAST + CHECKED_SOUTH + CHECKED_WEST)

#endif //MAZE_MAZECONSTANTS_H
