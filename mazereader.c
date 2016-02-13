/* 
 * File:   mazereader.c
 * Author: peterharrison
 *
 * Created on 13 February 2016, 21:16
 */

#include <stdio.h>
#include <assert.h>
#include "maze.h"
#include "mazereader.h"

static uint8_t wallData[MAZE_ROWS][MAZE_COLS];


void ReadMAZFile(char * filename) {
  FILE *fp;
  location_t loc;
  if ((fp = fopen(filename, "rb")) == NULL) 
  assert(fp);
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
      wallData[loc.row][loc.col] = fgetc(fp);
      MazeUpdateFromWallData(loc,wallData[loc.row][loc.col]);
    }
  }
  fclose(fp);
}