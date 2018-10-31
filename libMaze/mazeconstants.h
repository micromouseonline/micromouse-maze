/************************************************************************
*
* Copyright (C) 2017 by Peter Harrison. www.micromouseonline.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without l> imitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
************************************************************************/


#ifndef MAZE_MAZECONSTANTS_H
#define MAZE_MAZECONSTANTS_H

#include <cstdint>


const uint16_t MAX_COST = UINT16_MAX;

#define NORTH         (uint8_t)0x00
#define EAST          (uint8_t)0x01
#define SOUTH         (uint8_t)0x02
#define WEST          (uint8_t)0x03
#define INVALID_DIRECTION (uint8_t)0x04

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

#define WALL_PRESENT  0x01
#define WALL_UNSEEN   0x10
#define ALL_UNSEEN    0xF0

#define WALL_NORTH (WALL_PRESENT << (NORTH))
#define WALL_EAST  (WALL_PRESENT << (EAST))
#define WALL_SOUTH (WALL_PRESENT << (SOUTH))
#define WALL_WEST  (WALL_PRESENT << (WEST))

#define UNSEEN_NORTH (WALL_UNSEEN << (NORTH))
#define UNSEEN_EAST  (WALL_UNSEEN << (EAST))
#define UNSEEN_SOUTH (WALL_UNSEEN << (SOUTH))
#define UNSEEN_WEST  (WALL_UNSEEN << (WEST))

#define CLOSED_MASK  0x11
#define OPEN_MASK    0x01

#endif //MAZE_MAZECONSTANTS_H
