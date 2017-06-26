/*
 * File:   mazesearcher.h
 * Author: peterharrison
 *
 * Created on 17 February 2016, 21:31
 */

#ifndef MAZESEARCHER_H
#define MAZESEARCHER_H


/*
 * The mazeSearcher is the mouse. The robot that explores and runs the maze.
 * It gets its sensor data from the worldview and uses it to update a maze
 * and act appropriately.
 *
 * It is here that the behaviour of the mouse will be defined. For each
 * action, a single public function should be defined.
 *
 * Note that there is no access to private state information except through
 * accessor functions. Thus, it is possible to implement the mouse in any
 * way the user chooses and the tests will only deal with the public
 * functions.
 *
 * A single SearchTo function is provided along with an enum naming the
 * search method and means to select one of those methods.
 *
 * From the outside, code should set a method and then call MouseSearchTo().
 * there should not be any direct calls to specific search methods.
 */

class MazeSearcher {
 public:

enum {
  SEARCH_NORMAL,
  SEARCH_RANDOM,
  SEARCH_LEFT_WALL,
  SEARCH_RIGHT_WALL,
};

  enum {
    E_NO_ROUTE = -1,
    E_ROUTE_TOO_LONG = -2,
  };

  MazeSearcher();
  ~MazeSearcher();
  uint16_t location() const;
  void setLocation(uint16_t location);
  uint8_t heading() const;
  void setHeading(uint8_t heading);
  void setMazeWalls(const uint8_t *mazeWalls, uint16_t cellCount);
  Maze * maze();
  /// move the mouse 1 cell in in the current Heading
  const Maze *realMaze() const;
  void setRealMaze(const Maze *mRealMaze);
  void move();
  /// follow direction data in the maze to get to the given target cell
  /// return the number of steps needed
  int runTo(uint16_t target);
  /// search unknown maze for target cell
  /// return the number of steps needed
  int searchTo(uint16_t target);



 private:
  uint16_t mLocation;
  uint8_t mHeading;
  Maze * mMaze;
  const Maze * mRealMaze;
  bool mVerbose;
  int mSearchMethod;
 public:
  int searchMethod() const;
  void setSearchMethod(int mSearchMethod);
 public:
  bool isVerbose() const;
  void setVerbose(bool mVerbose);
 private:
  // display maze as we search or run
  MazeSearcher & operator=(const MazeSearcher& rhs) ;
  MazeSearcher(const MazeSearcher & orig);
};

//void MouseInit (void);
//location_t MousePosition (void);
//direction_t MouseHeading (void);
//void MouseSetPosition (location_t mLocation);
//void MouseSetHeading (direction_t direction);
//void MouseMove (void);
//void MouseRunTo (location_t target);
//int MouseSearchToFullFlood (location_t target);
//int MouseSearchToModifiedFlood (location_t target);
//int MouseSearchToModifiedFloodAll (location_t target);



#endif /* MAZESEARCHER_H */

