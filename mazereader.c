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

void ReadMazFileData (char * filename)
{
  FILE *fp;
  location_t loc;
  if ( (fp = fopen (filename, "rb")) == NULL) {
    assert (fp);
  }
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
      wallData[loc.row][loc.col] = fgetc (fp);
    }
  }
  fclose (fp);
}

void LoadMAZFile (char * filename)
{
  location_t loc;
  ReadMazFileData (filename);
  MazeResetWalls();
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
      MazeUpdateFromWallData (loc, wallData[loc.row][loc.col]);
    }
  }
}


void LoadEmptyMaze (void)
{
  MazeResetWalls();
  location_t loc;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    loc.col = 0;
    MazeAddWall (loc, WEST);
    loc.col = MAZE_COLS - 1;
    MazeAddWall (loc, EAST);
  }
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    loc.row = 0;
    MazeAddWall (loc, SOUTH);
    loc.row = MAZE_ROWS - 1;
    MazeAddWall (loc, NORTH);
  }
  loc.row = 0;
  loc.col = 0;
  MazeAddWall (loc, EAST);
}