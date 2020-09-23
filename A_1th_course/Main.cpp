#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;

int PointAverage(Mat);					//  1. read a image and get it average of every point

int Binaryzation(Mat, int);				//  3. compare with every point of Mat with int,two result

int TwoOfCopy(Mat);						//  4. compare the shollow-copy and deep-copy

int main() {

	

	std::cout << "hello world" << std::endl;
	
	Mat O_img = imread("It_not_my_fault.jpg");
	imshow("Origin Picture", O_img);
	

	Mat A_img;							//deepcopy a "Mat" for subfuction to process
	O_img.copyTo(A_img);				
	PointAverage(A_img);				
	imshow("Average_picture",A_img);	//show the result


	Mat img_0 = imread("It_not_my_fault.jpg", 0);
	imshow("gray_level", img_0);

	Mat B_img;
	A_img.copyTo(B_img);
	Binaryzation(B_img, 100);
	imshow("binaryzation", B_img);

	TwoOfCopy(O_img);

	waitKey(0);

	return 0;

}



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

	return 0;
	
}



int Binaryzation(Mat Mat_0, int n) {

	int hight = Mat_0.rows;
	int weight = Mat_0.cols*Mat_0.channels();
	int i, j;

	for (i = 0; i < hight; i++) {

		uchar* data = Mat_0.ptr<uchar>(i);
		
		for (j = 0; j < weight; j++){
			
			data[j]=data[j]>n?255:0;
		}
	}

	return 0;
}



int TwoOfCopy(Mat Mat_0) {


	Mat srcMat,S_copy, D_copy;

	Mat_0.copyTo(srcMat);		//Copy the origion picture in subfuction to test;

	S_copy = srcMat;			//shallow copy

	srcMat.copyTo(D_copy);		//deep copy


	Binaryzation(srcMat,100);	//process srcMat by the thrid way


	imshow("the shallow copy after processing", S_copy);

	imshow("the deep copy after processing", D_copy);

	return 0;
}