#include <metis.h>
#include <iostream>
#include <iomanip> 
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <set>
#include <map>
#include <climits>
#include <cassert>

using namespace std;

typedef struct point {
    idx_t id;
    double x, y;
    int left, right;
    int qtdepth;
    double nx, ny;
    double min_dist;
    idx_t flag1, flag2;
} point;

class Graph{
	public:
		idx_t nvtxs;
		idx_t nParts;
		int * totalPoints;
		int * currGlobalNum;
		idx_t * part;
		set<int> * ghosts;
		map<int, int> * inputToLoc;
		map<int, int> inputToGlob;
		vector<point> ptVec;
		vector<idx_t> xadjVec;
		vector<idx_t> adjncyVec;
		int format;
		int gpu;
		int regent;
		int hdf5;
		string file;
		
		// read file and build graph
		Graph(){ format = 0; gpu = 0; regent = 0; hdf5 = 0;};

		void read_point_create_graph_legacy();
		void read_point_create_graph_quad();
		void read_point_create_graph_restart();
		void cal_min_dist();
		void partition(int);
		string getfileName(int, int );
		void write_output_gpu_legacy();
		void write_output_gpu_quad();
		void write_output_legacy(int);
		void write_output_quad(int);
		void write_output_quad_regent(int);
		void write_output_hdf5();
		 
};
