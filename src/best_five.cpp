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

const string image_file_name = "../data/orl_faces/s1/1.pgm";
const string output_file_name = "../data/celeb_accuracy_scores";

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
 * Saves the accuracy scores to a file.
 * 
 * @param outputFile       the name of the file used for storage
 * @param  predictedIndex a vector with indexes of images
 * @param  inputData      an inputData structure containing all the labels
 */
void 
saveDataToFile (
	string outputFile,
	vector<vector<Special_map>> predictedIndexes, 
	dataTrainTest inputData)
{
	ofstream fout;
 	fout.open (outputFile);
 	fout << "Accuracy scores\n\n";
 	const string gender[] = {"f","m"};

 	for (unsigned int celebImg = 0; celebImg < predictedIndexes.size(); celebImg ++)
 	{
 		// Write picture header
 		fout << "File: data\\celeb\\im" << (celebImg % 5 + 1);
 		fout << gender[celebImg < 5] << ".jpg\n";
 		fout << "\t\tRank\tPerson\tAccuracy\n";

 		for (int predictedIndex = 0; predictedIndex < 5; predictedIndex ++)
 		{
 			fout << "\t\t" << predictedIndex + 1 <<"\t";
 			fout << inputData.yTrain[predictedIndexes[celebImg][predictedIndex].index] << "\t";
 			fout << predictedIndexes[celebImg][predictedIndex].score << "\n\n";
 		}
 	}


 	fout.close();
}

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
	vector<vector<Special_map>> predictedAccuracies = eigenFaces_firstfive(mySample.inputData, 0.85, true);
	vector<vector<int>> predictedIndexes = changeFormat(predictedAccuracies);
	vector<vector<Mat>> predicted_X;

	for (int image = 0; image < 5; image ++)
	{
		vector<Mat> predicted_X_number = getXfromIndex(predictedIndexes[image], mySample.inputData);
		predicted_X.push_back(predicted_X_number);
	}


	saveDataToFile(output_file_name, predictedAccuracies, mySample.inputData);

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
