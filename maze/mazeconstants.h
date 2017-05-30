//
// Created by Peter Harrison on 26/05/2017.
//

#ifndef MAZE_MAZECONSTANTS_H
#define MAZE_MAZECONSTANTS_H

#include <stdint.h>


#define NOINIT

typedef uint8_t walls_t;
typedef uint8_t direction_t;
typedef uint16_t cost_t;

const uint8_t DEFAULT_GOAL = 0x77;
const uint16_t MAX_COST = UINT16_MAX;
const uint16_t UNREACHABLE = UINT16_MAX;
const uint8_t INVALID = UINT8_MAX;


#define NORTH      0
#define EAST       1
#define SOUTH      2
#define WEST       3


#define MAYBE_ABSENT    0   // not checked this wall
#define MAYBE_PRESENT   1   // not checked this wall
#define REALLY_ABSENT   2   // checked it and it is not there
#define REALLY_PRESENT  3   // checked it and it is there
#define WALL_BITS_MASK  3   // masks out wall status bits
#define WALL_KNOWN      2   // mask for known cells

#define WALLNORTH 0x01
#define WALLEAST  0x04
#define WALLSOUTH 0x10
#define WALLWEST  0x40

#define CHECKED_NORTH 0x02
#define CHECKED_EAST  0x08
#define CHECKED_SOUTH 0x20
#define CHECKED_WEST  0x80

#define WALLNORTHMASK (WALL_BITS_MASK << (2*NORTH))
#define WALLEASTMASK  (WALL_BITS_MASK << (2*EAST))
#define WALLSOUTHMASK (WALL_BITS_MASK << (2*SOUTH))
#define WALLWESTMASK  (WALL_BITS_MASK << (2*WEST))

#define VISITED (CHECKED_NORTH + CHECKED_EAST + CHECKED_SOUTH + CHECKED_WEST)

#endif //MAZE_MAZECONSTANTS_H
