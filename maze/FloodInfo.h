//
// Created by Peter Harrison on 01/06/2017.
//

#ifndef MAZE_FLOODINFO_H
#define MAZE_FLOODINFO_H

#include <stdint.h>

class FloodInfo {
public:
  uint16_t cost;
  uint16_t cell;
  uint8_t runLength;
  char lastTurn;

  FloodInfo() :
      lastTurn('\0'),
      runLength(),
      cell(0),
      cost(0) {
    //
  }

  FloodInfo(
      uint16_t _cost,
      uint16_t _cell ,
      uint8_t _length,
      char _turn
  ) :
      lastTurn(_turn),
      runLength(_length),
      cell(_cell),
      cost(_cost) {
    //
  }

  inline bool operator==(FloodInfo a) {
    if (a.lastTurn == lastTurn
        && a.runLength == runLength
        && a.cell == cell
        && a.cost == cost)
      return true;
    else
      return false;
  }

  inline bool operator !=(FloodInfo & rhs){
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
    return (lastTurn == 0 && runLength == 0 && cell == 0 && cost == 0);
  }
};


#endif //MAZE_FLOODINFO_H
