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

struct svd_return{
	cv::Mat L_training;
	cv::Mat U;
	cv::Mat S;
};

class Special_map{
public:
	int index;
	double score;

	Special_map(int index, double score):index(index), score(score) {}

	static bool compare (Special_map &a, Special_map &b); 
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
 * [eigenFaces description]
 * @param  inputData         [description]
 * @param  energy            [description]
 * @param  useFirstEigenface [description]
 * @return                   [description]
 */
std::vector<int> eigenFaces(dataTrainTest inputData, float energy, bool useFirstEigenface);


/**
 * [getYfromIndex description]
 * @param predictedIndex [description]
 * @param inputData      [description]
 */
std::vector<std::string> getYfromIndex(std::vector<int> predictedIndex, dataTrainTest inputData);


/**
 * [calculateEnergyCutoff description]
 * @param  sigma [description]
 * @return       [description]
 */
unsigned int calculateEnergyCutoff(cv::Mat sigma, float desiredEnergy);


/**
 * [findBestMatch description]
 * @param  W     [description]
 * @param  Wtest [description]
 * @return       [description]
 */
int findBestMatch(cv::Mat W, cv::Mat Wtest);


/**
 * [computeAccuracy description]
 * @param  true_Y      [description]
 * @param  predicted_Y [description]
 * @return             [description]
 */
float computeAccuracy(std::vector<std::string> &true_Y, std::vector<std::string> &predicted_Y);


/**
 * [svd_processing description]
 * @param  inputData [description]
 * @return           [description]
 */
svd_return svd_processing(dataTrainTest inputData);


/**
 * [getLfromMatVector description]
 * @param  x [description]
 * @return   [description]
 */
cv::Mat getLfromMatVector(std::vector<cv::Mat> x);


/**
 * 
 */
std::vector <Special_map> findBestMatches(cv::Mat W, cv::Mat Wtest);



/**
 * 
 */
std::vector<std::vector<int>> eigenFaces_firstfive(dataTrainTest inputData, float energy, bool useFirstEigenface);

#endif