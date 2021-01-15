#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int  main() {
	
	//第一步：：
	//读图片，变换为灰度图后使用大津法二值化，并进行闭运算去除小的噪点

	Mat srcMat = imread("2.jpg");
	Mat GrayMat,BinMat;

	cvtColor(srcMat, GrayMat, COLOR_RGB2GRAY);
	threshold(GrayMat, BinMat, 100, 255, THRESH_BINARY);

	Mat CloseMat, Ele1;
	Ele1 = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	morphologyEx(BinMat, CloseMat, MORPH_CLOSE, Ele1);

	imshow("原图", srcMat);
	imshow("去噪点后的二值图", CloseMat);



	//第二步：：
	//纵向扫描1/16图像范围，认为黑色像素的纵向最大height为圆点的直径，以此确定下一次闭运算模板大小
	//然后进行一次闭运算使得图像只剩圆点，进行连通域标记计数

	int i, j;
	int i_max = int(CloseMat.rows / 4);						//只扫1/16图像
	int j_max = int(CloseMat.cols / 4);
	int Diam = 0;											//黑色线的最大宽度即为圆点的直径
	int Max_pre_rows = 0;									//每一竖行黑色线的最大宽度
	int width_now = 0;										//黑色线的宽度（此时）

	for (j = 0; j < j_max; j++, width_now = 0) {
		for (i = 0; i < i_max; i++) {

			if (!CloseMat.at<uchar>(i, j))
				width_now++;
			else {
				Max_pre_rows = (width_now > Max_pre_rows) ? width_now : Max_pre_rows;
				width_now = 0;
			}
		}
		Diam = (Max_pre_rows > Diam) ? Max_pre_rows : Diam;
	}
	cout << "圆点直径（像素）" << Diam << endl;

	Mat Ele2;
	Mat LastMat;
	Ele2 = getStructuringElement(MORPH_ELLIPSE, Size(Diam*0.8, Diam*0.8));	//以0.8倍直径作为结构元素大小去直线
	morphologyEx(CloseMat, LastMat, MORPH_CLOSE, Ele2);
	imshow("圆点circle", LastMat);


	//第三步 ：：
	//使用连通域标记函数标记圆点并画出来
	Mat INVMat;
	Mat ImgLabels;
	Mat States;
	Mat Centroids;
	
	threshold(LastMat, INVMat, 100, 255, THRESH_BINARY_INV);				//反色处理
	int N = connectedComponentsWithStats(INVMat, ImgLabels, States,Centroids);
	
	for (i = 1; i < N; i++)
	{
		Rect rect;
		rect.x = States.at<int>(i, 0)-1;
		rect.y = States.at<int>(i, 1)-1;
		rect.width = States.at<int>(i, 2)+2;
		rect.height = States.at<int>(i, 3)+2;

		rectangle(srcMat, rect, Scalar(255 ,255, 0), 2, 8, 0);
	}	
	//标记圆点

	imshow("标记结果",srcMat);

	cout << "图中共有圆点" << N - 1 << "个" << endl;


	waitKey(0);
	destroyAllWindows();

	return 0;
}