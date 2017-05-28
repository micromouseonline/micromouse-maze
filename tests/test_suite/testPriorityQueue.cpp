#include "gtest/gtest.h"
#include "priorityqueue.h"

class QueueTest : public ::testing::Test {
protected:
  PriorityQueue *queue;
  FloodInfo * floodInfo;
  FloodInfo nullInfo = {0};

  virtual void SetUp() {
    queue = new PriorityQueue();
  }

  virtual void TearDown() {
    delete queue;
  }

};

TEST_F(QueueTest, Constructor_ProperInitialiation){
  FloodInfo item;

  EXPECT_EQ(0,queue->size());
  EXPECT_TRUE(queue->empty());
  item = queue->last();
  EXPECT_TRUE(item.isNull());
  item = queue->largest();
  EXPECT_TRUE(item.isNull());
  item = queue->smallest();
  EXPECT_TRUE(item.isNull());
}

TEST_F(QueueTest, PushAndRetrieve_Single_Item){
  FloodInfo info = {'F', 1,2,3};
  EXPECT_FALSE(info.isNull());
  FloodInfo item;
  queue->push(info);
  EXPECT_EQ(1,queue->size());
  EXPECT_FALSE(queue->empty());
  item = queue->last();
  EXPECT_TRUE(item == info);
  EXPECT_TRUE(queue->empty());
}

TEST_F(QueueTest, PushAndRetrieve_LargetAndSmallest_Item){
  FloodInfo infoA = {'F', 1,1,3};
  FloodInfo infoB = {'F', 1,1,2};
  FloodInfo infoC = {'F', 1,1,1};
  FloodInfo item;
  queue->push(infoA);
  queue->push(infoB);
  queue->push(infoC);
  EXPECT_EQ(3,queue->size());
  EXPECT_FALSE(queue->empty());
  item = queue->smallest();
  EXPECT_TRUE(item == infoC);
  item = queue->largest();
  EXPECT_TRUE(item == infoA);
  EXPECT_EQ(1,queue->size());
  item = queue->largest();
  EXPECT_TRUE(item == infoB);
  EXPECT_EQ(0,queue->size());
}