/************************************************************************
*
* Copyright (C) 2017 by Peter Harrison. www.micromouseonline.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without l> imitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
************************************************************************/

#ifndef _maze_h
#define _maze_h

#include <cstdint>

#include "mazeconstants.h"
#include "floodinfo.h"
#include "priorityqueue.h"


class Maze {

public:
  explicit Maze(uint16_t width);
  enum FloodType {
    MANHATTAN_FLOOD,
    WEIGHTED_FLOOD,
    RUNLENGTH_FLOOD
  };

  /// the maze is assumed to be square
  uint16_t width() const; ///
  uint16_t numCells(); ///

  ///  reset the wall, cost and direction data to defaults
  void clearData();
  /// clear the data and then set all the walls that exist in an empty maze
  void resetToEmptyMaze(); ///

  /// return the column number of  given cell
  inline uint16_t col(uint16_t cell) {
    return cell / mWidth;
  }
  /// return the roww number of a given cell
  inline uint16_t row(uint16_t cell) {
    return cell % mWidth;
  }
  ///  return the cell index from row and column
  inline uint16_t cell(uint16_t col, uint16_t row) {
    return row + col * mWidth;
  }

  /// return the address of the cell ahead from this cardinal direction
  static uint8_t ahead(uint8_t direction);
  /// return the address of the cell on the right of this cardinal direction
  static uint8_t rightOf(uint8_t direction);
  /// return the address of the cell on the left of this cardinal direction
  static uint8_t leftOf(uint8_t direction);
  /// return the address of the cell behind this cardinal direction
  static uint8_t behind(uint8_t direction);
  /// return the address of the cell opposite the given wall
  static uint8_t opposite(uint8_t direction);
  static uint8_t differenceBetween(uint8_t oldDirection, uint8_t newDirection);

  // static functions about neighbours
  /// return the address of the cell in the indicated direction
  uint16_t cellNorth(uint16_t cell);
  /// return the address of the cell in the indicated direction
  uint16_t cellEast(uint16_t cell);
  /// return the address of the cell in the indicated direction
  uint16_t cellSouth(uint16_t cell);
  /// return the address of the cell in the indicated direction
  uint16_t cellWest(uint16_t cell);

  /// return the address of the cell in the given direction
  uint16_t neighbour(uint16_t cell, uint16_t direction);

  /// return the address of the home cell. Nearly always cell zero
  uint16_t home();
  /// return the cell address of the current goal
  uint16_t goal();
  ///  set the current goal to a new value
  void setGoal(uint16_t goal);

  /// return the state of the four walls surrounding a given cell
  /// NOTE: should this be always the open maze
  uint8_t walls(uint16_t cell) const;
  wall_t xwalls(uint16_t cell) const;
  bool hasExit(uint16_t cell, uint8_t direction) const;
  ///  test for the presence of a wall. Don't care if it is seen or not
  bool hasWall(uint16_t cell, uint8_t direction) const DEPRECATED("Use the version of hasWall with an explicit mask");
  bool hasWall(uint16_t cell, uint8_t direction, uint8_t mask) const;
  bool hasMaskedWall(uint16_t cell, uint8_t direction) ;
  ///  it is not clear that these two mthods have any actual use
  ///  test for the definite, observed absence of a wall.
  bool hasRealExit(uint16_t cell, uint8_t direction) const;
  ///  test for the definite, observed presence of a wall.
  bool hasRealWall(uint16_t cell, uint8_t direction) const;
  inline bool isExit(uint8_t wall, uint8_t mask) const {
    return (wall & mask) == EXIT;
  };
  inline bool isWall(uint8_t wall, uint8_t mask) const {
    return (wall & mask) != EXIT;
  };
  /// return the stored direction for the given cell
  uint8_t direction(uint16_t cell);
  /// set the direction for the given cell
  void setDirection(uint16_t cell, uint8_t direction);

  /// test to see if  all the walls of a given cell have been seen
  bool isVisited(uint16_t cell);
  /// set a cell as having all the walls seen
  void setVisited(uint16_t cell);
  /// set a cell as having none of the walls seen
  void clearVisited(uint16_t cell);

