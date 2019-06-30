/***********************************************************************
 * Created by Peter Harrison on 2019-04-01.
 * Copyright (c) 2019 Peter Harrison
 *
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
 **************************************************************************/



#include "gtest/gtest.h"
#include "commandnames.h"


class CommandNameTest : public ::testing::Test {

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};


TEST_F(CommandNameTest, Blank_Test) {
  EXPECT_EQ(1, 1);
}


TEST_F(CommandNameTest, Command_Type_Mask) {
  MoveCommand move;
  int moveType;
  move = FWD16;
  moveType = getMoveType(move);
  EXPECT_EQ(CMD_TYPE_ORTHO, moveType);
  EXPECT_NE(CMD_TYPE_DIAG, moveType);
  EXPECT_NE(CMD_TYPE_SMOOTH, moveType);
  EXPECT_NE(CMD_TYPE_INPLACE, moveType);
  EXPECT_NE(CMD_TYPE_MESSAGE, moveType);

  move = FWD0;
  moveType = getMoveType(move);
  EXPECT_EQ(CMD_TYPE_ORTHO, moveType);
  EXPECT_NE(CMD_TYPE_DIAG, moveType);
  EXPECT_NE(CMD_TYPE_SMOOTH, moveType);
  EXPECT_NE(CMD_TYPE_INPLACE, moveType);
  EXPECT_NE(CMD_TYPE_MESSAGE, moveType);

  move = DIA0;
  moveType = getMoveType(move);
  EXPECT_NE(CMD_TYPE_ORTHO, moveType);
  EXPECT_EQ(CMD_TYPE_DIAG, moveType);
  EXPECT_NE(CMD_TYPE_SMOOTH, moveType);
  EXPECT_NE(CMD_TYPE_INPLACE, moveType);
  EXPECT_NE(CMD_TYPE_MESSAGE, moveType);

  move = DIA31;
  moveType = getMoveType(move);
  EXPECT_NE(CMD_TYPE_ORTHO, moveType);
  EXPECT_EQ(CMD_TYPE_DIAG, moveType);
  EXPECT_NE(CMD_TYPE_SMOOTH, moveType);
  EXPECT_NE(CMD_TYPE_INPLACE, moveType);
  EXPECT_NE(CMD_TYPE_MESSAGE, moveType);

  move = IP45R;
  moveType = getMoveType(move);
  EXPECT_NE(CMD_TYPE_ORTHO, moveType);
  EXPECT_NE(CMD_TYPE_DIAG, moveType);
  EXPECT_NE(CMD_TYPE_SMOOTH, moveType);
  EXPECT_EQ(CMD_TYPE_INPLACE, moveType);
  EXPECT_NE(CMD_TYPE_MESSAGE, moveType);


  move = CMD_ERROR;
  moveType = getMoveType(move);
  EXPECT_NE(CMD_TYPE_ORTHO, moveType);
  EXPECT_NE(CMD_TYPE_DIAG, moveType);
  EXPECT_NE(CMD_TYPE_SMOOTH, moveType);
  EXPECT_NE(CMD_TYPE_INPLACE, moveType);
  EXPECT_EQ(CMD_TYPE_MESSAGE, moveType);

  EXPECT_TRUE(isTurn(SS90FR));
  EXPECT_TRUE(isTurn(IP135R));
  EXPECT_FALSE(isTurn(DIA30));
  EXPECT_FALSE(isTurn(CMD_STOP));

}


TEST_F(CommandNameTest, Move_Length) {
  EXPECT_EQ(0, getMoveLength(FWD0));
  EXPECT_EQ(31, getMoveLength(FWD31));

  EXPECT_EQ(0, getMoveLength(DIA0));
  EXPECT_EQ(31, getMoveLength(DIA31));

}



TEST_F(CommandNameTest, Turn_Index) {
  EXPECT_EQ(0, getTurnIndex(SS90FR));
  EXPECT_EQ(1, getTurnIndex(SS90FL));
  EXPECT_EQ(14, getTurnIndex(SS90ER));
  EXPECT_EQ(15, getTurnIndex(SS90EL));

  EXPECT_EQ(0, getTurnIndex(IP45R));
  EXPECT_EQ(1, getTurnIndex(IP45L));

  EXPECT_EQ(6, getTurnIndex(IP180R));
  EXPECT_EQ(7, getTurnIndex(IP180L));
}

TEST_F(CommandNameTest, Turn_Type) {
  EXPECT_TRUE(isSmoothTurn(DD90R));
  EXPECT_TRUE(isSmoothTurn(DS45L));
  EXPECT_FALSE(isSmoothTurn(IP45L));
  EXPECT_FALSE(isSmoothTurn(FWD9));

  EXPECT_FALSE(isInPlaceTurn(DD90R));
  EXPECT_TRUE(isInPlaceTurn(IP90L));
  EXPECT_FALSE(isInPlaceTurn(DIA4));
}


TEST_F(CommandNameTest, Turn_Direction) {
  EXPECT_EQ(1, getTurnDirection(DD90L));
  EXPECT_EQ(0, getTurnDirection(DD90R));
  EXPECT_EQ(1, getTurnDirection(IP90L));
  EXPECT_EQ(0, getTurnDirection(IP90R));
}


TEST_F(CommandNameTest, Move_Never_Unknown) {
  for (int i = 0; i < 256; i++) {
    EXPECT_NE(CMD_TYPE_UNKNOWN, getMoveType(MoveCommand(i)));
  }
}

