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


/**
 *  \file floodinfo.h
 *  \brief Stores the data needed by the flooding algorithm(s)
 */


#pragma once

#include <stdint.h>

class FloodInfo {
public:
  uint16_t cost;
  uint16_t cell;
  uint8_t runLength;
  uint8_t entryDir;
  uint8_t entryWall;

  FloodInfo() :
    cost(0),
    cell(0),
    runLength(),
    entryDir(0),
    entryWall(0) {
    //
  }

  FloodInfo(uint16_t _cell) :
    cost(0),
    cell(_cell),
    runLength(),
    entryDir(0) {
    //
  }

  FloodInfo(uint16_t _cost, uint16_t _cell, uint8_t _length) :
    cost(_cost),
    cell(_cell),
    runLength(_length) {
    //
  }

  FloodInfo(uint16_t _cost, uint16_t _cell, uint8_t _length, uint8_t inDir) :
    cost(_cost),
    cell(_cell),
    runLength(_length),
    entryDir(inDir) {
    //
  }

  FloodInfo(uint16_t _cost, uint16_t _cell, uint8_t _length, uint8_t inDir, uint8_t inWall) :
    cost(_cost),
    cell(_cell),
    runLength(_length),
    entryDir(inDir),
    entryWall(inWall) {
    //
  }

  inline bool operator==(FloodInfo a) {
    if (a.runLength == runLength
        && a.cell == cell
        && a.cost == cost
        && a.entryDir == entryDir) {
      return true;
    } else {
      return false;
    }
  }

  inline bool operator!=(FloodInfo &rhs) {
    return !(*this == rhs);
  }

  inline bool operator>(FloodInfo a) {
    return cost > a.cost;
  }

  inline bool operator<(FloodInfo a) {
    return cost < a.cost;
  }

  inline bool operator>=(FloodInfo a) {
    return cost >= a.cost;
  }

  inline bool operator<=(FloodInfo a) {
    return cost <= a.cost;
  }

  inline bool isNull() {
    return (runLength == 0 && cell == 0 && cost == 0);
  }
};
