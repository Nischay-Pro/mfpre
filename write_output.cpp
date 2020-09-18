#include <iostream>
#include <fstream>

#include "point.h"
#include <H5Cpp.h>

using namespace std;
using namespace H5;

// generates filename in string format from partition number
string Graph::getfileName(int partID, int nParts){
	string s;
        stringstream out;
        out << partID;
        s = out.str();
        if(nParts == 1)
		return "partGrid";
        else {
		if(partID > -1 && partID < 10){
			return "partGrid000" + s;
		}
		else if(partID > 99 && partID < 1000){
			return "partGrid0" + s;
		}
		else 
			return "partGrid00" + s;
	}
}


void Graph::write_output_gpu_legacy(){
	
	/*  writing output routine  */
        // create files and write basic info
	for(int i=0; i<nParts; i++){
		string filename = getfileName(i, nParts);
		string folder = "point/";
		ofstream outfile (folder.append(filename.c_str()));
		outfile << totalPoints[i]+ghosts[i].size() << endl;
	}

        // local nodes
        for(int i = 0; i < nvtxs; i++){
		int partnId = part[i];
		string filename = getfileName(partnId, nParts);
		fstream write;
		string folder = "point/";
		write.open(folder.append(filename.c_str()), fstream::app);
		write << fixed;
		write << setprecision(20)  << ptVec[i].x << " " << ptVec[i].y 
			<< " " << inputToLoc[partnId][ptVec[i].left] << " " << inputToLoc[partnId][ptVec[i].right] << " " << ptVec[i].flag1 << " " << ptVec[i].flag2 << " " << ptVec[i].min_dist << " ";
		write << xadjVec[i+1]-xadjVec[i] << " ";
		for(idx_t j=xadjVec[i]; j<xadjVec[i+1]; j++){
			write << inputToLoc[partnId][adjncyVec[j]+1] << " ";
		}          
		currGlobalNum[partnId]++;   
		write << endl;
		write.close(); 
	}

        // ghost nodes
        for(int i=0; i < nParts; i++) {
		string filename = getfileName(i, nParts);
		fstream write;
		string folder = "point/";
		write.open(folder.append(filename.c_str()), fstream::app);
		set<int>::iterator itr;
		write << fixed << setprecision(20);
		for(itr = ghosts[i].begin(); itr!=ghosts[i].end(); itr++){
			write  << inputToGlob[*itr] << ptVec[*itr].x << " " << ptVec[*itr].y << " " << ptVec[*itr].min_dist << "  ";
			write << endl;
		}
		write.close(); 
	}
	
}

void Graph::write_output_gpu_quad(){
	
	/*  writing output routine  */
        // create files and write basic info
	for(int i=0; i<nParts; i++){
		string filename = getfileName(i, nParts);
		string folder = "point/";
		ofstream outfile (folder.append(filename.c_str()));
		outfile << totalPoints[i]+ghosts[i].size() << endl;
	}

        // local nodes
        for(int i = 0; i < nvtxs; i++){
		int partnId = part[i];
		string filename = getfileName(partnId, nParts);
		fstream write;
		string folder = "point/";
		write.open(folder.append(filename.c_str()), fstream::app);
		write << fixed;
		write << setprecision(20)  << ptVec[i].x << " " << ptVec[i].y 
			<< " " << inputToLoc[partnId][ptVec[i].left] << " " << inputToLoc[partnId][ptVec[i].right] << " " << ptVec[i].flag1 << " " << ptVec[i].flag2 << " " << ptVec[i].nx << " "<< ptVec[i].ny <<" "<< ptVec[i].qtdepth << " "<<ptVec[i].min_dist << " ";
		write << xadjVec[i+1]-xadjVec[i] << " ";
		for(idx_t j=xadjVec[i]; j<xadjVec[i+1]; j++){
			write << inputToLoc[partnId][adjncyVec[j]+1] << " ";
		}          
		currGlobalNum[partnId]++;   
		write << endl;
		write.close(); 
	}

        // ghost nodes
        for(int i=0; i < nParts; i++) {
		string filename = getfileName(i, nParts);
		fstream write;
		string folder = "point/";
		write.open(folder.append(filename.c_str()), fstream::app);
		set<int>::iterator itr;
		write << fixed << setprecision(20);
		for(itr = ghosts[i].begin(); itr!=ghosts[i].end(); itr++){
			write  << inputToGlob[*itr] << ptVec[*itr].x << " " << ptVec[*itr].y << " " << ptVec[*itr].min_dist << "  ";
			write << endl;
		}
		write.close(); 
	}
	
}

