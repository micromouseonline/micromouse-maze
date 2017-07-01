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

#include <gtest/gtest.h>
#include "floodinfo.h"

TEST(FloodInfoTest, Instantiation) {
  FloodInfo info;
  EXPECT_EQ(0,info.cost);
  EXPECT_EQ(0,info.cell);
  EXPECT_EQ(0,info.entryDir);
  EXPECT_EQ(0,info.entryWall);
  EXPECT_EQ(0,info.runLength);
  EXPECT_TRUE(info.isNull());
}

TEST(FloodInfoTest, Operators){
  FloodInfo infoA;
  FloodInfo infoB;
  EXPECT_TRUE(infoA == infoB);
  EXPECT_FALSE(infoA != infoB);
  EXPECT_FALSE(infoA > infoB);
  EXPECT_FALSE(infoA < infoB);
  EXPECT_TRUE(infoA >= infoB);
  EXPECT_TRUE(infoA <= infoB);
  infoA.cost = 99;
  infoB.cost = 11;
  EXPECT_FALSE(infoA == infoB);
  EXPECT_TRUE(infoA != infoB);
  EXPECT_TRUE(infoA > infoB);
  EXPECT_FALSE(infoA < infoB);
  EXPECT_TRUE(infoA >= infoB);
  EXPECT_FALSE(infoA <= infoB);
}
