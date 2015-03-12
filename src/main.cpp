/**
 * 	Project 1
 * 	Authors: Alina Dima & Mihai Fieraru
 * 	
 * 	main.cpp
 */


#include "eigenfaces.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <dirent.h>


using namespace std;
using namespace cv;

string image_file_name = "../data/orl_faces/s1/1.pgm";

int main(int argc, char *argv[]){
	std::srand ( unsigned ( time(0) ) );

	dataset myDataset = readData("orl_faces");

	sample mySample = sampleData(myDataset);
	
	vector<int> predictedIndex = eigenFaces(mySample.inputData, 0.85, true);
	
	vector<string> predicted_Y = getYfromIndex(predictedIndex, mySample.inputData);
	
	vector<string> true_Y = mySample.outputData;
	
	cout << computeAccuracy(true_Y, predicted_Y) << endl;


	return 0;
}