void Graph::write_output_legacy(int numPart){
	
	/*  writing output routine  */
        // create files and write basic info
	for(int i=0; i<nParts; i++){
		string filename = getfileName(i, nParts);
		string folder = "point/";
		ofstream outfile (folder.append(filename.c_str()));
		outfile << numPart << " " << totalPoints[i]+ghosts[i].size() << " "<< totalPoints[i] << " " << ghosts[i].size() << endl;
	}

        // local nodes
        for(int i = 0; i < nvtxs; i++){
		int partnId = part[i];
		string filename = getfileName(partnId, nParts);
		fstream write;
		string folder = "point/";
		write.open(folder.append(filename.c_str()), fstream::app);
		write << fixed;
		write << ptVec[i].id  << setprecision(20) << " " << ptVec[i].x << " " << ptVec[i].y 
			<< " " << inputToLoc[partnId][ptVec[i].left] << " " << inputToLoc[partnId][ptVec[i].right]<< " " << ptVec[i].flag1 << " " << ptVec[i].flag2 << " " << ptVec[i].min_dist << " ";
		write << xadjVec[i+1]-xadjVec[i] << " ";
		for(idx_t j=xadjVec[i]; j<xadjVec[i+1]; j++){
			write << inputToLoc[partnId][adjncyVec[j]+1] << " ";
		}          
		currGlobalNum[partnId]++;   
		write << endl;
		write.close(); 
	}

        // ghost nodes
        for(int i=0; i < nParts; i++) {
		string filename = getfileName(i, nParts);
		fstream write;
		string folder = "point/";
		write.open(folder.append(filename.c_str()), fstream::app);
		set<int>::iterator itr;
		write << fixed << setprecision(20);
		for(itr = ghosts[i].begin(); itr!=ghosts[i].end(); itr++){
			write << inputToGlob[*itr] << "  " << ptVec[*itr].x << " " << ptVec[*itr].y << " " << ptVec[*itr].min_dist << "  ";
			write << endl;
		}
		write.close(); 
	}
}

void Graph::write_output_quad(int numPart){
	
	/*  writing output routine  */
        // create files and write basic info
	for(int i=0; i<nParts; i++){
		string filename = getfileName(i, nParts);
		string folder = "point/";
		ofstream outfile (folder.append(filename.c_str()));
		outfile << numPart << " " << totalPoints[i]+ghosts[i].size() << " "<< totalPoints[i] << " " << ghosts[i].size() << endl;
	}

        // local nodes
        for(int i = 0; i < nvtxs; i++){
		int partnId = part[i];
		string filename = getfileName(partnId, nParts);
		fstream write;
		string folder = "point/";
		write.open(folder.append(filename.c_str()), fstream::app);
		write << fixed;
		write << ptVec[i].id  << setprecision(20) << " " << ptVec[i].x << " " << ptVec[i].y 
			<< " " << inputToLoc[partnId][ptVec[i].left] << " " << inputToLoc[partnId][ptVec[i].right]
			<< " " << ptVec[i].flag1 << " " << ptVec[i].flag2 << " " << ptVec[i].nx << " "
			<< ptVec[i].ny << " " << ptVec[i].qtdepth << " " << ptVec[i].min_dist << " ";
		write << xadjVec[i+1]-xadjVec[i] << " ";
		for(idx_t j=xadjVec[i]; j<xadjVec[i+1]; j++){
			write << inputToLoc[partnId][adjncyVec[j]+1] << " ";
		}          
		currGlobalNum[partnId]++;   
		write << endl;
		write.close(); 
	}

        // ghost nodes
        for(int i=0; i < nParts; i++) {
		string filename = getfileName(i, nParts);
		fstream write;
		string folder = "point/";
		write.open(folder.append(filename.c_str()), fstream::app);
		set<int>::iterator itr;
		write << fixed << setprecision(20);
		for(itr = ghosts[i].begin(); itr!=ghosts[i].end(); itr++){
			write << inputToGlob[*itr] << "  " << ptVec[*itr].x << " " << ptVec[*itr].y << " " << ptVec[*itr].min_dist << "  ";
			write << endl;
		}
		write.close(); 
	}
}

