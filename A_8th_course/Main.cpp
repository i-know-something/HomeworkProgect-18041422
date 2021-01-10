/***********************************/
//本周练习内容：通过判断图像特征的方法找到符合条件的区域
//时间：2020.11.18

#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace cv;
using namespace std;

void find_circle();			//练习一
void find_chip();			//练习二
void find_bowlcover();		//练习三


int main()
{
	find_circle();
	//find_chip();
	//find_bowlcover();

	return 0;
}

/**********************************/
//练习一：通过圆形度找到图片中的小圆孔并标记
void find_circle() 
{
	Mat srcMat = imread("1.png", 0);
	Mat BinMat,openMat,closeMat,Ele;
	threshold(srcMat, BinMat, 100, 255, THRESH_BINARY_INV);
	//Ele = getStructuringElement(MORPH_ELLIPSE, Size(3,3));
	//morphologyEx(BinMat, closeMat, MORPH_CLOSE,Ele);
	//morphologyEx(closeMat, openMat, MORPH_OPEN, Ele);
	imshow("srcMat", srcMat);
	//imshow("OTSUMat", OTSUMat);
	imshow("处理后",BinMat);
	
	vector<vector<Point>> contours;
	
	//vector<Vec4i> hierarchy;

	findContours(BinMat, contours,RETR_EXTERNAL,CHAIN_APPROX_NONE);


	for (int i; i < contours.size; i++) {
		RotatedRect rbox = minAreaRect(contours[i]);

		double k = rbox.size.width / robx.size.height;

		if (k > 1.1 || k < 0.9)
			continue;
		else{

			Point Center = rbox.center;
			int r = (rbox.size.width + robx.size.height) / 2;

			circle(srcMat,Center,r,Scalar(255,255,i),3);
		}
		



	}

	waitKey(0);
	destroyAllWindows();

}

/**********************************/
//练习二：通过对矩形系数？？的判断区分芯片与周围引脚


/*********************************/
//练习三：标记红色瓶盖，可以先找红色区域，再判断大小吧








