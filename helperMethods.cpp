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

 void getLRoute(routingInst *rst) {
	 int i, j, currEdge, k;
	 for (k = 0; k < rst->numNets; k++) {
		 cout << "routing " << k << "...\n";
		 rst->nets[k].croutes = new route[1];
		 point a;//the smaller coordinate
		 point b;//the larger coordinate
		 point temp;
		 route lorFlat;
		 lorFlat.numSegs = 0;
		 //lorFlat.segments = new segment[2*(theNet->numPins)];
		 for (j = 1; j < rst->nets[k].numPins; j++){
			 a = rst->nets[k].pins[j-1];
			 b = rst->nets[k].pins[j];
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
						 //cout << a.x << "," << a.y << "  " << b.x << "," << b.y << "\n";
						 currEdge = getXEdge(a);
						 //cout << "edge number x " << currEdge << "\n";
						 rst->edgeUtils[currEdge]++;
						 xSeg.edges.push_back(currEdge);
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
						 //cout << a.x << "," << a.y << "  " << b.x << "," << b.y << "\n";
						 currEdge = getYEdge(a);
						 //cout << "edge number y " << currEdge << "\n";
						 rst->edgeUtils[currEdge]++;
						 ySeg.edges.push_back(currEdge);
						 a.y++;
					 }
					 lorFlat.segments.push_back(ySeg);
					 lorFlat.numSegs++;
				 }
		 }
		 rst->nets[k].croutes[0] = lorFlat;
	 }
 }

 int updateUtil(routingInst* rst) {//Returns total overflow
	 int i, j, k, TOF, tempEdge, netWeight;
	 TOF = 0;
	 for (i = 0; i < rst->numNets; i++){
		 rst->nets[i].weight = 0;
		 for (j = 0; j < rst->nets[i].croutes[0].numSegs; j++){
			 netWeight = 0;
			 for(k = 0; k < rst->nets[i].croutes[0].segments.at(j).numEdges; k++){
				 tempEdge = rst->nets[i].croutes[0].segments.at(j).edges.at(k);
				 //cout << "Cap " << rst->edgeCaps[tempEdge] << " Util "<< rst->edgeUtils[tempEdge] << "\n";
				 if (rst->edgeCaps[tempEdge] != 0){
					 netWeight = netWeight + (rst->edgeUtils[tempEdge] / rst->edgeCaps[tempEdge]);
					 rst->nets[i].weight = rst->nets[i].weight + netWeight;
					 //cout << "weight " << rst->nets[i].weight << "\n";
				 }
				 else {
					 //cout << "BOOM \n";
					 netWeight = INT_MAX;
					 rst->nets[i].weight = netWeight;
				 }
				 if (rst->edgeUtils[tempEdge] > rst->edgeCaps[tempEdge]){
					 TOF++;
				 }
			 }
		 }
		 rst->pQueNets.push(rst->nets[i]);
	 }
	 return TOF;
 }
 void aStarRoute (routingInst* rst){

 }

