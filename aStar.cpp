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
	priority_queue<net, vector<net>, NetComparator> pQueNets;

	for (i = 0; i < (rst->numNets * .0002 ); i++){
		net currNet;
		currNet = rst->pQueNets.top();
		RipNet(rst, currNet.id);
		rst->pQueNets.pop();
		for (j = 1; j < currNet.numPins; j++){
			point S, T, u;
			point * T_ptr = &T;
			priority_queue<point, vector<point>, scoreComparison> astar_pq;
			astar_pq = priority_queue<point, vector<point>, scoreComparison>();
			S = currNet.pins[j-1];
			T = currNet.pins[j];
			//cout << "A Star pin: " << S.x <<","<<S.y << "  " <<T.x << "," << T.y << endl;

			parent.clear();
			score.clear();
			distance.clear();
			group.clear();

			// initialize the maps
			for (int e = 0; e < rst->gx; e++){
				for (int d = 0; d < rst->gy; d++){
					point temp;
					temp.x = e;
					temp.y = d;
					group[temp] = 1;
					distance[temp] = INT_MAX;
					score[temp] = INT_MAX;
					temp.locScore = INT_MAX;
					parent[temp] = temp;
				}
			}
			distance[S] = 0;
			score[S] = 0;
			S.locScore = 0;
			//Maps initialized

			//init(&S, &group, &distance, &score, &parent, rst);
			astar_pq.push(S);
			while (!astar_pq.empty()){
//				cout << group.size() << "Map size" << endl;
				u = astar_pq.top();
				//cout << u.x << " , " << u.y << endl;
				//cout << astar_pq.size() << endl;
				astar_pq.pop();
				group[u] = 3;
				if (u.x == T.x && u.y == T.y){
					while (!astar_pq.empty()){
						astar_pq.pop();
					}
					retrace(S, u, rst, &parent, currNet.id);
					break;
				}
				else {
					int currEdge;
					int tempDist;
					point modifier;
					currEdge = getYEdge(u);
					if (((u.y + 1 ) < rst->gy)/*&& (rst->edgeCaps[currEdge] > 0)*/){
						//check goal or update queue
						point v;
						point * v_ptr = &v;
						v.x = u.x;
						v.y = u.y + 1;
						tempDist = distance[u] + rst->edgeUtils[currEdge];
						//cout << group[v] << " " << distance[v] << " "<< v.x << "," << v.y << endl;
						if ((3 == group[v]) && (distance[v] <= tempDist)){
							//continue to next
						}
						else if ((2 != group[v]) || (distance[v] > tempDist)){
							parent[v] = u;
							distance[v] = tempDist;
							score[v] = distance[v] + manhattanDistance(v_ptr,T_ptr);
							v.locScore = score[v];
//							cout << v.x << "," << v.y << " group: " << group[v] <<endl;

							group[v] = 2;
							astar_pq.push(v);
//							if (2 != group[v]){
//								group[v] = 2;
//								//cout << group[v] << endl;
//								astar_pq.push(v);
//							}
//							else {
////								cout << "group # " << group[v] << "que size " << astar_pq.size() << endl;
//								priority_queue<point, vector<point>, scoreComparison> tempAstar_pq;
//								tempAstar_pq = priority_queue<point, vector<point>, scoreComparison>();
//								while (!astar_pq.empty()){
//									tempAstar_pq.push(astar_pq.top());
//									astar_pq.pop();
//								}
//								astar_pq = priority_queue<point, vector<point>, scoreComparison>();
//								astar_pq = tempAstar_pq;
//							}
						}
					}
					currEdge = getXEdge(u);
					if (((u.x + 1 ) < rst->gx)/* && (rst->edgeCaps[currEdge] > 0)*/){
						//check goal or update queue
						point v;
						point * v_ptr = &v;
						v.x = u.x + 1;
						v.y = u.y;
						//cout << v.x << "," << v.y << endl;
						tempDist = distance[u] + rst->edgeUtils[currEdge];
						if ((3 == group[v]) && (distance[v] <= tempDist)){
							//continue to next
						}
						else if ((2 != group[v]) || (distance[v] > tempDist)){
							parent[v] = u;
							distance[v] = tempDist;
							score[v] = distance[v] + manhattanDistance(v_ptr,T_ptr);
							v.locScore = score[v];
//							cout << v.x << "," << v.y << " group: " << group[v] <<endl;
							group[v] = 2;
							astar_pq.push(v);
//							if (2 != group[v]){
//								group[v] = 2;
//								//cout << group[v] << endl;
//								astar_pq.push(v);
//							}
//							else {
////								cout << "group # " << group[v] << "que size " << astar_pq.size() << endl;
//								priority_queue<point, vector<point>, scoreComparison> tempAstar_pq;
//								tempAstar_pq = priority_queue<point, vector<point>, scoreComparison>();
//								while (!astar_pq.empty()){
//									tempAstar_pq.push(astar_pq.top());
//									astar_pq.pop();
//								}
//								astar_pq = priority_queue<point, vector<point>, scoreComparison>();
//								astar_pq = tempAstar_pq;
//							}
						}
					}
					modifier = u;
					modifier.y--;
					currEdge = getYEdge(modifier);
					if ((u.y > 0)/* && (rst->edgeCaps[currEdge] > 0)*/){
						//check goal or update queue
						point v;
						point * v_ptr = &v;
						v.x = u.x;
						v.y = u.y - 1;
						//cout << v.x << "," << v.y << endl;
						tempDist = distance[u] + rst->edgeUtils[currEdge];
						if ((3 == group[v]) && (distance[v] <= tempDist)){
							//continue to next
						}
						else if ((2 != group[v]) || (distance[v] > tempDist)){
							parent[v] = u;
							distance[v] = tempDist;
							score[v] = distance[v] + manhattanDistance(v_ptr,T_ptr);
							v.locScore = score[v];
//							cout << v.x << "," << v.y << " group: " << group[v] <<endl;
							group[v] = 2;
							astar_pq.push(v);
//							if (2 != group[v]){
//								group[v] = 2;
//								//cout << group[v] << endl;
//								astar_pq.push(v);
//							}
//							else {
////								cout << "group # " << group[v] << "que size " << astar_pq.size() << endl;
//								priority_queue<point, vector<point>, scoreComparison> tempAstar_pq;
//								tempAstar_pq = priority_queue<point, vector<point>, scoreComparison>();
//								while (!astar_pq.empty()){
//									tempAstar_pq.push(astar_pq.top());
//									astar_pq.pop();
//								}
//								astar_pq = priority_queue<point, vector<point>, scoreComparison>();
//								astar_pq = tempAstar_pq;
//							}
						}
					}
					modifier.y++;
					modifier.x--;
					currEdge = getXEdge(modifier);
					//cout << rst->edgeCaps[currEdge] << endl;
					if ((u.x > 0)/* && (rst->edgeCaps[currEdge] > 0)*/){
						//check goal or update queue
						point v;
						point * v_ptr = &v;
						v.x = u.x - 1;
						v.y = u.y;
						//cout << v.x << "," << v.y << endl;
						tempDist = distance[u] + rst->edgeUtils[currEdge];
						if ((3 == group[v]) && (distance[v] <= tempDist)){
						}
						else if ((2 != group[v]) || (distance[v] > tempDist)){
							parent[v] = u;
							distance[v] = tempDist;
							score[v] = distance[v] + manhattanDistance(v_ptr,T_ptr);
							v.locScore = score[v];
//							cout << v.x << "," << v.y << " group: " << group[v] <<endl;
							group[v] = 2;
							astar_pq.push(v);
//							if (2 != group[v]){
//								group[v] = 2;
//								//cout << group[v] << endl;
//								astar_pq.push(v);
//							}
//							else {
////								cout << "group # " << group[v] << "que size " << astar_pq.size() << endl;
//								priority_queue<point, vector<point>, scoreComparison> tempAstar_pq;
//								tempAstar_pq = priority_queue<point, vector<point>, scoreComparison>();
//								while (!astar_pq.empty()){
//									tempAstar_pq.push(astar_pq.top());
//									astar_pq.pop();
//								}
//								astar_pq = priority_queue<point, vector<point>, scoreComparison>();
//								astar_pq = tempAstar_pq;
//							}
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
//							}
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
void retrace (point S, point A, routingInst* rst, map<point, point> *parent, int netID){
//	cout << "Retracing net: " << netID << endl;
	//trace back from A to parent to parent etc, form segments, and nets,
	//push to priority queue;
	point rent = (*parent)[A];
	point prev;
	segment seg;
	seg.numEdges = 0;
	int currEdge;
	seg.p1 = A;
	prev = A;
	while (S != A){
		currEdge = getEdge(&rent, &A);
		if ((rent.y != seg.p1.y) && (rent.x != seg.p1.x)){
			seg.p2 = A;
			rst->nets[netID].croutes[0].numSegs++;
			rst->nets[netID].croutes[0].segments.push_back(seg);
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
		rent = (*parent)[A];
	}
	seg.p2 = A;
	rst->nets[netID].croutes[0].numSegs++;
	rst->nets[netID].croutes[0].segments.push_back(seg);
}
//void init(point *S,
//		map<point, int> *group,
//		map<point, int> *distance,
//		map<point, int> *score,
//		map<point, point> *parent, routingInst *rst){
//	int i, j;
//	for (i = 0; i < rst->gx; i++){
//		for (j = 0; j < rst->gy; j++){
//			point temp;
//			temp.x = i;
//			temp.y = j;
//			//group->[temp] = 1;
//			//cout << group[temp] << endl;
//			//distance[temp] = INT_MAX;
//			//cout << distance[temp] << endl;
//			//score[temp] = INT_MAX;
//			//cout << score[temp] << endl;
//			//temp.locScore = INT_MAX;
//			//parent[temp] = temp;
//			//cout << parent[temp].x << "," << parent[temp].y << endl;
//			group->insert(pair<point, int>(temp, 1));
//			distance->insert(pair<point, int>(temp, INT_MAX));
//			temp.locScore = INT_MAX;
//			score->insert(pair<point, int>(temp, INT_MAX));
//			parent->insert(pair<point, point>(temp, temp));
//		}
//	}
//	//cout << "Parent S" << parent[S].x << parent[S].y << endl;
//	//cout << "S" << S.x << S.y << endl;
//	//distance[S] = 0;
//	//score[S] = 0;
//	S->locScore = 0;
//}

