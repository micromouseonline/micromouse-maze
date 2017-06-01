#include "gtest/gtest.h"
#include "priorityqueue.h"

class QueueTest : public ::testing::Test {
protected:
  PriorityQueue<FloodInfo> *queue;

  FloodInfo itemA;
  FloodInfo itemB;
  FloodInfo itemC;
  FloodInfo itemD;
  FloodInfo itemE;
  FloodInfo itemF;


  virtual void SetUp() {
    queue = new PriorityQueue<FloodInfo>();
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
  EXPECT_EQ(0,queue->size());
  EXPECT_DEATH(FloodInfo item = queue->fetch(),"");
}

TEST_F(QueueTest, AddFetch_CorrectOrder){
  EXPECT_EQ(0,queue->size());
  queue->add(itemA);
  queue->add(itemB);
  queue->add(itemC);
  queue->add(itemD);
  queue->add(itemE);

  EXPECT_EQ(5,queue->size());
//  FloodInfo item;
//  EXPECT_TRUE(itemD == queue->fetch());
//  EXPECT_TRUE(itemC == queue->fetch());
//  EXPECT_TRUE(itemE == queue->fetch());
//  EXPECT_TRUE(itemB == queue->fetch());
//  EXPECT_TRUE(itemA == queue->fetch());
//  EXPECT_EQ(0,queue->size());

}

TEST_F(QueueTest, PushAndRetrieve_Single_Item){
  FloodInfo info = {3,2,1,'F'};
  EXPECT_FALSE(info.isNull());
  FloodInfo item;
  queue->add(info);
  EXPECT_EQ(1,queue->size());
  item = queue->fetch();
  EXPECT_TRUE(item == info);

}


TEST_F(QueueTest, DuplicateItems_FetchGetsSmallest){
  FloodInfo item;
  queue->add(itemA);
  queue->add(itemB);
  queue->add(itemC);
  item = queue->fetch();
  EXPECT_TRUE(item == itemC) << item.cost << "  " << itemC.cost;
}

