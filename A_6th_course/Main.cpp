#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void Ex1_Canny();
void Ex2_ROTandRooming();
void Ex3_Affine();
void Ex4_Projection();
void Ex5_betterROT();


int main()
{
	Ex1_Canny();

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
		
		
		
		string Text = "The Window will be closed in " + to_string(int(10 - i / 10)) + " second";
		putText(result, Text, Point(50,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255),4);
		cout << Text << endl;
		imshow("Canny���Ӳ���",result);

		
		waitKey(10);
		i++;
		

	}
	destroyWindow("Canny���Ӳ���");
}


void Ex2_ROTandRooming() {

	Mat srcMat = imread("",0);
	Mat ROTMat, RoomingMat;

	if (srcMat.empty())
	{
		cout << "SomethingWrong in Exercise2" << endl;
		return;
	}
	/***��ת-10�ȣ����ų߶�Ϊ1***/
	float angle = -10;
	float scale = 1;
	/***��ת����***/
	Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);

	const Mat ROT_matrix = getRotationMatrix2D(center, angle, scale);

	warpAffine(srcMat, ROTMat, ROT_matrix, srcMat.Size());




}