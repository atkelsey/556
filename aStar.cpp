#include "ece556.h"

class scoreComparison
{
	bool reverse;
public:
	scoreComparison(const bool& revparam= false)
{reverse = revparam;}
	bool operator() (const point &s1, const point &s2) const{
		if (reverse) return (s1.locScore > s2.locScore);
		return (s1.locScore < s2.locScore);
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
	point * T_ptr = &T;
	priority_queue<net, vector<net>, NetComparator> pQueNets;

	for (i = 0; i < rst->numNets/2; i++){
		currNet = rst->pQueNets.top();
		RipNet(rst, currNet.id);
		rst->pQueNets.pop();
		S = currNet.pins[0];
		for (j = 1; j < currNet.numPins; j++){
			cout << "A Star pin: " << j << endl;
			T = currNet.pins[j];
			init(S, T, group, distance, score, parent, rst);
			astar_pq.push(S);
			while (!astar_pq.empty()){
				u = astar_pq.top();
				astar_pq.pop();
				if (u.x == T.x && u.y == T.y){
					retrace(u, rst, parent, currNet.id);
				}
				else {
					int currEdge;
					int tempDist;
					point modifier;
					currEdge = getYEdge(u);
					if (((u.y + 1 ) < rst->gy) && (rst->edgeCaps[currEdge] > 0)){
						//check goal or update queue
						point v;
						point * v_ptr = &v;
						v.x = u.x;
						v.y = u.y + 1;
						tempDist = distance[u] + rst->edgeUtils[currEdge];
						if ((3 == group[v]) && (distance[v] < tempDist)){
						}
						else if ((2 != group[v]) || (distance[v] > tempDist)){
							parent[v] = u;
							distance[v] = tempDist;
							score[v] = distance[v] + manhattanDistance(v_ptr,T_ptr);
							v.locScore = score[v];
							if (2 != group[v]){
								astar_pq.push(v);
							}
							else {
								priority_queue<point, vector<point>, scoreComparison> tempAstar_pq;
								while (!astar_pq.empty()){
									tempAstar_pq.push(astar_pq.top());
									astar_pq.pop();
								}
								astar_pq = tempAstar_pq;
							}
						}
					}
					currEdge = getXEdge(u);
					if (((u.x + 1 ) < rst->gx) && (rst->edgeCaps[currEdge] > 0)){
						//check goal or update queue
						point v;
						point * v_ptr = &v;
						v.x = u.x + 1;
						v.y = u.y;
						tempDist = distance[u] + rst->edgeUtils[currEdge];
						if ((3 == group[v]) && (distance[v] < tempDist)){
						}
						else if ((2 != group[v]) || (distance[v] > tempDist)){
							parent[v] = u;
							distance[v] = tempDist;
							score[v] = distance[v] + manhattanDistance(v_ptr,T_ptr);
							v.locScore = score[v];
							if (2 != group[v]){
								astar_pq.push(v);
							}
							else {
								priority_queue<point, vector<point>, scoreComparison> tempAstar_pq;
								while (!astar_pq.empty()){
									tempAstar_pq.push(astar_pq.top());
									astar_pq.pop();
								}
								astar_pq = tempAstar_pq;
							}
						}
					}
					modifier = u;
					modifier.y--;
					currEdge = getYEdge(modifier);
					if ((u.y > 0) && (rst->edgeCaps[currEdge] > 0)){
						//check goal or update queue
						point v;
						point * v_ptr = &v;
						v.x = u.x;
						v.y = u.y - 1;
						tempDist = distance[u] + rst->edgeUtils[currEdge];
						if ((3 == group[v]) && (distance[v] < tempDist)){
						}
						else if ((2 != group[v]) || (distance[v] > tempDist)){
							parent[v] = u;
							distance[v] = tempDist;
							score[v] = distance[v] + manhattanDistance(v_ptr,T_ptr);
							v.locScore = score[v];
							if (2 != group[v]){
								astar_pq.push(v);
							}
							else {
								priority_queue<point, vector<point>, scoreComparison> tempAstar_pq;
								while (!astar_pq.empty()){
									tempAstar_pq.push(astar_pq.top());
									astar_pq.pop();
								}
								astar_pq = tempAstar_pq;
							}
						}
					}
					modifier.y++;
					modifier.x--;
					currEdge = getXEdge(modifier);
					if ((u.x > 0) && (rst->edgeCaps[currEdge] > 0)){
						//check goal or update queue
						point v;
						point * v_ptr = &v;
						v.x = u.x - 1;
						v.y = u.y;
						tempDist = distance[u] + rst->edgeUtils[currEdge];
						if ((3 == group[v]) && (distance[v] < tempDist)){
						}
						else if ((2 != group[v]) || (distance[v] > tempDist)){
							parent[v] = u;
							distance[v] = tempDist;
							score[v] = distance[v] + manhattanDistance(v_ptr,T_ptr);
							v.locScore = score[v];
							if (2 != group[v]){
								astar_pq.push(v);
							}
							else {
								priority_queue<point, vector<point>, scoreComparison> tempAstar_pq;
								while (!astar_pq.empty()){
									tempAstar_pq.push(astar_pq.top());
									astar_pq.pop();
								}
								astar_pq = tempAstar_pq;
//								priority_queue<point, vector<point>, scoreComparison> tempAstar_pq;
//								while (!astar_pq.empty() && astar_pq.top() != v){
//									tempAstar_pq.push(astar_pq.top());
//									astar_pq.pop();
//								}
//								if (astar_pq.top() == v) {
//									tempAstar_pq.push(astar_pq.top());
//									astar_pq = tempAstar_pq;
//								}
//								else {
//									while (!tempAstar_pq.empty()){
//										astar_pq.push(tempAstar_pq.top());
//										tempAstar_pq.pop();
//									}
//								}
								//Resort the queue to reflect updated score of V
								//update score of V
							}
						}
					}

				}
			}
		}
		pQueNets.push(currNet);
	}
	while (!rst->pQueNets.empty()){
		pQueNets.push(rst->pQueNets.top());
		rst->pQueNets.pop();
	}
	rst->pQueNets = pQueNets;
}
void retrace (point A, routingInst* rst, map<point, point> parent, int netID){
	 cout << "Retracing net: " << netID << endl;
	//trace back from A to parent to parent etc, form segments, and nets,
	//push to priority queue;
	point rent = parent[A];
	point prev;
	segment seg;
	seg.numEdges = 0;
	int currEdge;
	seg.p1 = A;
	prev = A;
	while (rent != A){
		currEdge = getEdge(&rent, &A);
		if ((rent.y != seg.p1.y) && (rent.x != seg.p1.x)){
			seg.p2 = prev;
			rst->nets[netID].croutes[0].numSegs++;
			rst->nets[netID].croutes[0].segments.push_back(seg);
			//store seg
			seg.p1 = prev;
			seg.numEdges = 1;
			seg.edges.push_back(currEdge);
			rst->edgeUtils[currEdge]++;
		}
		else {
			seg.edges.push_back(currEdge);
			seg.numEdges++;
			rst->edgeUtils[currEdge]++;
			prev = A;
			A = rent;
			rent = parent[A];
		}
	}
}
void init(point S, point T,
		map<point, int> group,
		map<point, int> distance,
		map<point, int> score,
		map<point, point> parent, routingInst *rst){
	int i, j;
	for (i = 0; i < rst->gx; i++){
		for (j = 0; j < rst->gy; j++){
			point temp;
			temp.x = i;
			temp.y = j;
			group.insert(pair<point, int>(temp, 1));
		}
	}
	distance.insert(pair<point, int>(S, INT_MAX));
	score.insert(pair<point, int>(S, INT_MAX));
	S.locScore = INT_MAX;
	//group.insert(pair<point, int>(S, 1));
	parent.insert(pair<point, point>(S, S));
	distance.insert(pair<point, int>(T, 0));
	score.insert(pair<point, int>(T, 0));
	T.locScore = 0;
}

