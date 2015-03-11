#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <dirent.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;


string image_file_name = "../data/orl_faces/s1/1.pgm";
const int BUFFER_LENGTH = 1024;

struct dataTrainTest{
	vector<Mat> xTrain;
	vector<int> yTrain;
	vector<Mat> xTest;
};

struct dataset{
	vector<Mat> x;
	vector<string> y;
	int noCategories;
};


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
			cout << image.at<int>(i, j) << " ";
		cout << "\n";
	}
}

vector<int> eigenFaces(dataTrainTest data, float energy, bool useFirstEigenface){
	vector<int> yTest;
	return yTest;
}

int main(){


	// // showImg(image);

	// Mat S, U, Vt;
	// SVD::compute(image, S, U, Vt);


	// cout << S.rows << " " << S.cols << "\n";
	// cout << U.rows << " " << U.cols << "\n";
	// cout << Vt.rows << " " << Vt.cols << "\n";

	// printMat(S);
	dataset data = readData("orl_faces");
	// showImg(data.x[0]);
	// cout << data.y[0] << "\n";
	// showImg(data.x[12]);
	// cout << data.y[12] << "\n";
	// cout << data.noCategories << "\n";
	// cout << data.y.size() << "\n";

	return 0;
}