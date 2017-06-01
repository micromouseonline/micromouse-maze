//
// Created by Peter Harrison on 31/05/2017.
//

#ifndef MAZE_QUEUE_H
#define MAZE_QUEUE_H

#include <assert.h>

template<class item_t>
class Queue {
public:

  explicit Queue(int maxSize = 128);

  Queue(const Queue<item_t> &rhs);

  ~Queue(void);

  int size();

  void clear();

  void add(item_t item);

  item_t fetch();

protected:
  item_t *mData;
  const int MAX_ITEMS;
  int mHead;
  int mTail;
  int mItemCount;
};

template<class item_t>
Queue<item_t>::Queue(int maxSize) :
    MAX_ITEMS(maxSize) {
  mData = new item_t[MAX_ITEMS + 1];
  mHead = 0;
  mTail = 0;
  mItemCount = 0;
}


template<class item_t>
Queue<item_t>::Queue(const Queue &rhs) :
    MAX_ITEMS(rhs.MAX_ITEMS),
    mItemCount(rhs.mItemCount) {
  mHead = rhs.mHead;
  mTail = rhs.mTail;
  mData = new item_t(MAX_ITEMS + 1);
  for (int i = 0; i < MAX_ITEMS; i++) {
    mData[i] = rhs.mData[i];
  }

}

template<class item_t>
Queue<item_t>::~Queue(void) {
  delete[] mData;
}

template<class item_t>
int Queue<item_t>::size() {
  return mItemCount;
}

template<class item_t>
void Queue<item_t>::add(item_t item) {
  assert(mItemCount < MAX_ITEMS);
  mData[mTail] = item;
  ++mTail;
  ++mItemCount;
  if (mTail > MAX_ITEMS) {
    mTail -= MAX_ITEMS;
  }
}


template<class item_t>
void Queue<item_t>::clear() {
  mHead = 0;
  mTail = 0;
  mItemCount = 0;
};


template<class item_t>
item_t Queue<item_t>::fetch() {
  assert(mItemCount > 0);
  item_t result;
  result = mData[mHead];
  ++mHead;
  if (mHead > MAX_ITEMS) {
    mHead -= MAX_ITEMS;
  }
  --mItemCount;
  return result;
}

#endif //MAZE_QUEUE_H
