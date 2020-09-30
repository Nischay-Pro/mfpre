#include <iostream>
#include <fstream>

#include "point.h"
#include <H5Cpp.h>
#include "indicators.hpp"
#include <thread>
#include <chrono>

using namespace std;
using namespace H5;
using namespace indicators;

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

void Graph::write_output_hdf5(){
	FileAccPropList fapl(FileAccPropList::DEFAULT);
	int mdc_nelmts;
	size_t rdcc_nelmts;
	size_t rdcc_nbytes;
	double rdcc_w0;
	fapl.getCache(mdc_nelmts,rdcc_nelmts,rdcc_nbytes,rdcc_w0);
	// fapl.setCache(mdc_nelmts, rdcc_nelmts, 1e+8, 1);
	H5File file("point/point.h5", H5F_ACC_TRUNC, FileCreatPropList::DEFAULT, fapl);
	indicators::show_console_cursor(false);
	BlockProgressBar bar{
		option::BarWidth{80},
		option::ForegroundColor{Color::white},
		option::FontStyles{
		vector<FontStyle>{FontStyle::bold}},
		option::MaxProgress{100}
	};
	
	for(int i=0; i < nParts; i++){
		Group group(file.createGroup("/" + to_string(i + 1)));
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
	
	vector<int> locals[nParts];
	
	for(int i = 0; i < nvtxs; i++){
		locals[part[i]].push_back(i);
	}

	int pog = ceil(ptVec.size() / 100);

	int progress = 1;
	for(int i = 0; i < nParts; i++){
		auto localArray = new double[totalPoints[i]][30];
		auto ghostArray = new double[ghosts[i].size()][4];
		hsize_t dims[2];
		hsize_t chunk_dims[2] = { ceil(totalPoints[i] / 100) , 30 };

		// Local Points
		dims[0] = totalPoints[i];
		dims[1] = 30;
		int ptidx = 0;
		for(auto itr: locals[i]){
			auto point = ptVec[itr];
			auto nbhs = xadjVec[itr+1]-xadjVec[itr];
			localArray[ptidx][0] = itr;
			localArray[ptidx][1] = point.x;
			localArray[ptidx][2] = point.y;
			localArray[ptidx][3] = point.nx;
			localArray[ptidx][4] = point.ny;
			localArray[ptidx][5] = point.min_dist;

			localArray[ptidx][6] = point.left;
			localArray[ptidx][7] = point.right;
			int qtdepth = 0;
			if (format == 2){
				qtdepth = 0;
			}
			else{
				qtdepth = point.qtdepth;
			}
			localArray[ptidx][8] = qtdepth;
			localArray[ptidx][9] = point.flag1;
			localArray[ptidx][10] = point.flag2;
			localArray[ptidx][11] = nbhs;
			int k = 12;
			for(idx_t j=xadjVec[itr]; j<xadjVec[itr+1]; j++){
				localArray[ptidx][k] = inputToLoc[i][adjncyVec[j]+1];
				k++;
			}
			while(k < 30){
				localArray[ptidx][k] = -1;
				k++;
			}
			ptidx++;
			if(progress % pog == 0){
				bar.set_option(option::PostfixText{
					to_string(progress) + "/" + to_string(ptVec.size())
				});
				bar.tick();
			}
			progress++;
		}
		DataSpace *dataspace = new DataSpace(2, dims);
		DSetCreatPropList *plist = new DSetCreatPropList;
		plist->setChunk(2, chunk_dims);
		plist->setDeflate(6);
		DataSet *dataset = new DataSet(file.createDataSet("/" + to_string(i + 1) + "/local", PredType::NATIVE_DOUBLE, *dataspace, *plist));
		dataset->write(localArray, PredType::NATIVE_DOUBLE);
		delete plist;
		delete localArray;
		delete dataspace;
		delete dataset;

		// Ghost Points
		dims[0] = ghosts[i].size();
		dims[1] = 4;
		ptidx = 0;
		for(auto itr: ghosts[i]){
			auto point = ptVec[itr];
			ghostArray[ptidx][0] = inputToGlob[itr];
			ghostArray[ptidx][1] = point.x;
			ghostArray[ptidx][2] = point.y;
			ghostArray[ptidx][3] = point.min_dist;
			ptidx++;
		}

		DSetCreatPropList *plist2 = new DSetCreatPropList;
		chunk_dims[0] = ceil(ghosts[i].size() / 100);
		if(chunk_dims[0] == 0) chunk_dims[0]++;
		chunk_dims[1] = 4;
		plist2->setChunk(2, chunk_dims);
		plist2->setDeflate(6);
		DataSpace *dataspace2 = new DataSpace(2, dims);
		DataSet *dataset2 = new DataSet(file.createDataSet("/" + to_string(i + 1) + "/ghost", PredType::NATIVE_DOUBLE, *dataspace2, *plist2));
		dataset2->write(ghostArray, PredType::NATIVE_DOUBLE);
		delete ghostArray;
		delete plist2;
		delete dataspace2;
		delete dataset2;
	}

	bar.mark_as_completed();
	indicators::show_console_cursor(true);
}