void Graph::write_output_quad_regent(int numPart){
	
	/*  writing output routine  */
        // create files and write basic info
	for(int i=0; i<nParts; i++){
		string filename = getfileName(i, nParts);
		string folder = "point/";
		ofstream outfile (folder.append(filename.c_str()));
		outfile << numPart << " " << totalPoints[i]+ghosts[i].size() << " "<< totalPoints[i] << " " << ghosts[i].size() << endl;
	}

        // local nodes
        for(int i = 0; i < nvtxs; i++){
		int partnId = part[i];
		string filename = getfileName(partnId, nParts);
		fstream write;
		string folder = "point/";
		write.open(folder.append(filename.c_str()), fstream::app);
		write << fixed;
		write << ptVec[i].id  << setprecision(20) << " " << ptVec[i].x << " " << ptVec[i].y 
			<< " " << ptVec[i].left << " " << ptVec[i].right
			<< " " << ptVec[i].flag1 << " " << ptVec[i].flag2 << " " << ptVec[i].nx << " "
			<< ptVec[i].ny << " " << ptVec[i].qtdepth << " " << ptVec[i].min_dist << " ";
		write << xadjVec[i+1]-xadjVec[i] << " ";
		for(idx_t j=xadjVec[i]; j<xadjVec[i+1]; j++){
			write << adjncyVec[j]+1 << " ";
		}          
		currGlobalNum[partnId]++;   
		write << endl;
		write.close(); 
	}

        // ghost nodes
        for(int i=0; i < nParts; i++) {
		string filename = getfileName(i, nParts);
		fstream write;
		string folder = "point/";
		write.open(folder.append(filename.c_str()), fstream::app);
		set<int>::iterator itr;
		write << fixed << setprecision(20);
		for(itr = ghosts[i].begin(); itr!=ghosts[i].end(); itr++){
			write << inputToGlob[*itr] << "  " << ptVec[*itr].x << " " << ptVec[*itr].y << " " << ptVec[*itr].min_dist << "  ";
			write << endl;
		}
		write.close(); 
	}
}

