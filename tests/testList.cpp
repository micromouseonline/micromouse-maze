#include "gtest/gtest.h"
#include "list.h"


TEST (List, Initialisation_listIsEmpty)
{
  EXPECT_TRUE (ListEmpty());
}


TEST (List, AddToTail_ListNotEmpty)
{
  location_t loc = {8, 9};
  ListAdd (loc);
  EXPECT_FALSE (ListEmpty());
}

TEST (List, ListClear_ListEmpty)
{
  location_t loc = {8, 9};
  ListAdd (loc);
  ListAdd (loc);
  ListClear();
  EXPECT_TRUE (ListEmpty());
}

TEST (List, Additions_addItems_getCorrectCount)
{
  location_t loc = {8, 9};
  ListClear();
  ListAdd (loc);
  ListAdd (loc);
  ListAdd (loc);
  ListAdd (loc);
  ListStackPop();
  ListStackPop();
  ListStackPop();
  EXPECT_EQ (4, ListAdditions());
}

TEST (List, AddToTail_RemoveFromTail_ListEmpty_ReturnSameValue)
{
  location_t locA = {8, 9};
  location_t locB = {0, 0};
  ListClear();
  ListAdd (locA);
  locB = ListStackPop();
  EXPECT_TRUE (ListEmpty());
  EXPECT_EQ (locA.row, locB.row);
  EXPECT_EQ (locA.col, locB.col);
}


TEST (List, AddToTail_RemoveFromHead_ListEmpty_ReturnSameValue)
{
  location_t locA = {8, 9};
  location_t locB = {0, 0};
  ListClear();
  ListAdd (locA);
  locB = ListQueueHead();
  EXPECT_TRUE (ListEmpty());
  EXPECT_EQ (locA.row, locB.row);
  EXPECT_EQ (locA.col, locB.col);
}


TEST (List, ListSize_ListMaxSize_AddItems_GetCount)
{
  location_t locA = {0, 0};
  ListClear();
  EXPECT_EQ (0, ListSize());
  EXPECT_EQ (0, ListMaxSize());
  for (int i = 0; i < 10; i++) {
    ListAdd (locA);
  }
  EXPECT_EQ (10, ListSize());
  locA = ListStackPop();
  EXPECT_EQ (9, ListSize());
  EXPECT_EQ (10, ListMaxSize());
}

TEST (List, AddItem_WrapsAroundArray_SizeCorrect)
{
  location_t loc;
  ListClear();
  for (int i = 0; i < 200; i++) {
    ListAdd (loc);
  }
  for (int i = 0; i < 100; i++) {
    loc = ListQueueHead();
  }
  EXPECT_EQ (100, ListSize());
  for (int i = 0; i < 200; i++) {
    ListAdd (loc);
  }
  for (int i = 0; i < 190; i++) {
    loc = ListQueueHead();
  }
  EXPECT_EQ (110, ListSize());
  for (int i = 0; i < 200; i++) {
    ListAdd (loc);
  }
  for (int i = 0; i < 190; i++) {
    loc = ListQueueHead();
  }
  EXPECT_EQ (120, ListSize());
}

TEST (List, ListHead_AddItems_GetFirstAdded)
{
  location_t locA = {5, 1};
  location_t locB = {6, 2};
  location_t locC = {7, 3};
  location_t locD = {8, 4};
  ListClear();
  ListAdd (locA);
  ListAdd (locB);
  ListAdd (locC);
  ListAdd (locD);
  location_t locHead = ListQueueHead();;
  EXPECT_EQ (locA.row, locHead.row);
  EXPECT_EQ (locA.col, locHead.col);
}

TEST (List, ListTail_AddItems_GetLastAdded)
{
  location_t locA = {5, 1};
  location_t locB = {6, 2};
  location_t locC = {7, 3};
  location_t locD = {8, 4};
  ListClear();
  ListAdd (locA);
  ListAdd (locB);
  ListAdd (locC);
  ListAdd (locD);
  location_t locHead = ListStackPop();
  EXPECT_EQ (locD.row, locHead.row);
  EXPECT_EQ (locD.col, locHead.col);
}


