/**
 * 	Project 1
 * 	Authors: Alina Dima & Mihai Fieraru
 * 	
 * 	eigenfaces.cpp
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


int myRandomFn (int i){
	return rand() % i;
}


sample sampleData(dataset myDataset){
	sample mySample;
	vector<int> myVector;
	for (int categ = 0; categ < 40; categ++){
		for (int i = 0; i < 10; i++) 
			myVector.push_back(i);
		std::random_shuffle (myVector.begin(), myVector.end(), myRandomFn);
		for (int i = 0; i < 6; i++){
			mySample.inputData.xTrain.push_back(myDataset.x[categ * 10 + myVector[i]]);
			mySample.inputData.yTrain.push_back(myDataset.y[categ * 10 + myVector[i]]);
		}
		for (int i = 6; i < 10; i++){
			mySample.inputData.xTest.push_back(myDataset.x[categ * 10 + myVector[i]]);
			mySample.outputData.push_back(myDataset.y[categ * 10 + myVector[i]]);
		}
		myVector.clear();
	}
	return mySample;
}


dataset readData(string datasetName){
	dataset data;	
	DIR *dirDataset;
	struct dirent *entCategory;
	DIR *dirCategory;
	struct dirent *entImage;
	string yLabel;
	string imageName;
	int noCategories = 0;
	

	// Build path to dataset directory
	string dirPathStr = "../data/" + datasetName;
	char dirPath[BUFFER_LENGTH];
	strncpy(dirPath, dirPathStr.c_str(), sizeof(dirPath));
	dirPath[sizeof(dirPath) - 1] = 0;
		
	// Read categories
	if ((dirDataset = opendir(dirPath)) != NULL){
		while ((entCategory = readdir(dirDataset)) != NULL){
			if ((strcmp(entCategory->d_name, ".") != 0) && (strcmp(entCategory->d_name, "..") != 0) && (strcmp(entCategory->d_name, "README") != 0)){
				noCategories++;
				yLabel = entCategory->d_name;

				// Build path to catergory directory
				string catPathStr = dirPathStr + "/" + yLabel;
				char catPath[BUFFER_LENGTH];
				strncpy(catPath, catPathStr.c_str(), sizeof(catPath));
				catPath[sizeof(catPath) - 1] = 0;

				// Read images in the category
				if ((dirCategory = opendir(catPath)) != NULL){
					while ((entImage = readdir(dirCategory)) != NULL){
						if ((strcmp(entImage->d_name, ".") != 0) && (strcmp(entImage->d_name, "..") != 0) && (strcmp(entImage->d_name, "README") != 0)){
							imageName = entImage->d_name;
							string imagePathStr = catPathStr + "/" + imageName;
							Mat image = imread(imagePathStr, CV_LOAD_IMAGE_GRAYSCALE);
							image.convertTo(image, CV_32F, 1.0/255);
							data.x.push_back(image);
							data.y.push_back(yLabel);
						}
					}
					closedir(dirCategory);
				} else {
					perror("Could not open category in the datasetName directory! \n");
					exit(EXIT_FAILURE);
				}


			}
		} 
		closedir(dirDataset);
	} else {
		perror("Could not open datasetName in the /data/ directory! \n");
		exit(EXIT_FAILURE);
	}

	data.noCategories = noCategories;

	return data;
}


void showImg(Mat image){
	   	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	    imshow("MyWindow", image); //display the image which is stored in the 'image' in the "MyWindow" window

	    waitKey(0); //wait infinite time for a keypress

	    destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
}


void printMat(Mat image){
	for (int i = 0; i < image.rows; i++){
		for (int j = 0; j < image.cols; j++)
			cout << image.at<float>(i, j) << " ";
		cout << "\n";
	}
}


vector<int> eigenFaces(dataTrainTest inputData, float energy, bool useFirstEigenface){
	vector<int> yTest;
	Mat L, avgL, image, avgImage;
	int no_rows, no_cols;
		
	image = inputData.xTrain[0];
	no_rows = image.rows;
	no_cols = image.cols;

	L = image.reshape(1, no_rows * no_cols);

	for (int i = 1; i < inputData.xTrain.size(); i++){
		image = inputData.xTrain[i];
		image = image.reshape(0, no_rows * no_cols);
		hconcat(L, image, L);
	}

	reduce(L.t(), avgImage, 0, CV_REDUCE_SUM, CV_32F);
	avgImage = avgImage.t() / inputData.xTrain.size();

	avgL = avgImage;
	for (int i = 1; i < inputData.xTrain.size(); i++){
		hconcat(avgL, avgImage, avgL);
	}

	cout << L.rows << " " << L.cols << "\n";
	cout << avgL.rows << " " << avgL.cols << "\n";

	L = L - avgL;

	cout << L.col(0).rows << " " << L.col(0).cols << "\n";

	Mat i1;
	i1.copyTo(L.col(0));
	cout << i1.rows << " " << i1.cols << "\n";
	i1 = i1.reshape(0, no_rows);
	showImg(i1);



	return yTest;
}

