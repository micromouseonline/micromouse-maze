#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <assert.h>
#include <stdint.h>

struct FloodInfo {
  char lastTurn;
  uint8_t runLength;
  uint16_t cell;
  uint16_t cost;
};
class PriorityQueue
{
public:
  static const int max = 100;
  PriorityQueue();

  void clear();
  int size();
  bool empty();
  bool hasItems();
  FloodInfo item (int i);
  void push (int cell, int cost, char lastTurn = 'F', uint8_t runLength = 0);
  void push (FloodInfo infoBlock);
  FloodInfo last();
  FloodInfo smallest();
  FloodInfo largest();

private:
  FloodInfo info[max];
  int mHead;

};

#endif // PRIORITYQUEUE_H
