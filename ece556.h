// ECE556 - Copyright 2013 University of Wisconsin-Madison.  All Rights Reserved.

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <vector>
using std::vector;
using std::map;


#ifndef ECE556_H
#define ECE556_H

#include <stdio.h>

 /**
  * A structure to represent a 3D Point.
  */
 typedef struct
 {
   int x ; /* x coordinate ( >=0 in the routing grid)*/
   int y ; /* y coordinate ( >=0 in the routing grid)*/

 } point ;


  /**
  * A structure to represent a segment
  */
 typedef struct
 {
   point p1 ; 	/* start point of a segment */
   point p2 ; 	/* end point of a segment */
   int numEdges ; 	/* number of edges in the segment*/
   //int *edges ;  	/* array of edges representing the segment*/
   vector<int> edges;

 } segment ;


  /**
  * A structure to represent a route
  */
  typedef struct
  {

	vector<point> segments;
    int numSegs ;  	/* number of segments in a route*/
    //segment *segments ;  /* an array of segments (note, a segment may be flat, L-shaped or any other shape, based on your preference */

  } route ;


  /**
  * A structure to represent nets
  */
  typedef struct
  {

   int id ; 		/* ID of the net */
   int numPins ; 	/* number of pins (or terminals) of the net */
   point *pins ; 	/* array of pins (or terminals) of the net. */
   int numCRoutes ; 	/* number of (candidate) routes of the net. This may be equal to one (only one candidate route) in your implementation. */
   route *croutes ;	/* array of candidate routes of the net. */

  } net ;

  /**
  * A structure to represent the routing instance
  */
  typedef struct
  {
   int gx ;		/* x dimension of the global routing grid */
   int gy ;		/* y dimension of the global routing grid */

   int cap ;

   int numNets ;	/* number of nets */
   net *nets ;		/* array of nets */

   int numEdges ; 	/* number of edges of the grid */
   int *edgeCaps; 	/* array of the actual edge capacities after considering for blockages */
   int *edgeUtils;	/* array of edge utilizations */

  } routingInst ;


/* int readBenchmark(const char *fileName, routingInst *rst)
   Read in the benchmark file and initialize the routing instance.
   This function needs to populate all fields of the routingInst structure.
   input1: fileName: Name of the benchmark input file
   input2: pointer to the routing instance
   output: 1 if successful
*/
int readBenchmark(const char *fileName, routingInst *rst);


/* int solveRouting(routingInst *rst)
   This function creates a routing solution
   input: pointer to the routing instance
   output: 1 if successful, 0 otherswise (e.g. the data structures are not populated)
*/
int solveRouting(routingInst *rst);

/* int writeOutput(const char *outRouteFile, routingInst *rst)
   Write the routing solution obtained from solveRouting().
   Refer to the project link for the required output format.

   Finally, make sure your generated output file passes the evaluation script to make sure
   it is in the correct format and the nets have been correctly routed. The script also reports
   the total wirelength and overflow of your routing solution.

   input1: name of the output file
   input2: pointer to the routing instance
   output: 1 if successful, 0 otherswise(e.g. the output file is not valid)
  */
  int writeOutput(const char *outRouteFile, routingInst *rst);

  /* int release(routingInst *rst)
     Release the memory for all the allocated data structures.
     Failure to release may cause memory problems after multiple runs of your program.
     Need to recursively delete all memory allocations from bottom to top
     (starting from segments then routes then individual fields within a net struct,
     then nets, then the fields in a routing instance, and finally the routing instance)

     output: 1 if successful, 0 otherswise
  */
 int release(routingInst *rst);

 int manhattanDistance(point *a, point *b);

 int getEdge(point *smallerPt, point *largerPt);

 int getYEdge(point smallerPt);

 int getXEdge(point smallerPt);

 int updateUtil(routingInst* rst);

 void getLRoute(net *theNet);

 extern int xGridSize;
 extern int yGridSize;

#endif // ECE556_H
