#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <assert.h>
#include <stdint.h>

struct FloodInfo {
  char lastTurn ;
  uint8_t runLength;
  uint16_t cell;
  uint16_t cost;

  inline bool operator==(FloodInfo a) {
    if (a.lastTurn==lastTurn
        && a.runLength== runLength
        && a.cell == cell
        && a.cost == cost)
      return true;
    else
      return false;
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

  inline bool isNull(){
    return (lastTurn == 0 && runLength == 0 && cell == 0 && cost == 0);
  }
};


class PriorityQueue
{
public:
  static const int maxSize = 100;
  PriorityQueue();

  void clear();
  int size();
  bool empty();


  void push (int cell, int cost, char lastTurn , uint8_t runLength );
  void push (FloodInfo infoBlock);
  FloodInfo last();
  FloodInfo smallest();
  FloodInfo largest();

private:
  FloodInfo info[maxSize];
  int mHead;

  bool full();
};

#endif // PRIORITYQUEUE_H