  /// NOT TO BE USED IN SEARCH. Unconditionally set a  wall in a cell and mark as seen.
  void setWall(uint16_t cell, uint8_t direction);
  /// NOT TO BE USED IN SEARCH. Unconditionally clear a  wall in a cell and mark as seen.
  void clearWall(uint16_t cell, uint8_t direction);

  /// USE THIS FOR SEARCH. Update a single cell with wall data (normalised for direction)
  void updateMap(uint16_t cell, uint8_t wallData);

  /// Set all unseen walls as present. This is the closed maze used to test for a solution
  void setUnknowns();
  /// Set all unseen walls as present. This is the open maze used for path generation
  void clearUnknowns();

  /// return the cost value for a given cell. Used in flooding and searching
  uint16_t cost(uint16_t cell);
  /// return the cost in the neighbouring cell in the given direction
  uint16_t cost(uint16_t cell, uint16_t direction);

  /// set the cost in the given cell.
  void setCost(uint16_t cell, uint16_t cost); ///

  /// examine the goal area and move the goal if needed for a better entry speed
  void recalculateGoal();

  /// return the cost of the current best path assuming unknowns are absent
  uint16_t openMazeCost() const;
  /// return the cost of the current best path assuming unknowns are present
  uint16_t closedMazeCost() const;
  /// return the difference between the open and closed cost. Zero when the best route is found.
  int32_t costDifference();
  /// flood the maze for the give goal
  uint16_t flood(uint16_t target);
  /// RunLengthFlood is a specific kind of flood used in this mouse
  uint16_t runLengthFlood(uint16_t target);
  /// manhattanFlood is a the simplest kind of flood used in this mouse
  uint16_t manhattanFlood(uint16_t target);
  /// weightedFlood assigns a penalty to turns vs straights
  uint16_t weightedFlood(uint16_t target);

  /// Flood the maze both open and closed and then test the cost difference
  /// leaves the maze with unknowns clear
  bool testForSolution();
  /// returns the result of the most recent test for a solution
  bool isSolved();

  ///  return the direction from the given cell to the least costly neighbour
  uint8_t directionToSmallest(uint16_t cell);
  /// for every cell in the maze, calculate and store the least costly direction
  void updateDirections();

  /// save the wall data, including visited flags in the target array. Not checked for overflow.
  void save(uint8_t *data);

  /// load the wall data, including visited flags from the target array. Not checked for overflow.
  void load(const uint8_t *data);


  /// Clear the costs and directions and then copy the walls from an array
  void copyMazeFromFileData(const uint8_t *wallData, uint16_t cellCount) DEPRECATED(" use void loadFromFileData(const uint8_t *wallData)");
  void loadFromFileData(const uint8_t *fileData);


  /// set and get the Flood Type to use
  void setFloodType(FloodType mFloodType);
  FloodType floodType() DEPRECATED("Has no purpose?");

  /// used only for the weighted Flood
  uint16_t getCornerWeight() const;
  void setCornerWeight(uint16_t cornerWeight);

public:
  uint8_t getMSafetyMask() const;
protected:
  /// safety mask lets us choose to ignore unkmown walls
  uint8_t mSafetyMask;
  /// the width of the maze in cells. Assume mazes are always square
  uint16_t mWidth;
  /// stores the wall and visited flags. Allows for 32x32 maze but wastes space
  wall_t mWalls[1024];
  /// stores the least costly direction. Allows for 32x32 maze but wastes space
  uint8_t mDirection[1024];
  /// stores the cost information from a flood. Allows for 32x32 maze but wastes space
  uint16_t mCost[1024];
  /// the current goal as defined by the conetst rules
  uint16_t mGoal;
  /// The cost of the best path assuming unseen walls are absent
  uint16_t mPathCostOpen;
  /// The cost of the best path assuming unseen walls are present
  uint16_t mPathCostClosed;
  /// flag set when maze has been solved
  bool mIsSolved;
  /// Remember which type of flood is to be used
  FloodType mFloodType;
  /// the weighted flood needs a cost for corners
  uint16_t mCornerWeight;
  /// used to set up the queue before running the more complex floods
  void seedQueue(PriorityQueue<FloodInfo> &queue, uint16_t goal, uint16_t cost);
  /// set all the cell costs to their maxumum value, except the target
  void initialiseFloodCosts(uint16_t target);

};

#endif

