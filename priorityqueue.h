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

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <assert.h>
#include <stdint.h>

//#include "floodinfo.h"

template<class item_t>
class PriorityQueue {
public:

  explicit PriorityQueue(int maxSize = 128) :
    MAX_ITEMS(maxSize) {
    mData = new item_t[MAX_ITEMS + 1];
    mHead = 0;
    mTail = 0;
    mItemCount = 0;
  }

  PriorityQueue(const PriorityQueue<item_t> &rhs) :
    MAX_ITEMS(rhs.MAX_ITEMS),
    mItemCount(rhs.mItemCount) {
    mHead = rhs.mHead;
    mTail = rhs.mTail;
    mData = new item_t(MAX_ITEMS + 1);
    for (int i = 0; i < MAX_ITEMS; i++) {
      mData[i] = rhs.mData[i];
    }

  };

  ~PriorityQueue(void) {
    delete[] mData;
  };

  int size() {
    return mItemCount;
  }

  void clear() {
    mHead = 0;
    mTail = 0;
    mItemCount = 0;
  }

  /*
   * Adds an item to the tail of the queue
   */
  void add(item_t item) {
    assert(mItemCount < MAX_ITEMS);
    mData[mTail] = item;
    ++mTail;
    ++mItemCount;
    if (mTail > MAX_ITEMS) {
      mTail -= MAX_ITEMS;
    }
  }

  /*
   * fetch the item at the head of the queue. Using only this method
   * allows use of the queue as a simple LIFO structure
   */
  item_t head() {
    item_t result = mData[mHead];
    ++mHead;
    if (mHead > MAX_ITEMS) {
      mHead -= MAX_ITEMS;
    }
    --mItemCount;
    return result;
  }

  /*
   * Search from the head of the queue towards the tail
   * return the smallest item in the queue
   * If two items are equally small, return the one that
   * was in the queue the longest. That is, the first one found.
   * Operation is performed by swapping the smallest item into the head
   * position. Thus, the natural order of the queue is corrupted
   */
  item_t fetchSmallest() {
    assert(mItemCount > 0);
    int posSmallest = mHead;
    int index = mHead;
    while (index != mTail) {
      if (mData[index] < mData[posSmallest]) {
        posSmallest = index;
      }
      ++index;
      if (index > MAX_ITEMS) {
        index -= MAX_ITEMS;
      }
    }
    item_t smallest = mData[posSmallest];
    mData[posSmallest] = mData[mHead];
    mData[mHead] = smallest;
    return head();
  }

protected:
  item_t *mData;
  const int MAX_ITEMS;
  int mHead;
  int mTail;
  int mItemCount;
};

#endif // PRIORITYQUEUE_H
