/*
 * File:   list.h
 * Author: peterharrison
 *
 * Created on 13 February 2016, 16:55
 */

#ifndef LIST_H
#define LIST_H



#include <stdint.h>
#include <stdbool.h>
#include "oldmaze.h"

/* Set the list size to zero, initialise Size and MaxSize to zero*/
void ListReset (void);

/* return the number of items added to the list since last clear*/
int ListAdditions (void);

/* return true if list has no items in it */
bool ListIsEmpty (void);

/* Add an item to the tail of the list */
void ListAdd (location_t loc);

/* retrieve an item from the tail - list acts as a stack */
location_t ListStackPop (void);

/* retrieve an item from the head - list acts as a queue */
location_t ListQueueHead (void);

/* current number of items in the list */
int ListSize (void);

/* the maximum number of items in the list since it was last cleared */
int ListMaxSize (void);




#endif /* LIST_H */

