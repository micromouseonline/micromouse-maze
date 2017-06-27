
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


static char dirChars[] = "^>v<  ";

void printNorthWalls(Maze *maze, int row) {
  for (int col = 0; col < maze->width(); col++) {
    uint16_t cell = row + maze->width() * col;
    printf("o");
    if (maze->hasWall(cell, NORTH)) {
      printf("---");
    } else {
      printf("   ");
    }
  }
  printf("o\n");
}

void printSouthWalls(Maze *maze, int row) {
  for (int col = 0; col < maze->width(); col++) {
    uint16_t cell = row + maze->width() * col;
    printf("o");
    if (maze->hasWall(cell, SOUTH)) {
      printf("---");
    } else {
      printf("   ");
    }
  }
  printf("o\n");
}

void MazePrinter::printDirs(Maze *maze) {
  printf("\n");
  for (int row = maze->width() - 1; row >= 0; row--) {
    printNorthWalls(maze, row);
    for (int col = 0; col < maze->width(); col++) {
      uint16_t cell = row + maze->width() * col;
      if (maze->hasWall(cell, WEST)) {
        printf("|");
      } else {
        printf(" ");
      }
      uint8_t direction = maze->direction(cell);
      if (direction > WEST) {
        direction = NONE;
      }
      printf(" %c ", dirChars[direction]);
    }
    printf("|\n");
  }
  printSouthWalls(maze, 0);
}

void MazePrinter::printVisitedDirs(Maze *maze) {
  printf("\n");
  for (int row = maze->width() - 1; row >= 0; row--) {
    printNorthWalls(maze, row);
    for (int col = 0; col < maze->width(); col++) {
      uint16_t cell = row + maze->width() * col;
      if (maze->hasWall(cell, WEST)) {
        printf("|");
      } else {
        printf(" ");
      }
      uint8_t direction = maze->direction(cell);
      if (!maze->isVisited(cell)) {
        direction = UNSEEN;
      }
      printf(" %c ", dirChars[direction]);
    }
    printf("|\n");
  }
  printSouthWalls(maze, 0);
}

void MazePrinter::printPlain(Maze *maze) {
  printf("\n");

  for (int row = maze->width() - 1; row >= 0; row--) {
    printNorthWalls(maze, row);
    /* TODO:  this is all rather messy */
    for (int col = 0; col < maze->width(); col++) {
      uint16_t cell = row + maze->width() * col;
      if (maze->hasWall(cell, WEST)) {
        printf("|");
      } else {
        printf(" ");
      }
      printf("   ");
    }
    printf("|\n");
  }
  printSouthWalls(maze, 0);
}

void MazePrinter::printCDecl(Maze *maze, const char *name) {
  printf("\n\nconst uint8_t %s[] = {\n", name);
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

void MazePrinter::printRawDecl(Maze *maze, const char *name) {
  printf("\n\nconst uint8_t %s[] = {\n", name);
  for (int x = 0; x < maze->width(); x++) {
    printf("   ");
    for (int y = 0; y < maze->width(); y++) {
      uint16_t cell = x * maze->width() + y;
      printf("0x%02X, ", maze->internalWalls(cell));
    }
    printf("\n");
  }
  printf("   };\n\n");
  return;
}

void MazePrinter::printCosts(Maze *maze) {
  printf("\n");

  for (int row = maze->width() - 1; row >= 0; row--) {
    printNorthWalls(maze, row);
    /* TODO:  this is all rather messy */
    for (int col = 0; col < maze->width(); col++) {
      uint16_t cell = row + maze->width() * col;
      if (maze->hasWall(cell, WEST)) {
        printf("|");
      } else {
        printf(" ");
      }
      uint16_t cost = maze->cost(cell);
      if (cost < MAX_COST) {
        printf("%3d", cost);
      } else {
        printf(" - ");
      }
    }
    printf("|\n");
  }
  printSouthWalls(maze, 0);
}

