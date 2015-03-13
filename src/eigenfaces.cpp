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

#include <algorithm>
#include <map>

using namespace std;
using namespace cv;


int 
myRandomFn (int i){
	return rand() % i;
}



sample 
sampleData(dataset myDataset){
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



dataset 
readData(string datasetName){
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



void 
showImg(Mat image){
	   	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	    imshow("MyWindow", image); //display the image which is stored in the 'image' in the "MyWindow" window

	    waitKey(0); //wait infinite time for a keypress

	    destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
}



void 
printMat(Mat image){
	for (int i = 0; i < image.rows; i++){
		for (int j = 0; j < image.cols; j++)
			cout << image.at<float>(i, j) << " ";
		cout << "\n";
	}
}



unsigned int 
calculateEnergyCutoff(Mat sigma, float desiredEnergy)
{
	float totalEnergy = 0;
	float energy = 0;

	for (int i = 0; i < sigma.rows; i++)
	{
		totalEnergy += sigma.at<float>(i, 0);
	}

	for (int i = 0; i < sigma.rows; i++)
	{
		energy += sigma.at<float>(i, 0);
		if ((energy / totalEnergy) > desiredEnergy)
		{
			return i;
		}
	}

	perror("Could not calculate energy cutoff\n");
	exit(EXIT_FAILURE);
}




Mat 
getLfromMatVector(vector<Mat> x){
	Mat L, avgL, image, avgImage;
	int no_rows, no_cols;

	image = x[0];
	no_rows = image.rows;
	no_cols = image.cols;

	L = image.reshape(1, no_rows * no_cols);

	for (unsigned int i = 1; i < x.size(); i++){
		image = x[i];
		image = image.reshape(0, no_rows * no_cols);
		hconcat(L, image, L);
	}

	reduce(L.t(), avgImage, 0, CV_REDUCE_SUM, CV_32F);
	avgImage = avgImage.t() / x.size();

	avgL = avgImage;
	for (unsigned int i = 1; i < x.size(); i++){
		hconcat(avgL, avgImage, avgL);
	}
	L = L - avgL;
	return L;
}



double 
getScore(Mat u1, Mat u2)
{
	Mat u3 = u1 - u2;
	return u3.dot(u3); // compute norm 
}



int 
findBestMatch(Mat W, Mat Wtest)
{
	double bestScore = getScore(W.col(0), Wtest);
	int bestMatch = 0;

	for (int i = 1; i < W.cols; i ++)
	{
		double score = getScore(W.col(i), Wtest);
		if (score < bestScore)
		{
			bestMatch = i;
			bestScore = score;
		}
	}

	return bestMatch;
}



float 
computeAccuracy(vector<string> &true_Y, vector<string> &predicted_Y){
	int matches = 0;

	for (unsigned int i = 0; i < true_Y.size(); i++)
	{
		if (true_Y[i] == predicted_Y[i]){
			matches++;
		}
	}
	return float(matches) / float(true_Y.size());
}



svd_return 
svd_processing(dataTrainTest inputData)
{
	Mat L_training = getLfromMatVector(inputData.xTrain);
	Mat S, U, Vt;
	SVD::compute(L_training, S, U, Vt);

	svd_return ret;
	ret.S = S;
	ret.U = U;
	ret.L_training = L_training;
	return ret;
}



vector<int> 
eigenFaces(dataTrainTest inputData, float energy, bool useFirstEigenface){
	vector<int> predictedIndex;
	Mat L_training, W_training, L_testing, W_testing;
	int k;
		
	L_training = getLfromMatVector(inputData.xTrain);

	// Apply SVD 
	Mat S, U, Vt;
	SVD::compute(L_training, S, U, Vt);

	// Reduce U
	k = calculateEnergyCutoff(S, energy);
	if (useFirstEigenface)
		U = U.colRange(0, k);
	else
		U = U.colRange(1, k);

	W_training = U.t() * L_training;

	L_testing = getLfromMatVector(inputData.xTest);
	W_testing = U.t() * L_testing;

	for (int i = 0; i < W_testing.cols; i++)
	{
		int bestMatch = findBestMatch(W_training, W_testing.col(i));
		predictedIndex.push_back(bestMatch);
	}

	return predictedIndex;
}



vector<string> 
getYfromIndex(vector<int> predictedIndex, dataTrainTest inputData){
	vector<string> predicted_Y;
	for (unsigned int i = 0; i < predictedIndex.size(); i++)
		predicted_Y.push_back(inputData.yTrain[predictedIndex[i]]);
	return predicted_Y;
}



bool 
Special_map::compare (Special_map &a, Special_map &b) 
{ 
	return ( a.score < b.score); 
}



vector <int> 
findBestMatches(Mat W, Mat Wtest)
{
	vector<Special_map> scores;
	for (int i = 1; i < W.cols; i ++)
	{
		scores[i] = Special_map(i, getScore(W.col(i), Wtest));
	}

	partial_sort (scores.begin(), scores.begin() + 5, scores.end(), Special_map::compare);

	vector<int> bestMatches;
	for (int i = 1; i < 5; i++)
	{
		bestMatches.push_back(scores[i].index);
	}

	return bestMatches;
}



vector<vector<int>> 
eigenFaces_firstfive(dataTrainTest inputData, float energy, bool useFirstEigenface){
	vector<vector<int>> predictedIndexes;
	Mat L_training, W_training, L_testing, W_testing;
	int k;
		
	L_training = getLfromMatVector(inputData.xTrain);

	// Apply SVD 
	Mat S, U, Vt;
	SVD::compute(L_training, S, U, Vt);

	// Reduce U
	k = calculateEnergyCutoff(S, energy);
	if (useFirstEigenface)
		U = U.colRange(0, k);
	else
		U = U.colRange(1, k);

	W_training = U.t() * L_training;

	L_testing = getLfromMatVector(inputData.xTest);
	W_testing = U.t() * L_testing;

	for (int i = 0; i < W_testing.cols; i++)
	{
		vector<int> bestMatches = findBestMatches(W_training, W_testing.col(i));
		predictedIndexes.push_back(bestMatches);
	}

	return predictedIndexes;
}