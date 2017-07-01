//
// Created by Peter Harrison on 01/07/2017.
//

#ifndef MICROMOUSE_MAZE_PATH_TEST_DATA_H
#define MICROMOUSE_MAZE_PATH_TEST_DATA_H

#define MAX_CMD_COUNT 256
#include <stdint.h>
#include "commands.h"
typedef struct {
  char input[MAX_CMD_COUNT];
  uint8_t  expected[MAX_CMD_COUNT];
} testPair_t;


extern testPair_t testPairs[];



int testCount();
#endif //MICROMOUSE_MAZE_PATH_TEST_DATA_H
