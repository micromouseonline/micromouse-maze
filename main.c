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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "maze.h"
#include "mazeprinter.h"
#include "mazereader.h"
#include "mazeflooder.h"

/*
 *
 */
int main(int argc, char** argv) {
  printf("micromouse maze\n");
  MazeResetData();

  ReadMAZFile("mazefiles/minos03f.maz");
  ReadMAZFile("mazefiles/taiwan-2014-final.maz");
  ReadMAZFile("mazefiles/minos04f.maz");
  int i = 1;
  while (i < argc) {
    location_t target = {7, 7};
    ReadMAZFile(argv[i]);
    FloodMazeClassic(target);
    printf(" : %s\n", argv[i]);
    //ReadMAZFile ("mazefiles/empty.maz");
    //ReadEmptyMaze();
    i++;
  }
  //PrintMaze (WALLS + DIRS);
  return (EXIT_SUCCESS);
}

