/*
 * File:   mazereader.h
 * Author: peterharrison
 *
 * Created on 13 February 2016, 21:16
 */

#ifndef MAZEREADER_H
#define MAZEREADER_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Read a set of wall data from a standard maz file. The working maze and data
 * is unaffected. To grab the wall information for a single cell, call the
 * ReadCellWallData() function
 */
void ReadRealWallsFromFile (char * filename);

/*
 * Use the real world wall data to update the entire maze
 */
void UpdateEntireMazeFromRealWalls () ;

/*
 * Return wall data for a single cell without updating the working maze.
 * Use this when searching to simulate grabbing wall sensor data.
 */
walls_t ReadWallSensors (location_t loc);




#ifdef __cplusplus
}
#endif

#endif /* MAZEREADER_H */

