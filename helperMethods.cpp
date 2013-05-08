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


	int updateUtil(routingInst* rst) {//Returns total overflow
		int i, j, k, TOF, tempEdge, netWeight;
		while (!(rst->pQueNets.empty())){
			rst->pQueNets.pop();
		}
		TOF = 0;
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
					if (rst->edgeCaps[tempEdge] != 0){
						netWeight = netWeight + (rst->edgeUtils[tempEdge] - rst->edgeCaps[tempEdge]);
						rst->nets[i].weight = rst->nets[i].weight + netWeight;
						//cout << "weight " << rst->nets[i].weight << "\n";
					}
					else {
						//cout << "BOOM \n";
						netWeight = rst->edgeUtils[tempEdge];
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
	/*Updates the weights after a RRR cycle and resets the priority queue.
	 */
	int resetEdge(routingInst* rst){
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
		return updateUtil(rst);
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

