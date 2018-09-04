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
#include <cstdio>
#include <stdlib.h>
#include "maze.h"
#include "mazeprinter.h"

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

  glob_t glob_result;
  glob(argv[1], GLOB_TILDE, nullptr, &glob_result);
  std::cout << "Processing " << glob_result.gl_pathc << " mazes" << std::endl;

  if (argc >= 1) {
    Maze maze(16);
    maze.setFloodType(Maze::RUNLENGTH_FLOOD);
    for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
      std::cout << "";
      if (0 != ReadRealWallsFromFile(glob_result.gl_pathv[i])) {
        continue;
      };
      maze.load(wallData);
      maze.copyMazeFromFileData(wallData, 256);
      maze.flood(0x77);
    }
  } else {
    printf(" you should provide the name of at least one libMaze file on the command line\n");
  }
  return (EXIT_SUCCESS);
}

