#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>

#include <boost/tokenizer.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;
using namespace boost;

string image_file_name = "orl_faces/s1/1.pgm";

void showImg(Mat image){
	   	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	    imshow("MyWindow", image); //display the image which is stored in the 'img' in the "MyWindow" window

	    waitKey(0); //wait infinite time for a keypress

	    destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
}

int main(){
    Mat image;
	image = imread(image_file_name, CV_LOAD_IMAGE_GRAYSCALE);

	int no_rows = image.rows;
	int no_cols = image.cols;

	cout << image.at<uchar>(0,1) << "\n";

	cout << "no_rows: " << no_rows << "\n";
	cout << "no_cols: " << no_cols << "\n";

	image.convertTo(image, CV_32F, 1.0/255);

	// showImg(image);


	Mat S, U, V;
	SVD::compute(image, S, U, V);

	return 0;
}