// ECE556 - Copyright 2013 University of Wisconsin-Madison.  All Rights Reserved.

#include "ece556.h"

 int manhattanDistance(point *a, point *b){
	 return abs(a->x - b->x) + abs(a->y - b->y);
 }
