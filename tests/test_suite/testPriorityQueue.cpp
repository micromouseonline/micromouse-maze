#include "gtest/gtest.h"
#include "priorityqueue.h"

class QueueTest : public ::testing::Test {
protected:
  PriorityQueue<floodinfo> *queue;

  floodinfo itemA;
  floodinfo itemB;
  floodinfo itemC;
  floodinfo itemD;
  floodinfo itemE;
  floodinfo itemF;


  virtual void SetUp() {
    queue = new PriorityQueue<floodinfo>();
    itemA = floodinfo(13,2,1,'A');
    itemB = floodinfo(12,2,1,'B');
    itemC = floodinfo(1,2,1,'C');
    itemD = floodinfo(0,2,1,'D');
    itemE = floodinfo(6,2,1,'D');
    itemF = floodinfo(6,2,1,'D');
  }

  virtual void TearDown() {
    delete queue;
  }

};

TEST_F(QueueTest, Constructor_ProperInitialisation){
  EXPECT_EQ(0,queue->size());
  EXPECT_DEATH(floodinfo item = queue->fetch(),"");
}

TEST_F(QueueTest, AddFetch_CorrectPriorityOrder){
  EXPECT_EQ(0,queue->size());
  queue->add(itemA);
  queue->add(itemB);
  queue->add(itemC);
  queue->add(itemD);
  queue->add(itemE);
  EXPECT_EQ(5,queue->size());

  EXPECT_TRUE(itemD == queue->fetch());
  EXPECT_TRUE(itemC == queue->fetch());
  EXPECT_TRUE(itemE == queue->fetch());
  EXPECT_TRUE(itemB == queue->fetch());
  EXPECT_TRUE(itemA == queue->fetch());
  EXPECT_EQ(0,queue->size());

}
TEST_F(QueueTest, AddFetch_CorrectLifoOrder){
  EXPECT_EQ(0,queue->size());
  queue->add(itemA);
  queue->add(itemB);
  queue->add(itemC);
  queue->add(itemD);
  queue->add(itemE);

  EXPECT_EQ(5,queue->size());
  EXPECT_TRUE(itemA == queue->head());
  EXPECT_TRUE(itemB == queue->head());
  EXPECT_TRUE(itemC == queue->head());
  EXPECT_TRUE(itemD == queue->head());
  EXPECT_TRUE(itemE == queue->head());
  EXPECT_EQ(0,queue->size());

}

TEST_F(QueueTest, PushAndRetrieve_Single_Item){
  floodinfo info = {3,2,1,'F'};
  EXPECT_FALSE(info.isNull());
  floodinfo item;
  queue->add(info);
  EXPECT_EQ(1,queue->size());
  item = queue->fetch();
  EXPECT_TRUE(item == info);

}


TEST_F(QueueTest, DuplicateItems_FetchGetsSmallest){
  floodinfo item;
  queue->add(itemA);
  queue->add(itemB);
  queue->add(itemC);
  item = queue->fetch();
  EXPECT_TRUE(item == itemC) << item.cost << "  " << itemC.cost;
}

