// ECE556 - Copyright 2013 University of Wisconsin-Madison.  All Rights Reserved.

#include "ece556.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
net * nets;
point * pins;
int block = 0;
int readBenchmark(const char *fileName, routingInst *rst){
	ifstream myFile(fileName,ifstream::in);
	if (!myFile){ //if the file was not successfully opened
		cout << "file not read" << endl;
		myFile.close();
		return 0;
	}

	string line;
	int net_cnt = 0;
	int pin_cnt = 0;
	while (!getline(myFile, line).eof()){
		//cout << line << endl;
		istringstream iss(line);
		string result;
		if (getline(iss, result, ' ')){
			//cout << result << endl;
			//parses the grid dimensions
			if (result == "grid"){
				string token;
				getline(iss,token, ' ');
				istringstream (token) >> rst->gx;
				getline(iss,token, ' ');
				istringstream (token) >> rst->gy;
				int x = rst->gx;
				int y = rst->gy;
				rst->numEdges = y*(x - 1) + x*(y - 1);
				cout << "grid = " << rst->gx << "*" << rst->gy << " with "<< rst->numEdges << " edges" << endl;
			}
			//parses the edge capacity
			else if (result == "capacity"){
				string token;
				getline(iss, token, ' ');
				istringstream(token) >> rst->cap;
				cout << "capacity = " << rst->cap << endl;
			}
			//parses number of nets
			else if (result == "num"){
				string token;
				getline(iss, token, ' ');
				getline(iss, token, ' ');
				istringstream(token) >> rst->numNets;
				cout << "num nets = " << rst->numNets << endl;
				nets = new net[rst->numNets];
			}
			//parses the net and number of pins
			else if (result.find('n') != string::npos){
				string token;
				net net;
				net.id = net_cnt;
				getline(iss, token, ' ');
				istringstream(token) >> net.numPins;
				nets[net_cnt] = net;
				cout << "Net = n" << nets[net_cnt].id << endl;
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

				/*
				calculate new edge capacities
				*/

				block--;
			}
			else{
				istringstream(result) >> block;
			}
		}
	}
	rst->nets = nets;
	for (int i = 0; i < rst->numNets; i++){
		cout << "Net n" << rst->nets[i].id;
		cout << " num pins: " << rst->nets[i].numPins << endl;
		for (int j = 0; j < rst->nets[i].numPins; j++){
			cout << " pin " << j << ": " << rst->nets[i].pins[j].x << "," << rst->nets[i].pins[j].y << endl;
		}
	}
	myFile.close();
	return 1;
}

int solveRouting(routingInst *rst){
  /*********** TO BE FILLED BY YOU **********/

  return 1;
}

int writeOutput(const char *outRouteFile, routingInst *rst){
  /*********** TO BE FILLED BY YOU **********/

  return 1;
}


int release(routingInst *rst){
  /*********** TO BE FILLED BY YOU **********/

  return 1;
}


