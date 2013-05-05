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
	point S, T, u;

	for (i = 0; i < rst->numNets/2; i++){
		currNet = rst->pQueNets.top();
		rst->pQueNets.pop();
		S = currNet.pins[0];
		for (j = 1; j < currNet.numPins; j++){
			T = currNet.pins[j];
			init(S, T, group, distance, score, parent);
			astar_pq.push(S);
			while (!astar_pq.empty()){
				u = astar_pq.top();
				astar_pq.pop();
				if (u.x == T.x && u.y == T.y){
					retrace(u, rst);
				}
				else {
					int currEdge;
					int tempDist;
					point modifier;
					currEdge = getYEdge(u);
					if (((u.y + 1 ) < rst->gy) && (rst->edgeCaps[currEdge] > 0)){
						//check goal or update queue
						point v;
						v.x = u.x;
						v.y = u.y + 1;
						tempDist = distance[u] + rst->edgeUtils[currEdge];
						if ((3 == group[v]) && (distance[v] < tempDist)){
						}
						else if ((2 != group[v]) || (distance[v] > tempDist)){
							parent[v] = u;
							distance[v] = tempDist;
							score[v] = distance[v] + MD(V,T);
							if (2 != group[v]){
								astar_pq.push(v);
							}
							else {
								//update score of V
							}
						}
					}
					currEdge = getXEdge(u);
					if (((u.x + 1 ) < rst->gx) && (rst->edgeCaps[currEdge] > 0)){

					}
					modifier = u;
					modifier.y--;
					currEdge = getYEdge(modifier);
					if ((u.y > 0) && (rst->edgeCaps[currEdge] > 0)){

					}
					modifier.y++;
					modifier.x--;
					currEdge = getXEdge(modifier);
					if ((u.x > 0) && (rst->edgeCaps[currEdge] > 0)){

					}

				}
			}
		}
	}
}
void retrace (point A, routingInst* rst){
	 //trace back from A to parent to parent etc, form segments, and nets,
	 //push to priority queue;
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
