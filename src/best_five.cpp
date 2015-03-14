/**
 * 	Project 1
 * 	Authors: Alina Dima & Mihai Fieraru
 * 	
 * 	best_five.cpp
 *
 * Displays the five closest images to the given celebrity face, from closest to farthest.
 * 
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


/**
 * Reads the celebrity images in the folder. 
 * The image names are hardcoded.
 * @return a vector containing the images read 
 */
vector<Mat>
getXTest()
{
	vector<Mat> xTest;
	Mat image;

	for (int i = 1; i <= 5; i++)
	{
		image = imread("../data/celeb/im" + to_string(i) + "f.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		image.convertTo(image, CV_32F, 1.0/255);
		xTest.push_back(image);
		image = imread("../data/celeb/im" + to_string(i) + "m.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		image.convertTo(image, CV_32F, 1.0/255);
		xTest.push_back(image);
	}
	return xTest;
}


/**
 * Retrieves the images corresponding to the indexes.
 * The function is called after the distance coefficients
 * between images have been calculated and their corresponding 
 * indexes, in order to display them.
 * 
 * @param  predictedIndex a vector with indexes of images
 * @param  inputData      an inputData structure containing all the labels
 * @return                a vector with the corresponding images (as Mat)
 */
vector<Mat> 
getXfromIndex(
	vector<int> predictedIndex, 
	dataTrainTest inputData)
{
	vector<Mat> predicted_X;
	for (unsigned int i = 0; i < predictedIndex.size(); i++)
	{
		predicted_X.push_back(inputData.xTrain[predictedIndex[i]]);
	}
	return predicted_X;
}


/**
 * Saves the accuracy scores to a file
 * 
 * @param fileName       the name of the file used for storage
 * @param  predictedIndex a vector with indexes of images
 * @param  inputData      an inputData structure containing all the labels
 */
// void 
// saveDataToFile (
// 	string fileName,
// 	vector<int> predictedIndexes, 
// 	dataTrainTest inputData)
// {
// 
// }

int 
main(
	int argc, 
	char *argv[])
{
	std::srand(unsigned(time(0)));

	// Read and store data
	dataset myDataset = readData("orl_faces");
	sample mySample;
	mySample.inputData.xTrain = myDataset.x;
	mySample.inputData.yTrain = myDataset.y;
	mySample.inputData.xTest = getXTest();


	// Apply eignenfaces algorithm and compute accuracy scores
	vector<vector<int>> predictedIndexes = eigenFaces_firstfive(mySample.inputData, 0.85, true);
	vector<vector<Mat>> predicted_X;

	for (int image = 0; image < 5; image ++)
	{
		vector<Mat> predicted_X_number = getXfromIndex(predictedIndexes[image], mySample.inputData);
		predicted_X.push_back(predicted_X_number);
	}


	// Display results
	Mat all_together;
	for (unsigned int image = 0; image < predicted_X.size(); image++)
	{
		all_together = mySample.inputData.xTest[image];
		for (int match_number = 0; match_number < 5; match_number++)
		{
			hconcat(all_together, predicted_X[image][match_number], all_together);
		}
		showImg(all_together);
	}

	return 0;
}
