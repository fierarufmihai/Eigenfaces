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

int main(){
	std::srand ( unsigned ( time(0) ) );


	// // showImg(image);

	// Mat S, U, Vt;
	// SVD::compute(image, S, U, Vt);


	// cout << S.rows << " " << S.cols << "\n";
	// cout << U.rows << " " << U.cols << "\n";
	// cout << Vt.rows << " " << Vt.cols << "\n";

	// printMat(S);




	// Test readData()

	dataset myDataset = readData("orl_faces");
	// showImg(data.x[0]);
	// cout << data.y[0] << "\n";
	// showImg(data.x[12]);
	// cout << data.y[12] << "\n";
	// cout << data.noCategories << "\n";
	// cout << data.y.size() << "\n";


	// Test sampleData()

	sample mySample = sampleData(myDataset);
	// showImg(mySample.inputData.xTrain[0]);
	// cout << mySample.inputData.yTrain[0] << "\n";

	// showImg(mySample.inputData.xTrain[1]);
	// cout << mySample.inputData.yTrain[1] << "\n";

	// showImg(mySample.inputData.xTrain[6]);
	// cout << mySample.inputData.yTrain[6] << "\n";


	vector<string> predicted_Y = eigenFaces(mySample.inputData, 0.85, true);
	vector<string> true_Y = mySample.outputData;

	// for (unsigned int i = 0; i < predicted_Y.size(); i++){
	// 	cout << predicted_Y[i] << " " << true_Y[i] << "\n";
	// }


	cout << computeAccuracy(true_Y, predicted_Y) << endl;


	return 0;
}