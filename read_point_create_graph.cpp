#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <math.h> 


#include "point.h"

using namespace std;

void Graph::read_point_create_graph_legacy(){
	ifstream infile("point-input");
	assert(infile.is_open());
	string line;
	nvtxs = 0;
	xadjVec.push_back(adjncyVec.size());
	int i = 0;
	cout << "Reading Input File";
	while(getline(infile, line)){
		i++;
		nvtxs++;
		istringstream iss(line);
		point temp ;
		iss >> temp.id >> temp.x >> temp.y
			>> temp.left >> temp.right 
        	        >> temp.flag1 >> temp.flag2;
		temp.min_dist = 10000;
		ptVec.push_back(temp);
		int neighborId;
		int neighborCount;
		iss >> neighborCount;
		while(iss >> neighborId){
	                adjncyVec.push_back(neighborId-1);
		}
		xadjVec.push_back(adjncyVec.size());
	}
	cout << " ... [Done]" << endl << "Points Loaded: " << i << endl;
}

void Graph::read_point_create_graph_quad(){
	ifstream infile("point-input");
	assert(infile.is_open());
	string line;
	nvtxs = 0;
	xadjVec.push_back(adjncyVec.size());
	int i = 0;
	cout << "Reading Input File";
	while(getline(infile, line)){
		nvtxs++;
		i++;
		istringstream iss(line);
		point temp ;
		iss >> temp.id >> temp.x >> temp.y
			>> temp.left >> temp.right
        	        >> temp.flag1 >> temp.flag2;
		temp.min_dist = 10000;
		ptVec.push_back(temp);
		int neighborId;
		int neighborCount;
		iss >> neighborCount;
		while(iss >> neighborId){
	                adjncyVec.push_back(neighborId-1);
		}
		xadjVec.push_back(adjncyVec.size());
	}
	cout << " ... [Done]" << endl << "Points Loaded: " << i << endl;
}

void Graph::read_point_create_graph_restart(){
	ifstream infile("point-input");
	assert(infile.is_open());
	string line;
	nvtxs = 0;
	xadjVec.push_back(adjncyVec.size());
	int i = 0;
	while(getline(infile, line)){
		i++;
		nvtxs++;
		istringstream iss(line);
		point temp ;
		iss >> temp.id >> temp.x >> temp.y
			>> temp.left >> temp.right
        	        >> temp.flag1 >> temp.flag2;
		temp.min_dist = 10000;
		ptVec.push_back(temp);
		int neighborId;
		int neighborCount;
		iss >> neighborCount;
		while(iss >> neighborId){
	                adjncyVec.push_back(neighborId-1);
		}
		xadjVec.push_back(adjncyVec.size());
	}
	cout << " ... [Done]" << endl << "Points Loaded: " << i << endl;
}

void Graph::cal_min_dist(){
	for (int i = 0; i < nvtxs ; i++){
		for (int j = xadjVec[i]; j < xadjVec[i+1]; j++){
			double dx = ptVec[adjncyVec[j]].x - ptVec[i].x;
			double dy = ptVec[adjncyVec[j]].y - ptVec[i].y;
			double ds = sqrt(dx*dx + dy*dy);
			if(ds < ptVec[i].min_dist)
				ptVec[i].min_dist = ds;
		}
	}
}
