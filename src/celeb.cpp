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


vector<Mat> getXTest(){
	vector<Mat> xTest;
	Mat image;

	for (int i = 1; i <= 5; i++){
		image = imread("../data/celeb/im" + to_string(i) + "f.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		image.convertTo(image, CV_32F, 1.0/255);
		xTest.push_back(image);
		image = imread("../data/celeb/im" + to_string(i) + "m.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		image.convertTo(image, CV_32F, 1.0/255);
		xTest.push_back(image);
	}
	return xTest;
}


vector<Mat> getXfromIndex(vector<int> predictedIndex, dataTrainTest inputData){
	vector<Mat> predicted_X;
	for (unsigned int i = 0; i < predictedIndex.size(); i++)
		predicted_X.push_back(inputData.xTrain[predictedIndex[i]]);
	return predicted_X;
}



int main(int argc, char *argv[]){
	std::srand(unsigned(time(0)));


	dataset myDataset = readData("orl_faces");
	sample mySample;
	mySample.inputData.xTrain = myDataset.x;
	mySample.inputData.yTrain = myDataset.y;
	mySample.inputData.xTest = getXTest();


	vector<int> predictedIndex = eigenFaces(mySample.inputData, 0.85, true);
	vector<Mat> predicted_X = getXfromIndex(predictedIndex, mySample.inputData);

	Mat both;
	for (unsigned int i = 0; i < predicted_X.size(); i++){
		both = mySample.inputData.xTest[i];
		hconcat(both, predicted_X[i], both);
		showImg(both);
	}

	return 0;
}