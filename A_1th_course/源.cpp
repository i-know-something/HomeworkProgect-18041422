#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;

int PointAverage(Mat);				//read a image and get it average of every point

int Binary(Mat, int);				//(compare with every point of Mat with int,two result

int TwoOfCopy(Mat);					//compare the shollow-copy and deep-copy

int main() {

	std::cout << "first program" << std::endl;
	
	cv::Mat Oimg = imread("It_not_my_fault.jpg");
	imshow("Origin Picture", cv::Oimg);

	PointAverage(Oimg);
	
	cv::Mat img_0 = imread("It_not_my_fault.jpg", 0);
	imshow("gray_level", cv::img_0);

	return 0;

}
/*
int PointAverage( Mat Mat_0 ) {
	int hight=Mat_0.rows;
	int weight = Mat_0.cols;

	int i, j;
	i = j = 0;

	for (i=0;i<hight;i++)
		for (j = 0; j < weight; j++)
		{
			uchar* point = Mat_0.ptr<uchar>(i, j);
			uchar average = (point[0] + point[1] + point[2]) / 3;

			point[0] = point[1] = point[2] = average;
		}
	imshow("Average_point", Mat_0);
	return 0;
	

}
*/