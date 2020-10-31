#include<iostream>
#include<opencv2/opencv.hpp>
#include<conio.h>



/*
//只写了基础题目1,2,3,4
//未完成简陋磨皮程序的编写
//尴尬不知所言
*/


using namespace cv;
using namespace std;


void Exercise1_2_3(Mat);				//Mid_Mat,Mean_Mat,Gaus_Mat;

void Exercise4(Mat);					//边缘提取


int main()
{	
	VideoCapture cap;
	Mat S_srcMat,srcMat;
	cap.open(0);
	int i = 0;			//题号i



	while(i<3){

		cap >> S_srcMat;

		if (!S_srcMat.data) {
			cout << "读取摄像头失败" << endl; 
			continue;
		}

		else 

		{
			flip(S_srcMat, srcMat, 1);

			switch (i){
			case 0:
				Exercise1_2_3(srcMat);
				break;
			case 1:
				Exercise4(srcMat);
				break;
			default:;
				//Exercise5(srcMat);
			}

			if (_kbhit()) {
				_getch();
				i++;  
				destroyAllWindows();
			}

		}
	}


	return 0;

}



void Exercise1_2_3(Mat srcMat) {

	Mat Mid_Mat, Mean_Mat, Gaus_Mat;

	medianBlur(srcMat, Mid_Mat, 15);					//中值滤波
	blur(srcMat, Mean_Mat, Size(5, 5));					//均值滤波
	GaussianBlur(srcMat, Gaus_Mat, Size(5, 5), 1, 1);	//高斯滤波

	imshow("srcMat", srcMat);
	imshow("Mid_Mat/中值滤波", Mid_Mat);
	imshow("Mean_Mat/普通均值滤波", Mean_Mat);
	imshow("Gaus_Mat/高斯滤波", Gaus_Mat);

	waitKey(10);

}


void Exercise4(Mat srcMat) {

	Mat grad_x, grad_y;
	Mat ColGetMat, RowGetMat;

	Sobel(srcMat, grad_y, CV_16SC1, 1, 0,3);
	convertScaleAbs(grad_y, RowGetMat);

	Sobel(srcMat, grad_x, CV_16SC1, 0, 1, 3);
	convertScaleAbs(grad_x, ColGetMat);

	imshow("Row纵向", RowGetMat);
	imshow("Col横向", ColGetMat);


	Mat CombMat, GrayMat,OTSUMat;
	
	addWeighted(RowGetMat, 0.5, ColGetMat, 0.5, 0, CombMat);
	cvtColor(CombMat, GrayMat, COLOR_RGB2GRAY);
	threshold(GrayMat, OTSUMat,100, 255, THRESH_OTSU);

	imshow("边缘二值图", OTSUMat);

	waitKey(10);

}
