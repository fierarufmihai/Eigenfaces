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

/**
 * Used to transmit information needed for training, after 
 * the partition between train and test data has been made;
 *
 * xTrain	train images
 * yTrain	labels corresponding to train images
 * xTest 	test images (stored in the same data structure 
 * 			because it is needed to compute Wtest matrix
 * 			during eigenvectors algorithm)
 */
struct dataTrainTest{
	std::vector<cv::Mat> xTrain;
	std::vector<std::string> yTrain;
	std::vector<cv::Mat> xTest;
};


/**
 * Used to store newly-read information, before partitioning
 * it into train and test data.
 *
 * x 			images
 * y 			labels corresponding to images (denoting the person in the picture)
 * noCategories the number of persons in the data set
 */
struct dataset{
	std::vector<cv::Mat> x;
	std::vector<std::string> y;
	int noCategories;
};


/**
 * Full-scope data after partition into train and test.
 *
 * inputData	train set used for eigenfaces algorithm
 * outputData 	true labels of the test set used to compute the accuracy
 */
struct sample{
	dataTrainTest inputData;
	std::vector<std::string> outputData;
};


/**
 * Used to store the data obtained after applying the svd procedure, needed
 * to run more than one test case.
 *
 * L_training	centered set of images not yet converted to base U^t
 * U 			U matrix from svd needed for basis conversion
 * S 			Sigma matrix from svd needed to compute energy cutoff
 */
struct svd_return{
	cv::Mat L_training;
	cv::Mat U;
	cv::Mat S;
};


/**
 * Map of indexes and corresponding accuracy scores,
 * needed in order to apply std::partial_sort algoritm.  
 *
 * score 	wanted for storing
 * index 	wanted to identify the matching image for display
 */
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
 * Generates a random number using rand().
 * 
 * @param  i 	sets the upper bound
 * @return   	a random number up to i-1
 */
int myRandomFn (int i);



/**
 * Partitions the dataset into train and test images.
 * 
 * @param  myDataset raw data set
 * @return           a random sample of the data
 */
sample sampleData(dataset myDataset);



/**
 * Reads all images in a folder (can be in subfolders).
 * 
 * @param  datasetName 	path to the directory of the data
 * @return             	the data read
 */
dataset readData(std::string datasetName);



/**
 * Displays an image on the screen (in a separate window).
 * 
 * @param image 
 */
void showImg(cv::Mat image);



/**
 * Prints a matrix on the standard output.
 * 
 * @param image 
 */
void printMat(cv::Mat image);



/**
 * Performs eigenfaces algorithm.
 * 
 * @param  inputData         the data set used for training
 * @param  energy            specifies the percentage of energy retained
 * @param  useFirstEigenface specifies whether the first eigenface is used
 * @return                   the train image number of the best match for each test image
 */
std::vector<int> eigenFaces(dataTrainTest inputData, float energy, bool useFirstEigenface);



/**
 * Converts a vector of image indexes into a vector of image labels 
 * corresponding to the indexes.
 * 
 * @param predictedIndex a vector of indexes
 * @param inputData      the dataTrainTest containing the labels
 */
std::vector<std::string> getYfromIndex(std::vector<int> predictedIndex, dataTrainTest inputData);



/**
 * Computes the energy cutoff index for the reduction in eigenvectors of the
 * orthogonal matrix U.
 * 
 * @param  sigma 		Sigma matrix outputed by svd algorithm.
 * @param desiredEnergy	maximum energy percentage allowed
 * @return       		The number of eigenvectors to be retained
 */
unsigned int calculateEnergyCutoff(cv::Mat sigma, float desiredEnergy);



/**
 * Returns the training set image index that is closest to the test image.
 * 
 * @param  W     training set in basis U^t
 * @param  Wtest test set in basis U^t
 * @return       best match index
 */
int findBestMatch(cv::Mat W, cv::Mat Wtest);



/**
 * Computes the overall accuracy of the algorithm.
 * 
 * @param  true_Y      true labels of pictures
 * @param  predicted_Y algorithm-predicted lables 
 * @return             accuracy in single precision
 */
float computeAccuracy(std::vector<std::string> &true_Y, std::vector<std::string> &predicted_Y);



/**
 * Performs the svd decomposition and outputs the matrices further required
 * to vary the accuracy under the same conditions, without the need to 
 * redo calculations.
 *
 * @param  inputData training set
 * @return           L_training, Sigma, and U
 */
svd_return svd_processing(dataTrainTest inputData);



/**
 * Stitches centered training images to form L.
 * 
 * @param  x training images
 * @return   L matrix
 */
cv::Mat getLfromMatVector(std::vector<cv::Mat> x);



/**
 * Returns the best five training set image indexes that are closest to the test image.
 * Similar to findBestMatch
 * 
 * @param  W     training set in basis U^t
 * @param  Wtest test set in basis U^t
 * @return       five best match indexes
 */
std::vector <Special_map> findBestMatches(cv::Mat W, cv::Mat Wtest);



/**
 * Converts a matrix of Special_map to one of integers, thus
 * reducing the redundant accuracy information, which
 * is not needed when displaying images on the screen.
 * 
 * @param  predictedIndexes_raw 	matrix of Special_map ouputed by eigenFaces_firstfive function
 * @return                      	reduced matrix
 */
std::vector<std::vector<int>> changeFormat(std::vector<std::vector<Special_map>> predictedIndexes_raw);



/**
 * Performs eigenfaces algorithm, in the case where five values need to be outputed.
 * 
 * @param  inputData         the data set used for training
 * @param  energy            specifies the percentage of energy retained
 * @param  useFirstEigenface specifies whether the first eigenface is used
 * @return                   best five pairs with training image numbers and accuracy for each image
 */
std::vector<std::vector<Special_map>> eigenFaces_firstfive(dataTrainTest inputData, float energy, bool useFirstEigenface);

#endif