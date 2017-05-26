#include "priorityqueue.h"

PriorityQueue::PriorityQueue() : mHead(0)
{
  clear();
};

void PriorityQueue::clear()
{
  mHead = 0;
}

int PriorityQueue::size()
{
  return mHead;
}

bool PriorityQueue::empty()
{
  return size() == 0;
}

bool PriorityQueue::full()
{
  return mHead == maxSize;
}


void PriorityQueue::push(int cell, int cost, char lastTurn, uint8_t runLength)
{
  assert (mHead < maxSize);
  if (full()){
    return; // this is an error
  }
  info[mHead].cost = cost;
  info[mHead].cell = cell;
  info[mHead].lastTurn = lastTurn;
  info[mHead].runLength = runLength;
  mHead++;
}

void PriorityQueue::push(FloodInfo infoBlock)
{
   assert (mHead < maxSize);
  if (full()){
    return; // this is an error
  }
  info[mHead] = infoBlock;
  mHead++;
}

FloodInfo PriorityQueue::last()
{
  if (empty()){
    FloodInfo nullInfo = {0};
    return nullInfo;
  }
  FloodInfo result = info[--mHead];
  return result;
}

FloodInfo PriorityQueue::smallest()
{
  if (empty()){
    FloodInfo nullInfo = {0};
    return nullInfo;
  }
  int index = 0;
  for (int i = 0; i < mHead; i++) {
    if (info[i] <= info[index]) {
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
  if (empty()){
    FloodInfo nullInfo = {0};
    return nullInfo;
  }
  int index = 0;
  for (int i = 0; i < mHead; i++) {
    if (info[i] >= info[index]) {
      index = i;
    }
  }
  FloodInfo smallestValue = info[index];
  mHead--;
  info[index] = info[mHead];
  return smallestValue;
}

