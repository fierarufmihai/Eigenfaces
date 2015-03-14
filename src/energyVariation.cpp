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
const string prefix = "../data/output/output";
const string suffix = ".csv";

/**
 * Varies energy levels from 15% to 85% and saves the data in the file indicated.
 * The svd decomposition has already been made, so all images have the same partition 
 * of train/test pictures.
 * 
 * @param mySample   data sample containing labels (needed for accuracy)
 * @param L_training Precomputed image set
 * @param U          Precomputed svd U
 * @param S          Precomputed svd Sigma
 * @param outputFile 
 */
void 
runAccuracyTest(
	sample & mySample, 
	Mat L_training, 
	Mat U, 
	Mat S, 
	string outputFile)
{
	// Create a vector of energy values
	vector<float> energyValues;
	{
		float val = 0.85;
		while (val > 0.1)
		{
			energyValues.push_back(val);
			val -= 0.05;
		}
	}

	Mat W_training, L_testing, W_testing;

	ofstream fout;
 	fout.open (outputFile);
 	fout << "Energy" << "\t" << "First" << "\t" << "Accuracy" << endl;

	for (unsigned int index = 0; index < energyValues.size(); index++)
	{
		for (int useFirstEigenface = 0; useFirstEigenface <= 1; useFirstEigenface++)
		{
			// Reduce U and change basis
			int k = calculateEnergyCutoff(S, energyValues[index]);
			Mat Uprime = U.colRange(1 - useFirstEigenface, k);
			W_training = Uprime.t() * L_training;

			L_testing = getLfromMatVector(mySample.inputData.xTest);
			W_testing = Uprime.t() * L_testing;

			// calulate best match for each image
			vector<int> predictedIndex;
			for (int i = 0; i < W_testing.cols; i++)
			{
				int bestMatch = findBestMatch(W_training, W_testing.col(i));
				predictedIndex.push_back(bestMatch);
			}

			vector<string> predicted_Y = getYfromIndex(predictedIndex, mySample.inputData);
			vector<string> true_Y = mySample.outputData;

			// summarize 
			fout << energyValues[index] << "\t" << std::boolalpha <<  useFirstEigenface << "\t";
			double acc = computeAccuracy(true_Y, predicted_Y);
			fout << acc << "\n";
		}
	}

	fout.close(); 	
	cout << "Data saved" << endl;
}



int 
main()
{
	std::srand ( unsigned ( time(0) ) );

	dataset myDataset = readData("orl_faces");

	sample mySample = sampleData(myDataset);
	for (int i = 1; i < 20; i++)
	{
		svd_return svd_result = svd_processing(mySample.inputData);

		string outputFile = prefix + to_string(i) + suffix;
		runAccuracyTest(mySample, svd_result.L_training, svd_result.U, svd_result.S, outputFile);
	}

	return 0;
}