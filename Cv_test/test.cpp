#include <opencv2/opencv.hpp>

#include <iostream>

using namespace cv;

int main()
{
	//read a local picture
	//thr file path after imread can be changed to others

	Mat img = imread("1.png");


	imshow("test", img);

	//waiting for any key pressed

	waitKey(0);

	return 0;
}