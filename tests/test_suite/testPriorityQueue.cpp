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


#include "gtest/gtest.h"
#include "floodinfo.h"
#include "priorityqueue.h"

class QueueTest : public ::testing::Test {
protected:
  PriorityQueue<FloodInfo> *queue;

  FloodInfo itemA;
  FloodInfo itemB;
  FloodInfo itemC;
  FloodInfo itemD;
  FloodInfo itemE;

  virtual void SetUp() {
    queue = new PriorityQueue<FloodInfo>();
    itemA = FloodInfo(13, 2, 1, DIR_N);
    itemB = FloodInfo(12, 2, 1, DIR_NE);
    itemC = FloodInfo(1, 2, 1, DIR_E);
    itemD = FloodInfo(0, 2, 1, DIR_SE);
    itemE = FloodInfo(6, 2, 1, DIR_S);
  }

  virtual void TearDown() {
    delete queue;
  }

};

TEST_F(QueueTest, Constructor_ProperInitialisation) {
  EXPECT_EQ(0, queue->size());
  EXPECT_TRUE(queue->empty());
}

TEST_F(QueueTest, Clear_emptiesQueue) {
  PriorityQueue<int> intQueue;
  intQueue.push(9);
  intQueue.push(99);
  intQueue.push(9999);
  EXPECT_EQ(3, intQueue.size());
  intQueue.clear();
  EXPECT_TRUE(queue->empty());
}

TEST_F(QueueTest, AddFetch_CorrectPriorityOrder) {
  queue->push(itemA);
  queue->push(itemB);
  queue->push(itemC);
  queue->push(itemD);
  queue->push(itemE);
  EXPECT_EQ(5, queue->size());

  EXPECT_TRUE(itemD == queue->fetchSmallest());
  EXPECT_TRUE(itemC == queue->fetchSmallest());
  EXPECT_TRUE(itemE == queue->fetchSmallest());
  EXPECT_TRUE(itemB == queue->fetchSmallest());
  EXPECT_TRUE(itemA == queue->fetchSmallest());
  EXPECT_TRUE(queue->empty());

}

TEST_F(QueueTest, AddFetch_CorrectLifoOrder) {
  queue->push(itemA);
  queue->push(itemB);
  queue->push(itemC);
  queue->push(itemD);
  queue->push(itemE);

  EXPECT_EQ(5, queue->size());
  EXPECT_TRUE(itemA == queue->front());
  queue->pop();
  EXPECT_TRUE(itemB == queue->front());
  queue->pop();
  EXPECT_TRUE(itemC == queue->front());
  queue->pop();
  EXPECT_TRUE(itemD == queue->front());
  queue->pop();
  EXPECT_TRUE(itemE == queue->front());
  queue->pop();
  EXPECT_TRUE(queue->empty());

}

TEST_F(QueueTest, PushAndRetrieve_Single_Item) {
  FloodInfo info = {3, 2, 1, DIR_S};
  EXPECT_FALSE(info.isNull());
  FloodInfo item;
  queue->push(info);
  EXPECT_EQ(1, queue->size());
  item = queue->fetchSmallest();
  EXPECT_TRUE(item == info);

}

TEST_F(QueueTest, DuplicateItems_FetchGetsSmallest) {
  FloodInfo item;
  queue->push(itemA);
  queue->push(itemB);
  queue->push(itemC);
  item = queue->fetchSmallest();
  EXPECT_TRUE(item == itemC) << item.cost << "  " << itemC.cost;
}

