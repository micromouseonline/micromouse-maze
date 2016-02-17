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


void ReadMAZFile (char * filename)
{
  FILE *fp;
  location_t loc;
  if ( (fp = fopen (filename, "rb")) == NULL) {
    assert (fp);
  }
  MazeResetWalls();
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
      wallData[loc.row][loc.col] = fgetc (fp);
      MazeUpdateFromWallData (loc, wallData[loc.row][loc.col]);
    }
  }
  fclose (fp);
}


void ReadEmptyMaze (void)
{
  MazeResetWalls();
  location_t loc;
  for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
    loc.col = 0;
    MazeSetWall (loc, WEST);
    loc.col = MAZE_COLS - 1;
    MazeSetWall (loc, EAST);
  }
  for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
    loc.row = 0;
    MazeSetWall (loc, SOUTH);
    loc.row = MAZE_ROWS - 1;
    MazeSetWall (loc, NORTH);
  }
  loc.row = 0;
  loc.col = 0;
  MazeSetWall (loc, EAST);
}