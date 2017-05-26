//
// Created by Peter Harrison on 26/05/2017.
//

#ifndef MAZE_MAZECONSTANTS_H
#define MAZE_MAZECONSTANTS_H

#include <stdint.h>


#define NOINIT

const uint16_t MAZEWIDTH = 16;
const uint16_t MAZE_ROWS = 16;
const uint16_t MAZE_COLS = 16;
const uint16_t NUMCELLS = (MAZE_ROWS * MAZE_COLS);


const uint8_t DIRECTION_COUNT = 4;



const uint8_t DEFAULT_GOAL = 0x77;
const uint16_t MAX_COST = UINT16_MAX;


#define ORIGIN 0x00
#define UNREACHABLE INT16_MAX

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



#define NORTH      0
#define EAST       1
#define SOUTH      2
#define WEST       3

#define XORD(LOC) (LOC / MAZEWIDTH)
#define YORD(LOC) (LOC % MAZEWIDTH)


typedef struct {
  int8_t row;
  int8_t col;
} location_t;


/* one day diagonals may make this 8 */
typedef uint8_t walls_t;

typedef uint8_t direction_t;

typedef uint16_t cost_t;


#define WALLNORTH 0x01
#define WALLEAST  0x04
#define WALLSOUTH 0x10
#define WALLWEST  0x40



#define INVALID 4
/* TODO: hide all these macros by creating functions in maze.c */
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

#endif //MAZE_MAZECONSTANTS_H
