/*
 * File:   mazepathfinder.h
 * Author: peterharrison
 *
 * Created on 16 February 2016, 14:55
 */

#ifndef MAZEPATHFINDER_H
#define MAZEPATHFINDER_H



/*
 * clear all the direction arrows except those along the least-cost path
 * from start to target.
 * Expects a flooded maze.
 * Returns without any action if the start cost is MAX_COST, indicating
 * there is no route to the goal
 * An unflooded maze will have undefined results - the function may not return.
 */

/* TODO: make this follow a path until there is no smaller neighbour */
int IsolatePath (location_t start, location_t target);




#endif /* MAZEPATHFINDER_H */

