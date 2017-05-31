//
// Created by Peter Harrison on 31/05/2017.
//

#include "gtest/gtest.h"
#include "Queue.h"



TEST(TestQueue, CreateAndSize) {
  Queue<int> q(12);
  ASSERT_EQ(0, q.size());
  ASSERT_DEATH(q.fetch(),"");
  for(int i = 0; i < 12; i++){
    q.add(i);
  }
  ASSERT_EQ(12, q.size());
  ASSERT_DEATH(q.add(99),"");
}


TEST(TestQueue, Clear) {
  Queue<int> q(12);
  ASSERT_EQ(0, q.size());
  for(int i = 0; i < 12; i++){
    q.add(i);
  }
  q.clear();
  ASSERT_EQ(0, q.size());
  ASSERT_DEATH(q.fetch(),"");
}


TEST(TestQueue, AddAndFetch) {
  Queue<int> q(12);
  for(int i = 0; i < 5; i++){
    q.add(i);
  }
  ASSERT_EQ(0,q.fetch());
  ASSERT_EQ(1,q.fetch());
  ASSERT_EQ(2,q.fetch());
  ASSERT_EQ(3,q.fetch());
  ASSERT_EQ(4,q.fetch());
  ASSERT_DEATH(q.fetch(),"");
}