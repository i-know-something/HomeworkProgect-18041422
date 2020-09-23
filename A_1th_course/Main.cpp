#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;

Mat PointAverage(Mat);				//read a image and get it average of every point

int Binaryzation(Mat, int);				//(compare with every point of Mat with int,two result

int TwoOfCopy(Mat);					//compare the shollow-copy and deep-copy

int main() {

	std::cout << "first program" << std::endl;
	
	Mat Oimg = imread("It_not_my_fault.jpg");
	imshow("Origin Picture", Oimg);

	Mat A_img = PointAverage(Oimg);
	imshow("Average_picture",A_img);
	
	Mat img_0 = imread("It_not_my_fault.jpg", 0);
	imshow("gray_level", img_0);

	Binaryzation(A_img, 150);

	TwoOfCopy(Oimg);

	waitKey(0);

	return 0;

}

Mat PointAverage( Mat Mat_0 ) {
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

	return Mat_0;
	
}

int Binaryzation(Mat Mat_0, int n) {

	int hight = Mat_0.rows;
	int weight = Mat_0.cols*Mat_0.channels();
	int i, j;

	for (i = 0; i < hight; i++) {

		uchar* data = Mat_0.ptr<uchar>(i);
		
		for (j = 0; j < weight; j++){
			
			data[j]=data[j]>n?0:255;
		}
	}

	imshow("binaryzation", Mat_0);
	waitKey(0);

	return 0;
}

TwoOfCopy(Mat Mat_0) {
	return 0£»
}