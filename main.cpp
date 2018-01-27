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

#include <cstring>
#include <iostream>
#include "maze.h"
#include "mazeprinter.h"
#include "mazesearcher.h"
#include <glob.h>
#include <libgen.h>

uint8_t wallData[1024];

enum {
  E_FILE_NOT_FOUND = 1,
  E_FILE_READ_ERROR = 2,
};

int ReadRealWallsFromFile(char *filename) {
  FILE *fp;
  if ((fp = fopen(filename, "rb")) == nullptr) {
    return E_FILE_NOT_FOUND;
  }
  if (fread(wallData, 1, 256, fp) < 256) {
    fclose(fp);
    return E_FILE_READ_ERROR;
  };
  fclose(fp);
  return 0;
}

static char *strpad(const char *string, char pad, size_t fieldSize);

char *strpad(const char *string, char pad, size_t fieldSize) {
  size_t ssize = strlen(string);
  size_t padSize = fieldSize - ssize;
  assert(padSize > 0);
  char padding[128];
  memset(padding, pad, 126);
  padding[127] = 0;
  char *padded = (char *) malloc(fieldSize + 1);
  strncpy(padded, string, fieldSize);
  strncat(padded, padding, padSize);
//  memset(padded, pad, fieldSize);
  padded[fieldSize] = 0;
//  strcpy(padded , string);
  return padded;
}

/*
 *
 */
int main(int argc, char **argv) {
  MazeSearcher barney;
  glob_t glob_result;
  glob(argv[1], GLOB_TILDE, nullptr, &glob_result);
  std::cout << "Processing " << glob_result.gl_pathc << " mazes" << std::endl;

  if (argc >= 1) {
    Maze maze(16);
    int onePassCount = 0;
    int chancerCount = 0;
    maze.setFloodType(Maze::RUNLENGTH_FLOOD);
    for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
      std::cout << "";
      if (0 !=  ReadRealWallsFromFile(glob_result.gl_pathv[i])){
        continue;
      };
      maze.load(wallData);
      maze.copyMazeFromFileData(wallData, 256);
      maze.flood(0x77);
      barney.setRealMaze(&maze);
      barney.map()->resetToEmptyMaze();
      barney.setLocation(0x00);
      //Run a search out and back again, recording the total steps needed
      int steps = barney.searchTo(0x77);
      steps += barney.searchTo(0x00);
      barney.map()->testForSolution();
      int costDifference = barney.map()->costDifference();
      int openCost = barney.map()->openMazeCost();
      // how close to a complete solution are we?
      int residual = (100 * costDifference) / openCost;

      if (residual > 5) {
//        std::cout << glob_result.gl_pathv[i] << std::endl;
        MazePrinter::printVisitedDirs(barney.map());

      }
      char *fileName= basename(glob_result.gl_pathv[i]);
      char *name = strpad(fileName, ' ', 38);
      std::cout << name;
//      delete name;
      std::cout.width(6);
      std::cout << std::right;
      std::cout << steps << " steps - delta ";
      std::cout.width(3);
      std::cout << std::right;
      std::cout << costDifference << " (";
      std::cout.width(3);
      std::cout << std::right;
      std::cout << residual << "%)";
      if (costDifference == 0) {
        onePassCount++;
        std::cout << " Fully solved";
      } else if (residual < 5 && residual >= 0) {
        chancerCount++;
        std::cout << " Worth a run ";
      }
        std::cout << std::endl;
      delete name;

    }

    printf("\n%d mazes:\n", (int)glob_result.gl_pathc);
    printf(" one Pass mazes: %3d\n", onePassCount);
    printf(" Possible chancer  mazes: %3d\n", chancerCount);

  } else {
    printf(" you should provide the name of at least one libMaze file on the command line\n");
  }
  return (EXIT_SUCCESS);
}

