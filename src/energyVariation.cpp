/**
 * 	Project 1
 * 	Authors: Alina Dima & Mihai Fieraru
 * 	
 * 	energyVariation.cpp
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

const string outputFileName = "../data/output.csv";

void writeOutput();

int main()
{
	std::srand ( unsigned ( time(0) ) );

	dataset myDataset = readData("orl_faces");

	sample mySample = sampleData(myDataset);

	svd_return svd_result = svd_processing(mySample.inputData);


	return 0;
}

void writeOutput ()
{
	ofstream outputFile;
 	outputFile.open (outputFileName);

 	/**
 	 * 
 	 */


 	outputFile << "Saving data to " << outputFileName << endl;
 	outputFile.close();
}

