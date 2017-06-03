/*
 * File:   mazereader.c
 * Author: peterharrison
 *
 * Created on 13 February 2016, 21:16
 */

#include <stdio.h>
#include <assert.h>
#include "oldmaze.h"
#include "mazereader.h"

static uint8_t wallData[MAZE_ROWS][MAZE_COLS];

void ClearWallData(void) {
  location_t loc;
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
      wallData[loc.row][loc.col] = 0;
    }
  }
}

void ReadRealWallsFromFile(char *filename) {
  FILE *fp;
  location_t loc;
  ClearWallData(); /* in case we do not find a file */
  if ((fp = fopen(filename, "rb")) == NULL) {
    return;
  }
  fseek(fp, 0L, SEEK_END);
  long size = ftell(fp);
  // a standard maze uses 256 bytes
  // assume the first 256 bytes are the wall data
  if (size >= 256) {
    rewind(fp);
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
        wallData[loc.row][loc.col] = fgetc(fp);// & ~VISITED;
      }
    }
  }
  fclose(fp);
}

/*
 * TODO: should this be in the maze.c file?
 */
void UpdateEntireMazeFromRealWalls(void) {
  location_t loc;
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
      UpdateCellFromWallData(loc, wallData[loc.row][loc.col]);
    }
  }
}
  void UpdateEntireMazeFromData(const uint8_t * data) {
    location_t loc;
    for(int i = 0; i < MAZE_COLS*MAZE_ROWS;i++){
      ((uint8_t *)wallData)[i] = data[i];
    }
    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
      for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
        UpdateCellFromWallData(loc, wallData[loc.col][loc.row]);
      }
    }
  }


walldata_t ReadWallSensors(location_t loc) {
  return wallData[loc.row][loc.col];
}

