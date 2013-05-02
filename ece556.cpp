// ECE556 - Copyright 2013 University of Wisconsin-Madison.  All Rights Reserved.

#include "ece556.h"

using namespace std;
net * nets;
point * pins;
int *edge_caps;
int block = 0;
int xGridSize;
int yGridSize;

int readBenchmark(const char *fileName, routingInst *rst){
	ifstream myFile(fileName,ifstream::in);
	if (!myFile){ //if the file was not successfully opened
		cout << "Unable to open " << fileName << " for reading" << endl;
		myFile.close();
		return 0;
	}
	string line;
	int net_cnt = 0;
	int pin_cnt = 0;
	while (!getline(myFile, line).eof()){
		string result;
		istringstream iss(line);

		if (line.find("\t")!=string::npos){
			getline(iss,result, '\t');
		}
		else{
			getline(iss,result, ' ');
		}
			//parses the grid dimensions
			if (result.find("grid")!=string::npos){
				string token;
				getline(iss,token, ' ');
				istringstream (token) >> rst->gx;
				getline(iss,token, ' ');
				istringstream (token) >> rst->gy;
				int x = rst->gx;
				xGridSize = x;
				int y = rst->gy;
				yGridSize = y;
				rst->numEdges = y*(x - 1) + x*(y - 1);
			//	cout << "grid = " << rst->gx << "*" << rst->gy << " with "<< rst->numEdges << " edges" << endl;
			}
			//parses the edge capacity
			else if (result.find("capacity") != string::npos){
				string token;
				getline(iss, token, ' ');
				istringstream(token) >> rst->cap;

				edge_caps = new int[rst->numEdges];
				std::fill(edge_caps, edge_caps + rst->numEdges, rst->cap);
			//	cout << "capacity = " << rst->cap << endl;
			}
			//parses number of nets
			else if (result.find("num")!=string::npos){
				string token;
				getline(iss, token, ' ');
				getline(iss, token, ' ');
				istringstream(token) >> rst->numNets;
			//	cout << "num nets = " << rst->numNets << endl;
				nets = new net[rst->numNets];
			}
			//parses the net and number of pins
			else if (result.find('n')!= string::npos){
				string token;
				net net;
				net.id = net_cnt;
				getline(iss, token, ' ');
				istringstream(token) >> net.numPins;
				nets[net_cnt] = net;
				//cout << "Net = n" << nets[net_cnt].id << endl;
				pins = new point[nets[net_cnt].numPins];
				net_cnt++;
				pin_cnt = 0;
			}
			//parses each pin
			else if ((pin_cnt < nets[net_cnt - 1].numPins) && ((net_cnt-1) < rst->numNets) ){
				point pin;
				istringstream(result)>>pin.x;
				string token;
				getline(iss,token,'\n');
				istringstream(token) >> pin.y;
				pins[pin_cnt] = pin;
				pin_cnt++;
				if (pin_cnt == nets[net_cnt - 1].numPins){
					nets[net_cnt - 1].pins = pins;
				}
			}
			else if (block > 0){
				point p1;
				point p2;
				int cap;
				istringstream(result) >> p1.x;
				string token;
				getline(iss,token,' ');
				istringstream(token) >> p1.y;
				getline(iss,token,' ');
				istringstream(token) >> p2.x;
				getline(iss,token,' ');
				istringstream(token) >> p2.y;
				getline(iss,token,'\n');
				istringstream(token) >> cap;

				point *p1_ptr = &p1;
				point *p2_ptr = &p2;
				int edge = getEdge(p1_ptr,p2_ptr);
				edge_caps[edge] = cap;
				block--;
			}
			else{
				istringstream(result) >> block;
			}
	}
	rst->nets = nets;
	rst->edgeCaps = edge_caps;
/*	for (int i = 0; i < rst->numEdges ; i++){
		cout << rst->edgeCaps[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < rst->numNets; i++){
		cout << "Net n" << rst->nets[i].id;
		cout << " num pins: " << rst->nets[i].numPins << endl;
		for (int j = 0; j < rst->nets[i].numPins; j++){
			cout << " pin " << j << ": " << rst->nets[i].pins[j].x << "," << rst->nets[i].pins[j].y << endl;
		}
	}*/

	myFile.close();
	return 1;
}

int solveRouting(routingInst *rst){
	cout << "Started routing...\n";
	//initial solution goes here
	int i;
	//int incAmount;
	//incAmount = sizeof(net);
	for (i = 0; i < rst->numNets; i++) {
		//go through all nets and give a net assignment
		cout << "routing " << i << "...\n";
		getLRoute(&(rst->nets[i]));
	}
//	time_t startTime, elapsedTime;
//	time(&startTime);
//	int seconds = 0;
	
//	while (seconds < (15*60)){ //main loop: add all end cases here (TOF is not increasing over multiple runs)
//		//Compute edge weights
//		//Order nets in the priority queue (highest vales are worst)
//		//route each net UPdate edge util/weights
//
//
//
//		seconds = time(&elapsedTime)-startTime;
//	}

	cout << "Completed routing\n";
	return 1;
}

int writeOutput(const char *outRouteFile, routingInst *rst){
	ofstream outFile(outRouteFile);
	if (!outFile){
		cout << "Unable to open " << outRouteFile << " for writing" << endl;
		outFile.close();
		return 0;
	}
	for (int i = 0; i < rst->numNets; i++){
		outFile << "n" << rst->nets[i].id << endl;
		for (int j = 0; j < rst->nets[i].croutes->numSegs; j++){
			segment seg = rst->nets[i].croutes->segments.at(j);
			outFile << "(" << seg.p1.x << "," << seg.p1.y << ")-";
			outFile << "(" << seg.p2.x << "," << seg.p2.y << ")" << endl;
		}
		outFile << "!" << endl;
	}

	outFile.close();
	return 1;
}

int release(routingInst *rst){
	rst->cap = 0;
	rst->numEdges = 0;
	rst->gx = 0;
	rst->gy = 0;
	delete [] rst->edgeCaps;
	rst->edgeCaps = NULL;
	delete [] rst->edgeUtils;
	rst->edgeUtils = NULL;
	for (int i = 0; i < rst->numNets; i++){
		delete [] rst->nets[i].croutes;
		delete [] rst->nets[i].pins;
	}
	rst->numNets = 0;
	delete rst->nets;
	rst->nets = NULL;
	return 1;
}


