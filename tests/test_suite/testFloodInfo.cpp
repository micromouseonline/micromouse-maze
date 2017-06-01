//
// Created by Peter Harrison on 01/06/2017.
//

#include <gtest/gtest.h>
#include "FloodInfo.h"

TEST(FloodInfoTest, Instantiation) {
  FloodInfo infoA(3,2,1,'A');
  EXPECT_FALSE(infoA.isNull());
  EXPECT_EQ('A', infoA.lastTurn);
  EXPECT_EQ(1, infoA.runLength);
  EXPECT_EQ(2, infoA.cell);
  EXPECT_EQ(3, infoA.cost);
  FloodInfo infoX;
  EXPECT_TRUE(infoX.isNull());
  FloodInfo info = {13,12,11,'Q'};
  EXPECT_EQ(13,info.cost);
  EXPECT_EQ(12,info.cell);
  EXPECT_EQ(11,info.runLength);
  EXPECT_EQ('Q',info.lastTurn);

}

TEST(FloodInfoTest, Operators){
  FloodInfo infoA(3,2,1,'A');
  FloodInfo infoB(10,2,1,'A');
  FloodInfo infoC;
  ASSERT_TRUE(infoB > infoA);
  ASSERT_TRUE(infoB >= infoA);
  ASSERT_TRUE(infoA < infoB);
  ASSERT_TRUE(infoA <= infoB);
  ASSERT_TRUE(infoA != infoB);
  ASSERT_TRUE(infoA != infoC);
  infoC = infoA;
  ASSERT_TRUE(infoA == infoC);
  ASSERT_TRUE(infoC == infoA);
}
