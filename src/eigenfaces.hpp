/**
 * 	Project 1
 * 	Authors: Alina Dima & Mihai Fieraru
 * 	
 * 	eigenfaces.hpp
 */


#ifndef __EIGENFACES_H__
#define __EIGENFACES_H__


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <iostream>
#include <vector>

/**************************************************
 *               Constants 
 **************************************************
 */
const int BUFFER_LENGTH = 1024;



/**************************************************
 *               Data Structures 
 **************************************************
 */

struct dataTrainTest{
	std::vector<cv::Mat> xTrain;
	std::vector<std::string> yTrain;
	std::vector<cv::Mat> xTest;
};


struct dataset{
	std::vector<cv::Mat> x;
	std::vector<std::string> y;
	int noCategories;
};


struct sample{
	dataTrainTest inputData;
	std::vector<std::string> outputData;
};



/**************************************************
 *               Functions
 **************************************************
 */


/**
 * Generates a random number using rand()
 * @param  i 	sets the upper bound
 * @return   	a random number up to i-1
 */
int myRandomFn (int i);


/**
 * [sampleData description]
 * @param  myDataset [description]
 * @return           [description]
 */
sample sampleData(dataset myDataset);


/**
 * Reads all images in a folder (can be in subfolders)
 * @param  datasetName 	path to the directory of the data
 * @return             	the data read
 */
dataset readData(std::string datasetName);


/**
 * Displays an image on the screen (in a separate window).
 * @param image 
 */
void showImg(cv::Mat image);


/**
 * Prints a matrix on the standard output
 * @param image 
 */
void printMat(cv::Mat image);


/**
 * 
 */
std::vector<int> eigenFaces(dataTrainTest inputData, float energy, bool useFirstEigenface);




unsigned int calculateEnergyCutoff(cv::Mat sigma);

#endif