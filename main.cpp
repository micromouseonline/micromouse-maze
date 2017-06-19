/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: peterharrison
 *
 * Created on 07 February 2016, 23:47
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "mazeprinter.h"
//#include "mazepathfinder.h"
//#include "mazesearcher.h"
#include <glob.h>

uint8_t wallData[1024];

int ReadRealWallsFromFile(char *filename) {
  FILE *fp;

//  ClearWallData(); /* in case we do not find a file */
  if ((fp = fopen(filename, "rb")) == NULL) {
    return 1;
  }
  if (fread(wallData, 1, 256, fp) < 256) {
    fclose(fp);
    return 2;
  };

//  fseek(fp, 0L, SEEK_END);
//  long size = ftell(fp);
//  // a standard maze uses 256 bytes
//  // assume the first 256 bytes are the wall data
//  if (size >= 256) {
//    rewind(fp);
//    for (loc.col = 0; loc.col < MAZE_COLS; loc.col++) {
//      for (loc.row = 0; loc.row < MAZE_ROWS; loc.row++) {
//        wallData[loc.row][loc.col] = fgetc(fp);// & ~VISITED;
//      }
//    }
//  }
  fclose(fp);
  return 0;
}

/*
 *
 */
int main(int argc, char **argv) {
//  MazeResetWalls();
//  MouseInit();
//  location_t target = DefaultGoal();
  glob_t glob_result;
  glob("./mazefiles/*", GLOB_TILDE, NULL, &glob_result);
  if (argc > 1) {
    Maze maze(16);
    int totalMazes = 0;
    int fullCount = 0;
    int fullfullCount = 0;
    int modAllCount = 0;
    int modOpenCount = 0;
    printf("   FULL  MODOPEN   MODALL\n");
    for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
      std::cout << "\n\n\n";
      std::cout << glob_result.gl_pathv[i] << std::endl;
      ReadRealWallsFromFile(glob_result.gl_pathv[i]);
      maze.resetToEmptyMaze();
      maze.load(wallData);
      maze.copyMazeFromFileData(wallData, 256);
      maze.flood(0x77);
      MazePrinter::printDirs(&maze);

//    for (int i = 1; i < argc; i++) {
//      ReadRealWallsFromFile(argv[i]);
//
//      MouseInit();
//      MazeInit();
//      int stepsFull = MouseSearchToFullFlood(target);
//      MouseInit();
//      MazeInit();
//      int stepsModOpen = MouseSearchToModifiedFlood(target);
//      MouseInit();
//      MazeInit();
//      int stepsModAll = MouseSearchToModifiedFloodAll(target);
//      char x, y, z;
//      x = ' ';
//      y = ' ';
//      z = ' ';
//      if ((stepsFull < stepsModOpen) && (stepsFull < stepsModAll)) {
//        x = '*';
//        fullCount++;
//      }
//      if ((stepsModOpen < stepsFull) && (stepsModOpen < stepsModAll)) {
//        y = '*';
//        modOpenCount++;
//      }
//      if ((stepsModAll < stepsFull) && (stepsModAll < stepsModOpen)) {
//        z = '*';
//        modAllCount++;
//      }
//      if ((stepsFull >= stepsModAll) || (stepsFull >= stepsModOpen)) {
//        x = '!';
//        fullfullCount++;
//      }
//      totalMazes++;
//      printf("%7d%c  %9d%c  %9d%c  steps for %s\n", stepsFull, x, stepsModOpen, y, stepsModAll, z, argv[i]);
//      //printf ("%4d : %3d %c %3d steps for %s\n", stepsFull - stepsModAll, stepsFull, (stepsFull > stepsModAll) ? '>' : '<', stepsModAll,  argv[i]);
    }
    printf("\n%d mazes:\n", totalMazes);
    printf("                Full FULL Flood %3d mazes\n", fullfullCount);
    printf("                     Full Flood %3d mazes\n", fullCount);
    printf(" Modified Open Neighbours Flood %3d mazes\n", modOpenCount);
    printf("  Modified All Neighbours Flood %3d mazes\n", modAllCount);
    printf("\n%3d mazes in total\n", fullfullCount + fullCount + modOpenCount + modAllCount);
  } else {
//    char fileName[] = "mazefiles/minos03f.maz";
//    ReadRealWallsFromFile(fileName);
//    MouseInit();
//    MazeInit();
//    printf(" : %s\n", fileName);
//    int steps = MouseSearchToFullFlood(target);
//    printf("searched in %d steps\n", steps);
//    int length = IsolatePath(Home(), Goal());
//    printf("Path length is %d cells\n", length);

  }
  return (EXIT_SUCCESS);
}

