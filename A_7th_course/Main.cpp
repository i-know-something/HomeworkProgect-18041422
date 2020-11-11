/****************************/
//学习霍夫变换并进行相关练习
//实验日期：2020.11.11



#include<iostream>
#include<vector>
#include<conio.h>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() 
{
	Mat srcMat = imread("18.jpg", 0);
	Mat cannyMat,result_HoughL,result_HoughLP;
	Canny(srcMat, cannyMat, 100, 200);
	imshow("cannyMat", cannyMat);
	srcMat.copyTo(result_HoughL);
	srcMat.copyTo(result_HoughLP);


/***********************************/
//练习1 图像旋转而不丢失信息
	Mat AffineMat;
	Point2f center(srcMat.cols / 2.0,srcMat.rows / 2.0);
	//旋转20度，缩放尺度为1.
	Mat ROT = getRotationMatrix2D(center, 20, 1);
	//获取外接四边形
	Rect box = RotatedRect(center, srcMat.size(),20).boundingRect();
	//调整变换矩阵
	ROT.at<double>(0, 2) += box.width / 2.0 - center.x;
	ROT.at<double>(1, 2) += box.height / 2.0 - center.y;
	warpAffine(srcMat, AffineMat, ROT, box.size());
	imshow("AffineMat", AffineMat);
	

/***********************************/
//使用HoughLines函数，画直线
	vector<Vec2f> HLlines;
	HoughLines(cannyMat,HLlines, 1, CV_PI / 180,100);
	vector<Vec2f>::iterator it = HLlines.begin();
	for (; it != HLlines.end(); it++)
	{
		float rho = (*it)[0];
		float theta = (*it)[1];
		Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;

		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));

		line(result_HoughL,pt1, pt2, Scalar(255, 255, 0),1,LINE_AA);
	}
	imshow("result", result_HoughL);
	


/*********************************/
//使用HoughLinesP函数画线段
	Mat HLPlines;
	HoughLinesP(cannyMat, HLPlines, 1, CV_PI / 180, 50,10,20);
	cout << HLPlines << endl;
	
	for (int i = 0; i < HLPlines.rows; i++) {
		Point pt1, pt2;

		pt1.x = HLPlines.ptr<int>(i)[0];
		pt1.y = HLPlines.ptr<int>(i)[1];
		pt2.x = HLPlines.ptr<int>(i)[2];
		pt2.y = HLPlines.ptr<int>(i)[3];
		line(result_HoughLP, pt1, pt2, Scalar(255, 0, 0), 3, LINE_AA, 0);
	}
	imshow("HoughLinesP_result", result_HoughLP);
	waitKey(0);

	return 0;
}
