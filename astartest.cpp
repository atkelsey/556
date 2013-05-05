#include "ece556.h"

class scoreComparison
{
	bool reverse;
public:
	scoreComparison(const bool& revparam= false)
		{reverse = revparam;}
	bool operator() (const point &s1, const point &s2) const{
		if (reverse) return (s1.locScore < s2.locScore);
		return (s1.locScore > s2.locScore);
	}
/*	int Score(const point& p1, const point& T){
		int MD = abs(p1.x - T.x) + abs(p1.y - T.y);
		return MD;
	}*/
};
 void aStarRoute (routingInst* rst){
	 int i, j;
	 map<point, int> group;
	 map<point, int> distance;
	 map<point, int> score;
	 map<point, point> parent;
	 priority_queue<point, vector<point>, scoreComparison> astar_pq;
	 net currNet;
	 point S, T;

	 for (i = 0; i < rst->numNets/2; i++){
		 currNet = rst->pQueNets.top();
		 rst->pQueNets.pop();
		 S = currNet.pins[0];
		 for (j = 1; j < currNet.numPins; j++){
			 T = currNet.pins[j];
			 astar_pq.push(T);
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
