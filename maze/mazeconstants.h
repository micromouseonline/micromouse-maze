//
// Created by Peter Harrison on 26/05/2017.
//

#ifndef MAZE_MAZECONSTANTS_H
#define MAZE_MAZECONSTANTS_H

#include <stdint.h>



const uint8_t DEFAULT_GOAL = 0x77;
const uint16_t MAX_COST = UINT16_MAX;
const uint8_t BAD_DIRECTION = UINT8_MAX;


typedef uint16_t cellref_t;
typedef uint16_t cost_t;
typedef uint8_t walldata_t;
typedef uint8_t direction_t;


#define NORTH         (uint8_t)0x00
#define EAST          (uint8_t)0x01
#define SOUTH         (uint8_t)0x02
#define WEST          (uint8_t)0x03
#define NONE          (uint8_t)0x04
#define UNSEEN        (uint8_t)0x05
#define INVALID_DIRECTION (uint8_t)255


enum {
  DIR_N = 0,
  DIR_NE = 1,
  DIR_E = 2,
  DIR_SE = 3,
  DIR_S = 4,
  DIR_SW = 5,
  DIR_W = 6,
  DIR_NW = 7,
};

#define WALL_PRESENT    0x01
#define WALL_KNOWN      0x10

#define WALL_NORTH (WALL_PRESENT << (NORTH))
#define WALL_EAST  (WALL_PRESENT << (EAST))
#define WALL_SOUTH (WALL_PRESENT << (SOUTH))
#define WALL_WEST  (WALL_PRESENT << (WEST))

#define CHECKED_NORTH (WALL_KNOWN << (NORTH))
#define CHECKED_EAST  (WALL_KNOWN << (EAST))
#define CHECKED_SOUTH (WALL_KNOWN << (SOUTH))
#define CHECKED_WEST  (WALL_KNOWN << (WEST))

#define VISITED (CHECKED_NORTH + CHECKED_EAST + CHECKED_SOUTH + CHECKED_WEST)

#endif //MAZE_MAZECONSTANTS_H
