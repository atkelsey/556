// ECE556 - Copyright 2013 University of Wisconsin-Madison.  All Rights Reserved.

#include "ece556.h"

 int manhattanDistance(point *a, point *b){
	 return abs(a->x - b->x) + abs(a->y - b->y);
 }

 int getXEdge(point *smallerPt){//Return the edge directly right of given point
	return (smallerPt->x + smallerPt->y*(xGridSize -1));
 }

 int getYEdge(point *smallerPt){ //Returns the edge directly above the given point
	return (yGridSize*(xGridSize - 1) + (smallerPt->x + smallerPt->y*xGridSize));
 }

 int getEdge(point *smallerPt, point *largerPt){//Returns edge between two points
	 if (smallerPt->x == largerPt->x){
		 return (yGridSize*(xGridSize - 1) + (smallerPt->x + smallerPt->y*xGridSize));
	 }
	 else {
		 return (smallerPt->x + smallerPt->y*(xGridSize -1));
	 }
 }
 /*segment* getSegment(point *a, point *b){
	 segment xSeg;
	 point *smallerPt;
	 segment* segPtr = &xSeg;
	 if (a->x == b->x){
		 if (a->y > b->y){
			 smallerPt = b;
		 }
		 else {
			 smallerPt = a;
		 }
		 return (yGridSize*(xGridSize - 1) + (smallerPt->x + smallerPt->y*xGridSize));
	 }
	 else {
		 if (a->x > b->x){
			 smallerPt = b;
		 }
		 else {
			 smallerPt = a;
		 }
		 return (smallerPt->x + smallerPt->y*(xGridSize -1));
	 }
 }*/
 route* getLRoute(point *a, point *b) {
	 route lorFlat;
	 route *ptr = &lorFlat;
	 point *small;
	 point *large;
	 int i;
	 ptr->numSegs = 0;
	 if (a->x != b->x){
		 segment xSeg;
		 segment* xSegPtr = &xSeg;
		 if (a->x < b->x){
			 small = a;
			 large = b;
		 }
		 else {
			 small = b;
			 large = a;
		 }
		 for (i = 0; i < (large->x - small->x); i++){
			 xSegPtr->edges[i] = getEdge(small, large);
			 xSegPtr->numEdges++;
		 }

	 }
	 if (a->y != b->y){
		 segment ySeg;
		 segment* ySegPtr = &ySeg;
		 if (a->y < b->y){
			 small = a;
			 large = b;
		 }
		 else {
			 small = b;
			 large = a;
		 }
		 for (i = 0; i < (large->y - small->y); i++){
			 ySegPtr->edges[i] = getEdge(small, large);
			 ySegPtr->numEdges++;
		 }
	 }
 }

