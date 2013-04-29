// ECE556 - Copyright 2013 University of Wisconsin-Madison.  All Rights Reserved.

#include "ece556.h"

 int manhattanDistance(point *a, point *b){
	 return abs(a->x - b->x) + abs(a->y - b->y);
 }

 int getEdge(point *a, point *b, int xGrid, int yGrid){
	 point *smallerPt;
	 if (a->x == b->x){
		 if (a->y > b->y){
			 smallerPt = b;
		 }
		 else {
			 smallerPt = a;
		 }
		 return (yGrid*(xGrid - 1) + (smallerPt->x + smallerPt->y*xGrid));
	 }
	 else {
		 if (a->x > b->x){
			 smallerPt = b;
		 }
		 else {
			 smallerPt = a;
		 }
		 return (smallerPt->x + smallerPt->y*(xGrid -1));
	 }
 }
