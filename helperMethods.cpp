// ECE556 - Copyright 2013 University of Wisconsin-Madison.  All Rights Reserved.

#include "ece556.h"

 int manhattanDistance(point *a, point *b){
	 return abs(a->x - b->x) + abs(a->y - b->y);
 }

 int getXEdge(point a){//Return the edge directly right of given point
	return (a.x + a.y*(xGridSize -1));
 }

 int getYEdge(point a){ //Returns the edge directly above the given point
	return (yGridSize*(xGridSize - 1) + (a.x + a.y*xGridSize));
 }

 int getEdge(point *a, point *b){//Returns edge between two points
	 point *smallerPt;
	 if (a->x == b->x){
		 if (a->y < b->y){
			 smallerPt = a;
		 }
		 else{
			 smallerPt = b;
		 }
		 return (yGridSize*(xGridSize - 1) + (smallerPt->x + smallerPt->y*xGridSize));
	 }
	 else {
		 if (a->x < b->x){
			 smallerPt = a;
		 }
		 else{
			 smallerPt = b;
		 }
		 return (smallerPt->x + smallerPt->y*(xGridSize -1));
	 }
 }

 void getLRoute(net *theNet) {
	 int i, j;
	 for (i = 0; i < theNet->numPins; i++){
		 theNet->pins[i].locScore = (theNet->median.x - theNet->pins->x)
				 + 0.5*abs(theNet->median.y - theNet->pins->y);
	 }
	 for (i = 0; i < theNet->numPins; i++){
		 theNet->pQuePins.push(theNet->pins[i]);
	 }
	 theNet->croutes = new route[1];
	 point a;//the smaller coordinate
	 point b;//the larger coordinate
	 point temp;
	 route lorFlat;
	 lorFlat.numSegs = 0;
	 //lorFlat.segments = new segment[2*(theNet->numPins)];
	 a = theNet->pQuePins.top();
	 theNet->pins[0] = a;
	 theNet->pQuePins.pop();
	 for (j = 1; j < theNet->numPins; j++){
		 b = theNet->pQuePins.top();
		 theNet->pins[j] = b;
		 theNet->pQuePins.pop();
		 	 if (a.x != b.x){
		 		 segment xSeg;
		 		 if (a.x > b.x){
		 			 temp = a;
		 			 a = b;
		 			 b = temp;
		 		 }
		 		 xSeg.p1.x = a.x;
		 		 xSeg.p1.y = a.y;
		 		 xSeg.p2.x = b.x;
		 		 xSeg.p2.y = a.y;
		 		 xSeg.numEdges = (b.x - a.x);
		 		 //xSeg.edges = new int[xSeg.numEdges];
		 		 for (i = 0; i < xSeg.numEdges; i++){
		 			 xSeg.edges.push_back(getXEdge(a));
		 			 a.x++;
		 		 }
		 		 lorFlat.segments.push_back(xSeg);
		 		 lorFlat.numSegs++;
		 	 }
		 	 if (a.y != b.y){
		 		 segment ySeg;
		 		 if (a.y > b.y){
		 			 temp = a;
		 			 a = b;
		 			 b = temp;
		 		 }
		 		 ySeg.p1.x = a.x;
		 		 ySeg.p1.y = a.y;
		 		 ySeg.p2.x = a.x;
		 		 ySeg.p2.y = b.y;
		 		 ySeg.numEdges = (b.y - a.y);
		 		 //ySeg.edges = new int[ySeg.numEdges];
		 		 for (i = 0; i < ySeg.numEdges; i++){
		 			 ySeg.edges.push_back(getYEdge(a));
		 			 a.y++;
		 		 }
		 		 lorFlat.segments.push_back(ySeg);
		 		 lorFlat.numSegs++;
		 	 }
		a = b;
	 }
	 theNet->croutes[0] = lorFlat;
 }

 int updateUtil(routingInst* rst) {//Returns total overflow
	 int i, j, k, TOF, tempEdge;
	 for (i = 0; i < rst->numNets; i++){
		 for (j = 0; j < rst->nets[i].croutes[0].numSegs; j++){
			 for(k = 0; k < rst->nets[i].croutes[0].segments.at(j).numEdges; k++){
				 tempEdge = rst->nets[i].croutes[0].segments.at(j).edges.at(k);
				 rst->edgeUtils[tempEdge]++;
				 if (rst->edgeUtils[tempEdge] > rst->edgeCaps[tempEdge]){
					 TOF++;
				 }
			 }
		 }
	 }
	 return TOF;
 }

