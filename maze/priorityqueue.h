#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <assert.h>
#include <stdint.h>

#include "FloodInfo.h"


class PriorityQueue
{
public:
  static const int maxSize = 256;
  PriorityQueue();

  void clear();
  int size();
  bool empty();


  void add(int cell, int cost, char lastTurn, uint8_t runLength);
  void add(FloodInfo infoBlock);

  FloodInfo smallest();
  FloodInfo largest();

private:
  FloodInfo info[maxSize];
  int mHead;
  int mTail;

  bool full();
};

#endif // PRIORITYQUEUE_H
