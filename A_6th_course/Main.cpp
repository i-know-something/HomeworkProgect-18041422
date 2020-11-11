/**********************************************************/
//上一周的作业，旋转和缩放，仿射与投影
//补交时间2020.11.11
//备注：：Point（x,y)在图像映射中，x对应weith（col），y对应height(row),所以（0，height）点应该表示左下角。。

//这次实验虽然对于学会了怎么操作，感觉还是缺少一些形象的理解，

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void Ex1_Canny();								//练习1 canny算子测试
void Ex2_ROTandRooming();						//练习2 旋转和缩放
void Ex3_Affine();								//普通仿射
void Ex4_Perspective();							//投影
void Ex5();										//把斜着的图像转正


int main()
{
	Ex1_Canny();
	Ex2_ROTandRooming();
	Ex3_Affine();
	Ex4_Perspective();
	Ex5();
	return 0;
}


void Ex1_Canny() {
	
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		cout << "Something wrong" << endl;
		return;
	}
	Mat frame,GrayMat,result;
	int i=0;
	while(i<100) {
				
		cap >> frame;
		cvtColor(frame, GrayMat, COLOR_RGB2GRAY);
		Canny(GrayMat, result, 150, 170);	
		
		string Text = "The Window will be closed in " + to_string(int(5 - i / 20)) + " second";
		putText(result, Text, Point(50,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255),4);
		imshow("Canny算子测试",result);
		
		waitKey(10);
		i++;
		
	}
	destroyWindow("Canny算子测试");
}


/************************************/
//进行旋转和缩放变换子函数
void Ex2_ROTandRooming() {

	Mat srcMat = imread("1.jpg");
	Mat ROTMat, RoomingMat;
	if (srcMat.empty())
	{
		cout << "SomethingWrong in Exercise2" << endl;
		return;
	}

	/***旋转-10度，缩放尺度为1***/
	float angle = -10;
	float scale = 1;
	Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);

	//旋转
	const Mat ROT_matrix = getRotationMatrix2D(center, angle, scale);
	warpAffine(srcMat, ROTMat, ROT_matrix, srcMat.size());
	imshow("ROTMat", ROTMat);

	//缩放
	const Mat Rooming= getRotationMatrix2D(center, 0, 0.5);
	warpAffine(srcMat, RoomingMat, Rooming, srcMat.size());
	imshow("RoomingMat", RoomingMat);

	waitKey(0);
	destroyAllWindows();
	return;
}
/*****************************************************/
//进行仿射变换和投影变换
void Ex3_Affine()
{
	Mat srcMat = imread("1.jpg");
	Mat AffineMat;

	Point2f src[] = {
			Point2f(0,0),
			Point2f(100, 100),
			Point2f(50, 200)
	};

	Point2f dst[] = {
			Point2f(50,30),
			Point2f(75,125),
			Point2f(30,150)

	};

	Mat Aff_matrix = getAffineTransform(src, dst);

	warpAffine(srcMat, AffineMat, Aff_matrix, srcMat.size());
	imshow("AffineMat", AffineMat);

	waitKey(0);
	destroyAllWindows();

}


void Ex4_Perspective()
{
	Mat srcMat = imread("1.jpg");
	Mat PerspectiveMat;

	Point2f src[] = {
			Point2f(0,0),
			Point2f(100, 100),
			Point2f(50, 200),
			Point2f(300,30)
	};

	Point2f dst[] = {
			Point2f(50,30),
			Point2f(75,125),
			Point2f(30,150),
			Point2f(500,150)

	};

	Mat Pers_matrix = getPerspectiveTransform(src, dst);

	warpPerspective(srcMat, PerspectiveMat, Pers_matrix, srcMat.size());
	imshow("Perspective",PerspectiveMat);

	waitKey(0);
	destroyAllWindows();


}

//将图片扭正
//用二值化黑白图得到大概轮廓，扫边界找顶点，再进行仿射
void Ex5() {

	Mat srcMat = imread("1.jpg");

	Mat GrayMat, ThreshMat;
	cvtColor(srcMat, GrayMat, COLOR_RGB2GRAY);
	threshold(GrayMat, ThreshMat, 200, 255, THRESH_BINARY);
	imshow("ThreshMat", ThreshMat);

	int width = srcMat.cols;
	int height = srcMat.rows;

	Point2f pt1, pt2, pt3;
	pt1 = pt2 = pt3 = Point2f(0, 0);

	//从第一行开始横向扫描，寻找第一个点
	for (int i = 0, j = 0; j < width; j++) {
		if (ThreshMat.at<uchar>(i, j)!=255) {
			pt1.x = j;
			pt1.y = i;
		}
		//如果第一行没扫到扫下一行
		if (j == width - 1 && pt1.y == 0){
			i = 1;
			j = 0;
		}
	}

	//扫描第一列找到第二个点
	for (int i = 0, j = 0; i < height; i++) {

		if (ThreshMat.at<uchar>(i, j)!=255) {
			pt2.x = j;
			pt2.y = i;
		}
	}

	//扫最后一列找第三个点
	for (int i = 0, j = width - 1; i < height; i++) {

		if (ThreshMat.at<uchar>(i, j) != 255) {
			pt3.x = j;
			pt3.y = i;
		}
	}

	Point2f src[] = { pt1,pt2,pt3 };
	Point2f dst[] = { Point2f(0,0),Point2f(0,width),Point2f(height,0) };
	cout << pt1<<pt2<<pt3 << endl;

	Mat Aff_matrix = getAffineTransform(src, dst);
	Mat AffineMat;
	warpAffine(srcMat, AffineMat, Aff_matrix, srcMat.size());
	imshow("AffineMat", AffineMat);

	waitKey(0);
	destroyAllWindows();

}