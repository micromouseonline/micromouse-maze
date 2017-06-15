
/*
 * File:   mazeprinter.c
 * Author: peterharrison
 *
 * Created on 13 February 2016, 19:53
 */
#include <stdio.h>
//#include "oldmaze.h"
#include "mazeprinter.h"
//#include "mazesearcher.h"


static char dirChars[] = "^>v< ";

void printNorthWalls(Maze *maze, int row) {
  for (int col = 0; col < maze->width(); col++) {
    uint16_t cell = row+maze->width()* col;
    printf ("o");
    if (maze->hasWall(cell,NORTH)) {
      printf ("---");
    } else {
      printf ("   ");
    }
  }
  printf ("o\n");
}

void printSouthWalls(Maze *maze, int row) {
  for (int col = 0; col < maze->width(); col++) {
    uint16_t cell = row+maze->width()* col;
    printf ("o");
    if (maze->hasWall(cell,SOUTH)) {
      printf ("---");
    } else {
      printf ("   ");
    }
  }
  printf ("o\n");
}

void MazePrinter::printDirs(Maze *maze)  {
  printf("\n");

  for (int row = maze->width() - 1; row >= 0; row--) {
    printNorthWalls(maze, row);
    /* TODO:  this is all rather messy */
    for (int col = 0; col < maze->width(); col++) {
      uint16_t cell = row+maze->width()* col;
      //Do the west walls
      if (maze->hasWall(cell,WEST)) {
        printf ("|");
      } else {
        printf (" ");
      }
        printf (" %c ", dirChars[maze->direction(cell)]);
    }
    printf ("|\n");
  }
  printSouthWalls(maze, 0);
}

void MazePrinter::printPlain(Maze *maze)  {
  printf("\n");

  for (int row = maze->width() - 1; row >= 0; row--) {
    printNorthWalls(maze, row);
    /* TODO:  this is all rather messy */
    for (int col = 0; col < maze->width(); col++) {
      uint16_t cell = row+maze->width()* col;
      if (maze->hasWall(cell,WEST)) {
        printf ("|");
      } else {
        printf (" ");
      }
      printf ("   ");
    }
    printf ("|\n");
  }
  printSouthWalls(maze, 0);
}

void MazePrinter::printCDecl(Maze *maze, const char * name)  {
  printf("\n\nconst uint8_t %s[] = {\n",name);
  for (int x = 0; x < maze->width(); x++) {
    printf("   ");
    for (int y = 0; y < maze->width(); y++) {
      uint16_t cell = x * maze->width() + y;
      printf("0x%02X, ", maze->walls(cell));
    }
    printf("\n");
  }
  printf("   };\n\n");
  return;
}
