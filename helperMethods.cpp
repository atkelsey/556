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
void ZRoutes(routingInst *rst) {
	int j, k;
	for (k = 0; k < rst->numNets; k++) {
		cout << "routing " << k << "...\n";
		rst->nets[k].croutes = new route[1];
		point small;//the smaller coordinate
		point big;//the larger coordinate
		point temp;
		route zRoute;
		vector<point> points;
		int xUtil = 0;
		int yUtil = 0;
		int xEdge;
		int yEdge;
		zRoute.numSegs = 0;
		for (j = 1; j < rst->nets[k].numPins; j++){
			points.clear();
			small = rst->nets[k].pins[j-1];
			big = rst->nets[k].pins[j];
			if (small.x != big.x){ //points are on different X axis
				if (small.x > big.x){
					temp = small;
					small = big;
					big = temp;
				}
				if (big.y > small.y){ //go up and right
					while ((big.x >= small.x) && (big.y >= small.y)){
						if(big.x == small.x){ //small is directly under big
							while (big.y >= small.y){
								points.push_back(small);
								small.y++;
							}
						}
						else if(big.y == small.y){ //small is directly to left of
							while (big.x >= small.x){
								points.push_back(small);
								small.x++;
							}
						}
						else { // small is to left and below big
							points.push_back(small);
							xEdge = getXEdge(small);
							xUtil = rst->edgeUtils[xEdge] - rst->edgeCaps[xEdge];
							yEdge = getYEdge(small);
							yUtil = rst->edgeUtils[yEdge] - rst->edgeCaps[yEdge];
							if (xUtil < yUtil){
								small.x++;
							}
							else {
								small.y++;
							}
						}
					}
				}
				else if (big.y < small.y){ //go down and right
					points.push_back(small);
					while ((big.x >= small.x) && (big.y <= small.y)){
						if(big.x == small.x){ //small is directly above big
							while (big.y <= small.y){
								points.push_back(small);
								small.y--;
							}
						}
						else if(big.y == small.y){ //small is directly to left of
							while (big.x >= small.x){
								points.push_back(small);
								small.x++;
							}
						}
						else { // small is to left and above big
							point modify;
							modify.x = small.x;
							modify.y = small.y - 1;
							points.push_back(small);
							xEdge = getXEdge(small);
							xUtil = rst->edgeUtils[xEdge] - rst->edgeCaps[xEdge];
							yEdge = getYEdge(modify);
							yUtil = rst->edgeUtils[yEdge] - rst->edgeCaps[yEdge];
							if (xUtil < yUtil){
								small.x++;
							}
							else {
								small.y--;
							}
						}
					}
				}
				else { //go directly across
					while (big.x >= small.x){
						points.push_back(small);
						small.x++;
					}
					//push edges onto a vector to be parsed later
				}
			}
			else { // go up or down
				if (small.y > big.y){
					temp = small;
					small = big; //small is lower on the y axis
					big = temp; //big is higher on the y axis
				}
				while (big.y >= small.y){
					points.push_back(small);
					small.y++;
				}
			}
			//Parse the points
			point T = points.at(points.size()-1);
			point A = points.at(0);
			point rent = points.at(1);
			point prev;
			segment seg;
			seg.numEdges = 0;
			int currEdge;
			int parentIterator = 1;
			seg.p1 = A;
			prev = A;
			while (T != A){
				parentIterator++;
				currEdge = getEdge(&rent, &A);
				if ((rent.y != seg.p1.y) && (rent.x != seg.p1.x)){
					seg.p2 = A;
					zRoute.numSegs++;
					zRoute.segments.push_back(seg);
//					rst->nets[k].croutes[0].numSegs++;
//					rst->nets[k].croutes[0].segments.push_back(seg);
					//store seg
					seg.p1 = A;
					seg.numEdges = 1;
				}
				else {
					seg.numEdges++;
				}
				seg.edges.push_back(currEdge);
				rst->edgeUtils[currEdge]++;
				prev = A;
				A = rent;
				if (parentIterator < points.size()){
					rent = points.at(parentIterator);
				}
			}
			seg.p2 = A;
			zRoute.numSegs++;
			zRoute.segments.push_back(seg);
//			rst->nets[k].croutes[0].numSegs++;
//			rst->nets[k].croutes[0].segments.push_back(seg);
		}
		rst->nets[k].croutes[0] = zRoute;
	}
}

