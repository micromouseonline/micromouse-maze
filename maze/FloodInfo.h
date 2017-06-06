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

  FloodInfo(uint16_t _cost, uint16_t _cell, uint8_t _length,  uint8_t inDir, uint8_t inWall) :
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
