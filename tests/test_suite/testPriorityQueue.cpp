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
  FloodInfo info = {3,2,1,'F'};
  EXPECT_FALSE(info.isNull());
  FloodInfo item;
  queue->add(info);
  EXPECT_EQ(1,queue->size());
  EXPECT_FALSE(queue->empty());
  item = queue->last();
  EXPECT_TRUE(item == info);
  EXPECT_TRUE(queue->empty());
}


TEST_F(QueueTest, DuplicateItems_FetchGetsMostRecent){
  FloodInfo itemOne;
  FloodInfo itemTwo;
  queue->add(itemE);
  queue->add(itemF);
  queue->add(itemD);
  itemOne = queue->largest();
  EXPECT_TRUE(itemOne == itemF);
}

TEST_F(QueueTest, PushAndRetrieve_UsedAsQueue){

  FloodInfo item;
  queue->add(itemA);
  queue->add(itemB);
  queue->add(itemC);
  queue->add(itemD);
  EXPECT_EQ(4,queue->size());
  EXPECT_FALSE(queue->empty());
  item = queue->last();
  EXPECT_TRUE(item == itemD);
  item = queue->last();
  EXPECT_TRUE(item == itemC);
}

TEST_F(QueueTest, PushAndRetrieve_LargetAndSmallest_Item){
  FloodInfo item;
  queue->add(itemA);
  queue->add(itemB);
  queue->add(itemC);
  queue->add(FloodInfo(6,1,1,'X'));
  EXPECT_EQ(4,queue->size());
  EXPECT_FALSE(queue->empty());
  item = queue->smallest();
  EXPECT_TRUE(item == itemC);
  item = queue->largest();
  EXPECT_TRUE(item == itemA);
  EXPECT_EQ(2,queue->size());
  item = queue->largest();
  EXPECT_TRUE(item == itemB);
  EXPECT_EQ(1,queue->size());
}