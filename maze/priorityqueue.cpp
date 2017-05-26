#include "priorityqueue.h"

PriorityQueue::PriorityQueue() : mHead(0)
{
  clear();
};

void PriorityQueue::clear()
{
  mHead = 0;
  FloodInfo emptyInfo = {0};
  for (int i = 0; i < max; i++) {
    info[i] = emptyInfo;
  }
}

int PriorityQueue::size()
{
  return mHead;
}

bool PriorityQueue::empty()
{
  return size() == 0;
}

bool PriorityQueue::hasItems()
{
  return size() > 0;
}

FloodInfo PriorityQueue::item(int i)
{
  return info[i];
}

void PriorityQueue::push(int cell, int cost, char lastTurn, uint8_t runLength)
{
//    assert (mHead < max);
  info[mHead].cost = cost;
  info[mHead].cell = cell;
  info[mHead].lastTurn = lastTurn;
  info[mHead].runLength = runLength;
  mHead++;
}

void PriorityQueue::push(FloodInfo infoBlock)
{
//    assert (mHead < max);
  info[mHead] = infoBlock;
  mHead++;
}

FloodInfo PriorityQueue::last()
{
  FloodInfo result = info[--mHead];
  return result;
}

FloodInfo PriorityQueue::smallest()
{
  int index = 0;
  for (int i = 0; i < mHead; i++) {
    if (info[i].cost <= info[index].cost) {
      index = i;
    }
  }
  FloodInfo smallestValue = info[index];
  mHead--;
  info[index] = info[mHead];
  return smallestValue;
}

FloodInfo PriorityQueue::largest()
{
  int index = 0;
  for (int i = 0; i < mHead; i++) {
    if (info[i].cost >= info[index].cost) {
      index = i;
    }
  }
  FloodInfo smallestValue = info[index];
  mHead--;
  info[index] = info[mHead];
  return smallestValue;
}

