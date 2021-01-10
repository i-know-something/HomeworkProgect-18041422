/***********************************/
//本周练习内容：通过判断图像特征的方法找到符合条件的区域
//时间：2020.11.18
//补完整时间 2021.1.10


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
	find_chip();
	find_bowlcover();

	return 0;
}


/**********************************/
//练习一：通过圆形度找到图片中的小圆孔并标记,判断半径大小确定是不是要找圆

void find_circle() 
{
	Mat srcMat = imread("1.png");
	Mat GrayMat, BinMat;
	imshow("原图", srcMat);
																			//得到灰度图并反向二值化
	cvtColor(srcMat, GrayMat, COLOR_RGB2GRAY);
	threshold(GrayMat, BinMat, 101, 255, THRESH_BINARY_INV);

																			/*开始圆形度匹配并画圆*/
	vector<vector<Point>> contours;
	findContours(BinMat, contours,RETR_EXTERNAL,CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		double k = rbox.size.width / rbox.size.height;
		if (k > 1.1 || k < 0.9)
			continue;
		else{

			Point Center = rbox.center;
			int r = (rbox.size.width + rbox.size.height) / 4;
																			//如果半径小于20像素点，认为不是要找的
			if (r < 20)
				continue;
			circle(srcMat,Center,r,Scalar(100,100,0),-1,8);
		}
		
		imshow("上色后", srcMat);

	}
	waitKey(0);
	destroyAllWindows();

}


/**********************************/
//练习二：通过对矩形系数找到芯片并标记,同理于第一题

void find_chip()
{
	Mat srcMat = imread("2.jpg");
	Mat GrayMat,OTSUMat,Ele,OpenMat;
	cvtColor(srcMat, GrayMat, COLOR_RGB2GRAY);					//灰度图
	threshold(GrayMat, OTSUMat, 100, 255, THRESH_OTSU);			//大津法二值化
	Ele = getStructuringElement(MORPH_RECT, Size(4,4));			//开操作除掉小的连线
	morphologyEx(OTSUMat, OpenMat,MORPH_OPEN,Ele);
	
	imshow("原图",srcMat);
	imshow("OTSU大津法", OTSUMat);
	imshow("开操作后", OpenMat);


	//开始进行矩形系数判断
	vector<vector<Point>> contours;
	findContours(OpenMat, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
															//如果长宽有一个小20，认为不是芯片
		if (rbox.size.width < 20 || rbox.size.height < 20)
			continue;
		
		double k = rbox.size.width / rbox.size.height;
		
		if (k > 1.1 || k < 0.9)
			continue;

		Point2f pts[4];										//定义四边形的四个顶点,左下，左上，右上，右下
		rbox.points(pts);
															//画芯片的最小外接四边形
		line(srcMat, pts[0], pts[1], Scalar(255, 255, 0), 3);
		line(srcMat, pts[1], pts[2], Scalar(255, 255, 0), 3);
		line(srcMat, pts[2], pts[3], Scalar(255, 255, 0), 3);
		line(srcMat, pts[3], pts[0], Scalar(255, 255, 0), 3);

	}

	imshow("结果", srcMat);

	waitKey(0);
	destroyAllWindows();
}


/*********************************/
//练习三：框红色瓶盖，在HSV域标记红色，再判断大小。
//百度到一种算法是得到HSV域标记后通过canny算子得到边缘，再霍夫变换找圆，再判断填充度找到瓶盖，此算法可适应复杂情况的寻找

void find_bowlcover()
{
	Mat srcMat = imread("3.jpg");
	Mat ssrcMat;
	resize(srcMat, ssrcMat, Size(srcMat.cols*0.2, srcMat.rows*0.2));

	Mat hsv;
	cvtColor(ssrcMat, hsv, COLOR_RGB2HSV);
	for(int i=0;i<hsv.rows;i++)
		for (int j = 0; j < hsv.cols; j++) {		
		
		/*
		opencv 的H范围是0~180，红色的H范围大概是(0~8)∪(120,180)
		S是饱和度，一般是大于一个值,S过低就是灰色（参考值S>80)，
		V是亮度，过低就是黑色，过高就是白色(参考值220>V>50)。
		*/
			if ((hsv.ptr(i, j)[0]>8 && hsv.ptr(i,j)[0]<120)
				||(hsv.ptr(i, j)[1] < 80)
				||(hsv.ptr(i, j)[2] > 220 || hsv.ptr(i, j)[2] < 50))
			{
				hsv.ptr(i, j)[0] = 0;
				hsv.ptr(i, j)[1] = 0;
				hsv.ptr(i, j)[2] = 0;
			}

		}	
	imshow("hsv", hsv);

																	//直接对hsv图像进行灰度化，二值化（因为非红色区域都是黑色，所以没有影响）
	Mat GrayMat,BinMat,Ele,closeMat;
	cvtColor(hsv, GrayMat, COLOR_RGB2GRAY);
	threshold(GrayMat, BinMat, 100, 255, THRESH_BINARY);			//直接对hsv图像二值化得到红色区域掩膜
	Ele = getStructuringElement(MORPH_RECT, Size(4, 4));			//闭操作使白色区域连续
	morphologyEx(BinMat, closeMat, MORPH_CLOSE, Ele);
	imshow("红色区域",closeMat);

	Mat Labels, States, Centrodis;
	int N =connectedComponentsWithStats(closeMat, Labels, States, Centrodis);
	Rect rect;
	for (int i = 1; i < N; i++)
	{
		rect.x = States.at<int>(i, 0);
		rect.y = States.at<int>(i, 1);
		rect.width = States.at<int>(i, 2);
		rect.height =States.at<int>(i, 3);

		if (rect.width < 100 || rect.height < 100)
			continue;

		rectangle(ssrcMat, rect, CV_RGB(255, 255, 0), 3, 8, 0);

	}

	imshow("标记", ssrcMat);

	waitKey(0);
	destroyAllWindows();

}