void Graph::write_output_hdf5(int numPart){
	H5File file("point/point.h5", H5F_ACC_TRUNC);
	for(int i=0; i < nParts; i++){
		Group group(file.createGroup("/" + to_string(i + 1)));
		Group group2(file.createGroup("/" + to_string(i + 1) + "/local"));
		Group group3(file.createGroup("/" + to_string(i + 1) + "/ghost"));

		hsize_t dims[1] = {1};
		DataSpace attr_dataspace = DataSpace (1, dims);
		Attribute attribute_total = group.createAttribute("total", PredType::NATIVE_INT, attr_dataspace);
		Attribute attribute_local = group.createAttribute("local", PredType::NATIVE_INT, attr_dataspace);
		Attribute attribute_ghost = group.createAttribute("ghost", PredType::NATIVE_INT, attr_dataspace);
		int temp[1] = {0};
		temp[0] = totalPoints[i]+ghosts[i].size();
		attribute_total.write(PredType::NATIVE_INT, temp);
		temp[0] = totalPoints[i];
		attribute_local.write(PredType::NATIVE_INT, temp);
		temp[0] = ghosts[i].size();
		attribute_ghost.write(PredType::NATIVE_INT, temp);
	}

	for(int i = 0; i < nvtxs; i++){
		hsize_t dims[1] = { 0 };
		dims[0] = xadjVec[i+1]-xadjVec[i];
		int conn[dims[0]] = {0};
		int k = 0;
		for(idx_t j=xadjVec[i]; j<xadjVec[i+1]; j++){
			conn[k] = inputToLoc[part[i]][adjncyVec[j]+1];
			k++;
		}  
		DataSpace *dataspace = new DataSpace(1, dims);
		DataSet *dataset = new DataSet(file.createDataSet("/" + to_string(part[i] + 1) + "/local/" + to_string(ptVec[i].id), PredType::NATIVE_INT, *dataspace));
		dataset->write(conn, PredType::NATIVE_INT);

		hsize_t dims_attr[1] = { 1 };
		double temp[dims_attr[0]] = {ptVec[i].x};
		DataSpace attr_dataspace = DataSpace(1, dims_attr);

		Attribute *attr_x = new Attribute(dataset->createAttribute("x", PredType::NATIVE_DOUBLE, attr_dataspace));
		attr_x->write(PredType::NATIVE_DOUBLE, temp);
		delete attr_x;

		Attribute *attr_y = new Attribute(dataset->createAttribute("y", PredType::NATIVE_DOUBLE, attr_dataspace));
		temp[0] = ptVec[i].y;
		attr_y->write(PredType::NATIVE_DOUBLE, temp);
		delete attr_y;

		Attribute *attr_nx = new Attribute(dataset->createAttribute("nx", PredType::NATIVE_DOUBLE, attr_dataspace));
		temp[0] = ptVec[i].nx;
		attr_nx->write(PredType::NATIVE_DOUBLE, temp);
		delete attr_nx;

		Attribute *attr_ny = new Attribute(dataset->createAttribute("ny", PredType::NATIVE_DOUBLE, attr_dataspace));
		temp[0] = ptVec[i].ny;
		attr_ny->write(PredType::NATIVE_DOUBLE, temp);
		delete attr_ny;

		Attribute *attr_min_dist = new Attribute(dataset->createAttribute("min_dist", PredType::NATIVE_DOUBLE, attr_dataspace));
		temp[0] = ptVec[i].min_dist;
		attr_min_dist->write(PredType::NATIVE_DOUBLE, temp);
		delete attr_min_dist;

		int temp2[dims_attr[0]] = {inputToLoc[part[i]][ptVec[i].left]};
		Attribute *attr_left = new Attribute(dataset->createAttribute("left", PredType::NATIVE_INT, attr_dataspace));
		attr_left->write(PredType::NATIVE_INT, temp2);
		delete attr_left;

		Attribute *attr_right = new Attribute(dataset->createAttribute("right", PredType::NATIVE_INT, attr_dataspace));
		temp2[0] = inputToLoc[part[i]][ptVec[i].right];
		attr_right->write(PredType::NATIVE_INT, temp2);
		delete attr_right;

		Attribute *attr_qtdepth = new Attribute(dataset->createAttribute("qtdepth", PredType::NATIVE_INT, attr_dataspace));
		if (format == 2){
			temp2[0] = 0;
		}
		else{
			temp2[0] = ptVec[i].qtdepth;
		}
		attr_qtdepth->write(PredType::NATIVE_INT, temp2);
		delete attr_qtdepth;

		Attribute *attr_flag1 = new Attribute(dataset->createAttribute("flag1", PredType::NATIVE_INT, attr_dataspace));
		temp2[0] = ptVec[i].flag1;
		attr_flag1->write(PredType::NATIVE_INT, temp2);
		delete attr_flag1;

		Attribute *attr_flag2 = new Attribute(dataset->createAttribute("flag2", PredType::NATIVE_INT, attr_dataspace));
		temp2[0] = ptVec[i].flag2;
		attr_flag2->write(PredType::NATIVE_INT, temp2);
		delete attr_flag2;

		Attribute *attr_nbhs_count = new Attribute(dataset->createAttribute("nbhs_count", PredType::NATIVE_INT, attr_dataspace));
		temp2[0] = xadjVec[i+1]-xadjVec[i];
		attr_nbhs_count->write(PredType::NATIVE_INT, temp2);
		delete attr_nbhs_count;
	}

	for(int i=0; i < nParts; i++) {
		set<int>::iterator itr;
		for(itr = ghosts[i].begin(); itr!=ghosts[i].end(); itr++){


		hsize_t dims[1] = { 0 };
		dims[0] = 1;
		int data[] = {inputToGlob[*itr]};
		DataSpace *dataspace = new DataSpace(1, dims);
		DataSet *dataset = new DataSet(file.createDataSet("/" + to_string(part[i] + 1) + "/ghost/" + to_string(data[0]), PredType::NATIVE_INT, *dataspace));
		dataset->write(data, PredType::NATIVE_INT);

		double temp[] = {ptVec[*itr].x};
		Attribute *attr_x = new Attribute(dataset->createAttribute("x", PredType::NATIVE_DOUBLE, *dataspace));
		attr_x->write(PredType::NATIVE_DOUBLE, temp);
		delete attr_x;

		temp[0] = ptVec[*itr].y;
		Attribute *attr_y = new Attribute(dataset->createAttribute("y", PredType::NATIVE_DOUBLE, *dataspace));
		attr_y->write(PredType::NATIVE_DOUBLE, temp);
		delete attr_y;

		Attribute *attr_min_dist = new Attribute(dataset->createAttribute("min_dist", PredType::NATIVE_DOUBLE, *dataspace));
		temp[0] = ptVec[*itr].min_dist;
		attr_min_dist->write(PredType::NATIVE_DOUBLE, temp);
		delete attr_min_dist;
		}
	}
}
