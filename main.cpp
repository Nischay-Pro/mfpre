#include <iostream> 
#include <cstring>
#include <sys/stat.h>
#include "point.h"
#include "indicators.hpp"

using namespace std;
using namespace indicators;

int main(int argc, char *argv[]){
    int numPart = 1;
    Graph g;
    for(int i=1; i<argc; ++i)
    {
        if(strcmp(argv[i],"--quadtree") == 0){
            g.format = 1;
        }else if(strcmp(argv[i],"--legacy") == 0){
            g.format = 2;
        }else if(strcmp(argv[i],"--restart") == 0){
            g.format = 3;
        }else if(strcmp(argv[i],"--file") == 0){
            g.file = argv[i+1];
        }else if(strcmp(argv[i],"--cuda") == 0){
            if(g.format == 1){
                g.gpu = 1;
            }else if(g.format == 2){
                g.gpu = 2;
            }
        }else if(strcmp(argv[i], "--regent") == 0){
            g.regent = 1;
        }else if(strcmp(argv[i], "--hdf5") == 0){
            g.hdf5 = 1;
        }else if(atoi(argv[i]) > 0){
            numPart = atoi(argv[i]);
        }
    }

    // choose the point format
    if (g.format == 1){ // Quad tree format
	    cout << "Quadtree input format" << endl;
        cout << "Reading File";
	    g.read_point_create_graph_quad();
    }else if(g.format == 2){ // Legacy
	    cout << "Legacy input format" << endl;
        cout << "Reading File";
	    g.read_point_create_graph_legacy();
    }else if(g.format == 3){ // Restart
	    cout << "Restart input format" << endl;
        cout << "Reading File";
	    g.read_point_create_graph_restart();
    }else{
	    cout << "No input format chosen or invalid input format" << endl;
	    exit(0);
    }

    cout << termcolor::green << " ✔ " << endl << termcolor::reset;

    g.cal_min_dist();
    g.partition(numPart);

    // Creating a directory 
    if (mkdir("point", 0777) == -1) 
        cerr << "Point file status :  " << strerror(errno) << endl; 
    else
        cout << "Directory created " << endl; 

    // Choose output format
    if (g.hdf5 == 1){
        cout << "Writing HDF5 Format" << endl;
        g.write_output_hdf5(numPart);
    }
    else if (g.regent == 1){
        cout << "Writing regent mpi output" << endl;
        g.write_output_quad_regent(numPart);
    }
    else if (g.gpu == 1){ // gpu output for quadtree
	    cout << " Writing quadtree cuda output " << endl;
	    g.write_output_gpu_quad();
    }
    else if (g.gpu == 2){ // gpu output for legacy
	    cout << " Writing legacy cuda output " << endl;
	    g.write_output_gpu_legacy();
    }else if (g.format == 1) { // quadtree mpi
	    cout << " Writing quadtree mpi output " << endl;
	    g.write_output_quad(numPart); 
    }else if (g.format == 2) { // Legacy mpi
       	    cout << "Writing legacy mpi output" << endl;
	    g.write_output_legacy(numPart);
    }

    cout << "Done" << termcolor::green << " ✔ " << endl << termcolor::reset;
    

    return 0;
}