void getLRoute(routingInst *rst) {
	int i, j, currEdge, k;
	for (k = 0; k < rst->numNets; k++) {
		cout << "routing " << k << "...\n";
		rst->nets[k].croutes = new route[1];
		point a;//the smaller coordinate
		point b;//the larger coordinate
		point temp, tempA, tempB;
		route lorFlatX, lorFlatY;
		lorFlatX.numSegs = 0;
		lorFlatY.numSegs = 0;
		int xUtil = 0;
		int yUtil = 0;
		//lorFlat.segments = new segment[2*(theNet->numPins)];
		for (j = 1; j < rst->nets[k].numPins; j++){
			a = rst->nets[k].pins[j-1];
			b = rst->nets[k].pins[j];
			tempA.x = a.x;
			tempA.y = a.y;
			tempB.x = b.x;
			tempB.y = b.y;
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
					//rst->edgeUtils[currEdge]++;
					xUtil = xUtil + rst->edgeUtils[currEdge];
					xSeg.edges.push_back(currEdge);
					a.x++;
				}
				lorFlatX.segments.push_back(xSeg);
				lorFlatX.numSegs++;
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
					//rst->edgeUtils[currEdge]++;
					xUtil = xUtil + rst->edgeUtils[currEdge];
					ySeg.edges.push_back(currEdge);
					a.y++;
				}
				lorFlatX.segments.push_back(ySeg);
				lorFlatX.numSegs++;
			}
			a.x = tempA.x;
			a.y = tempA.y;
			b.x = tempB.x;
			b.y = tempB.y;
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
					//rst->edgeUtils[currEdge]++;
					yUtil = yUtil + rst->edgeUtils[currEdge];
					ySeg.edges.push_back(currEdge);
					a.y++;
				}
				lorFlatY.segments.push_back(ySeg);
				lorFlatY.numSegs++;
			}
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
					//rst->edgeUtils[currEdge]++;
					yUtil = yUtil + rst->edgeUtils[currEdge];
					xSeg.edges.push_back(currEdge);
					a.x++;
				}
				lorFlatY.segments.push_back(xSeg);
				lorFlatY.numSegs++;
			}
		}
		if (xUtil < yUtil){
			rst->nets[k].croutes[0] = lorFlatX;
			for(i = 0; i < rst->nets[k].croutes[0].numSegs; i++){
				for (j = 0; j < rst->nets[k].croutes->segments.at(i).numEdges; j++){
					rst->edgeUtils[rst->nets[k].croutes->segments.at(i).edges.at(j)]++;
				}
			}
		}
		else {
			rst->nets[k].croutes[0] = lorFlatY;
			for(i = 0; i < rst->nets[k].croutes[0].numSegs; i++){
				for (j = 0; j < rst->nets[k].croutes->segments.at(i).numEdges; j++){
					rst->edgeUtils[rst->nets[k].croutes->segments.at(i).edges.at(j)]++;
				}
			}
		}
	}
}
bool xOrY(point a, point b, routingInst* rst){ //return true for rout x first, or false for route y
	point temp;
	int utilX = 0;
	int utilY = 0;
	int currEdge;
	if (a.x > b.x){
		temp = a;
		a = b;
		b = temp;
	}
	currEdge = getXEdge(a);
	utilX = rst->edgeUtils[currEdge] - rst->edgeCaps[currEdge];
	if (a.y > b.y){
		temp = a;
		a = b;
		b = temp;
	}
	currEdge = getXEdge(a);
	utilY = rst->edgeUtils[currEdge] - rst->edgeCaps[currEdge];
	if (utilX < utilY){
		return true;
	}
	else {
		return false;
	}
}


void updateUtil(routingInst* rst) {//Returns total overflow
	int i, j, k, tempEdge, netWeight;
	while (!(rst->pQueNets.empty())){
		rst->pQueNets.pop();
	}
	while (!rst->pQueNets.empty()){
		rst->pQueNets.pop();
	}
	for (i = 0; i < rst->numNets; i++){
		rst->nets[i].weight = 0;
		for (j = 0; j < rst->nets[i].croutes[0].numSegs; j++){
			netWeight = 0;
			for(k = 0; k < rst->nets[i].croutes[0].segments.at(j).numEdges; k++){
				tempEdge = rst->nets[i].croutes[0].segments.at(j).edges.at(k);
				//cout << "Cap " << rst->edgeCaps[tempEdge] << " Util "<< rst->edgeUtils[tempEdge] << "\n";
				netWeight = netWeight + (rst->edgeUtils[tempEdge] - rst->edgeCaps[tempEdge]);
				rst->nets[i].weight = rst->nets[i].weight + netWeight;
				//cout << "weight " << rst->nets[i].weight << "\n";
			}
		}
		rst->pQueNets.push(rst->nets[i]);
	}
}
/*Updates the weights after a RRR cycle and resets the priority queue.
 */
void resetEdge(routingInst* rst){
	int i, j, k;
	//might not need this
	delete [] rst->edgeUtils;
	int* edgeUtils = new int[rst->numEdges];
	rst->pQueNets.empty();
	std::fill(edgeUtils, edgeUtils + rst->numEdges, 0);
	//updates the edge Utils for all Nets
	for (i = 0; i < rst->numNets; i++){
		for (j = 0; j < rst->nets[i].croutes[0].numSegs; j++){
			for (k = 0; k < rst->nets[i].croutes[0].segments.at(j).numEdges; k++){
				int edge = rst->nets[i].croutes[0].segments.at(j).edges.at(k);
				edgeUtils[edge]++;
			}
		}
	}
	rst->edgeUtils = edgeUtils;
	updateUtil(rst);
}

void RipNet(routingInst* rst, int net){
	for (int i = 0; i<rst->nets[net].croutes[0].numSegs; i++){
		for (int j = 0; j < rst->nets[net].croutes[0].segments.at(i).numEdges; j++){
			int k = rst->nets[net].croutes[0].segments.at(i).edges.at(j);
			rst->edgeUtils[k]--;

		}
	}
	rst->nets[net].croutes[0].segments.clear();
	rst->nets[net].croutes[0].numSegs = 0;
	cout << "Ripping net: " << net << endl;
}

