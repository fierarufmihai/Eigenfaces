#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

string image_file_name = "data/orl_faces/s1/1.pgm";

void showImg(Mat image){
	   	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	    imshow("MyWindow", image); //display the image which is stored in the 'img' in the "MyWindow" window

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

int main(){
    Mat image;
	image = imread(image_file_name, CV_LOAD_IMAGE_GRAYSCALE);
	image.convertTo(image, CV_32F, 1.0/255);

	// showImg(image);

	Mat S, U, Vt;
	SVD::compute(image, S, U, Vt);

	cout << U.rows << " " << U.cols << "\n";
	cout << Vt.rows << " " << Vt.cols << "\n";

	// printMat(U.mul(Vt));


	return 0;
}