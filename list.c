/*
 * File:   list.c
 * Author: peterharrison
 *
 * Created on 13 February 2016, 16:55
 */

#include "list.h"
#include "maze.h"

#define LIST_SIZE 256

static location_t items[LIST_SIZE];
static int head;
static int tail;
static int size;
static int maxSize;
static int additions;

void ListClear (void)
{
  head = 0;
  tail = 0;
  size = 0;
  maxSize = 0;
  additions = 0;
}

bool ListEmpty (void)
{
  return head == tail;
}

int ListAdditions (void)
{
  return additions;
}

void ListAdd (location_t loc)
{
  tail++;
  if (tail >= LIST_SIZE) {
    tail -= LIST_SIZE;
  }
  size++;
  if (size > maxSize) {
    maxSize = size;
  }
  additions++;
  items[tail] = loc;
}

location_t ListStackPop (void)
{
  location_t result;
  result = items[tail];
  tail--;
  size--;
  return result;
}

location_t ListQueueHead (void)
{
  location_t result;
  head++;
  if (head >= LIST_SIZE) {
    head -= LIST_SIZE;
  }
  size--;
  result = items[head];
  return result;
}

int ListSize (void)
{
  return size;
}

int ListMaxSize (void)
{
  return maxSize;
}

