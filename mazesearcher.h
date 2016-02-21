/*
 * File:   mazesearcher.h
 * Author: peterharrison
 *
 * Created on 17 February 2016, 21:31
 */

#ifndef MAZESEARCHER_H
#define MAZESEARCHER_H

#ifdef __cplusplus
extern "C" {
#endif

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

enum {
  SEARCH_RANDOM,
  SEARCH_FULL_FLOOD,
  SEARCH_MODIFIED_Flood_Open_Neighbours,
  SEARCH_MODIFIED_Flood_All_Neighbours,

};


void MouseInit (void);

location_t MousePosition (void);
direction_t MouseHeading (void);
void MouseSetPosition (location_t location);
void MouseSetHeading (direction_t direction);
void MouseMove (void);
void MouseRunTo (location_t target);
int MouseSearchToFullFlood (location_t target);
int MouseSearchToModifiedFlood (location_t target);



#ifdef __cplusplus
}
#endif

#endif /* MAZESEARCHER_H */

