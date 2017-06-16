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
    itemA = FloodInfo(13, 2, 1, 'A');
    itemB = FloodInfo(12, 2, 1, 'B');
    itemC = FloodInfo(1, 2, 1, 'C');
    itemD = FloodInfo(0, 2, 1, 'D');
    itemE = FloodInfo(6, 2, 1, 'D');
    itemF = FloodInfo(6, 2, 1, 'D');
  }

  virtual void TearDown() {
    delete queue;
  }

};

TEST_F(QueueTest, Constructor_ProperInitialisation) {
  EXPECT_EQ(0, queue->size());
  EXPECT_DEATH(FloodInfo item = queue->fetchSmallest(), "");
}

TEST_F(QueueTest, Clear_emptiesQueue) {
  PriorityQueue<int> intQueue;
  EXPECT_EQ(0, intQueue.size());
  intQueue.add(9);
  intQueue.add(99);
  intQueue.add(9999);
  EXPECT_EQ(3, intQueue.size());
  intQueue.clear();
  EXPECT_EQ(0, intQueue.size());
}

TEST_F(QueueTest, AddFetch_CorrectPriorityOrder) {
  EXPECT_EQ(0, queue->size());
  queue->add(itemA);
  queue->add(itemB);
  queue->add(itemC);
  queue->add(itemD);
  queue->add(itemE);
  EXPECT_EQ(5, queue->size());

  EXPECT_TRUE(itemD == queue->fetchSmallest());
  EXPECT_TRUE(itemC == queue->fetchSmallest());
  EXPECT_TRUE(itemE == queue->fetchSmallest());
  EXPECT_TRUE(itemB == queue->fetchSmallest());
  EXPECT_TRUE(itemA == queue->fetchSmallest());
  EXPECT_EQ(0, queue->size());

}

TEST_F(QueueTest, AddFetch_CorrectLifoOrder) {
  EXPECT_EQ(0, queue->size());
  queue->add(itemA);
  queue->add(itemB);
  queue->add(itemC);
  queue->add(itemD);
  queue->add(itemE);

  EXPECT_EQ(5, queue->size());
  EXPECT_TRUE(itemA == queue->head());
  EXPECT_TRUE(itemB == queue->head());
  EXPECT_TRUE(itemC == queue->head());
  EXPECT_TRUE(itemD == queue->head());
  EXPECT_TRUE(itemE == queue->head());
  EXPECT_EQ(0, queue->size());

}

TEST_F(QueueTest, PushAndRetrieve_Single_Item) {
  FloodInfo info = {3, 2, 1, 'F'};
  EXPECT_FALSE(info.isNull());
  FloodInfo item;
  queue->add(info);
  EXPECT_EQ(1, queue->size());
  item = queue->fetchSmallest();
  EXPECT_TRUE(item == info);

}

TEST_F(QueueTest, DuplicateItems_FetchGetsSmallest) {
  FloodInfo item;
  queue->add(itemA);
  queue->add(itemB);
  queue->add(itemC);
  item = queue->fetchSmallest();
  EXPECT_TRUE(item == itemC) << item.cost << "  " << itemC.cost;
}

