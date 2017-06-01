#include "gtest/gtest.h"
#include "priorityqueue.h"

class QueueTest : public ::testing::Test {
protected:
  PriorityQueue *queue;

  FloodInfo itemA;
  FloodInfo itemB;
  FloodInfo itemC;
  FloodInfo itemD;
  FloodInfo itemE;
  FloodInfo itemF;


  virtual void SetUp() {
    queue = new PriorityQueue();
    itemA = FloodInfo(13,2,1,'A');
    itemB = FloodInfo(12,2,1,'B');
    itemC = FloodInfo(1,2,1,'C');
    itemD = FloodInfo(0,2,1,'D');
    itemE = FloodInfo(6,2,1,'D');
    itemF = FloodInfo(6,2,1,'D');
  }

  virtual void TearDown() {
    delete queue;
  }

};

TEST_F(QueueTest, Constructor_ProperInitialisation){
  FloodInfo item;
  EXPECT_EQ(0,queue->size());
  EXPECT_TRUE(queue->empty());
  item = queue->smallest();
  EXPECT_TRUE(item.isNull());
  item = queue->smallest();
  EXPECT_TRUE(item.isNull());
}

TEST_F(QueueTest, PushAndRetrieve_Single_Item){
  FloodInfo info = {3,2,1,'F'};
  EXPECT_FALSE(info.isNull());
  FloodInfo item;
  queue->add(info);
  EXPECT_EQ(1,queue->size());
  EXPECT_FALSE(queue->empty());
  item = queue->smallest();
  EXPECT_TRUE(item == info);
  EXPECT_TRUE(queue->empty());
}


TEST_F(QueueTest, DuplicateItems_FetchGetsMostRecent){
  FloodInfo item;
  queue->add(itemA);
  queue->add(itemF);
  queue->add(itemE);
  item = queue->smallest();
  EXPECT_TRUE((item == itemF) || (item == itemE));
}

