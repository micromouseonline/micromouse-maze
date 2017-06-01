#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <assert.h>
#include <stdint.h>

#include "FloodInfo.h"


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
