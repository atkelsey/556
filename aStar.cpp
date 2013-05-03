// ECE556 - Copyright 2013 University of Wisconsin-Madison.  All Rights Reserved.

#include "ece556.h"


 void aStarRoute (routingInst* rst){
	 int i, j;
	 map<point, int> group;
	 map<point, int> distance;
	 map<point, int> score;
	 map<point, point> parent;
	 net currNet;
	 point S, T;
	  struct ScoreComparator {
	      bool operator() (const point& p1, const point& p2) {
	          return score[p1] > score[p2]; //calls your operator
	      }
	  };
	 priority_queue<point, vector<point>, ScoreComparator> group2;
	 for (i = 0; i < rst->numNets/2; i++){
		 currNet = rst->pQueNets.top();
		 rst->pQueNets.pop();
		 S = currNet.pins[0];
		 for (j = 1; j < currNet.numPins; j++){
			 T = currNet.pins[j];
			 group2.push()
		 }
	 }
 }
 void init(point S, point T,
	 map<point, int> group,
	 map<point, int> distance,
	 map<point, int> score,
	 map<point, point> parent){
	 distance.insert(pair<point, int>(S, INT_MAX));
	 score.insert(pair<point, int>(S, INT_MAX));
	 group.insert(pair<point, int>(S, 1));
	 parent.insert(pair<point, point>(S, NULL));
	 distance.insert(pair<point, int>(T, 0));
	 score.insert(pair<point, int>(T, 0));
 }
