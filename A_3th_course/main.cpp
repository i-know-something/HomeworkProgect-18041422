#include<iostream>
#include<opencv2/opencv.hpp>
#include<conio.h>

using namespace cv;
using namespace std;

void First();
void Second();
void Thrid();





int main()
{
	//First();

	Second();

	Thrid();


	return 0;
}





/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/


void First() {


	VideoCapture cap(0);

	double scale = 0.5;

	double i_minH = 30;
	double i_maxH = 120;

	double i_minS = 43;
	double i_maxS = 255;

	double i_minV = 55;
	double i_maxV = 255;

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;

		cap >> frame;

		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale);

		Mat rFrame = Mat(ResImgSiz, frame.type());

		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		cvtColor(rFrame, hsvMat, COLOR_RGB2HSV);

		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		imshow("whie:in the range", detectMat);
		imshow("frame", rFrame);

		waitKey(30);

		if (_kbhit())
		{
			destroyAllWindows();

			break;
		}
	}
}




/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/



void Second() {

	Mat srcMat = imread("1.png",0);
	Mat A_TMat, B_TMat;				//adaptiveThreshold  and thresh_binary


	threshold(srcMat, B_TMat, 100, 255, THRESH_OTSU);

	adaptiveThreshold(srcMat, A_TMat, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);


	imshow("THRESH_BINARY", B_TMat);
	imshow("AdaptiveThreshold", A_TMat);


	imwrite("Adapt_Thresh.jpg", A_TMat);
	imwrite("Binary_Thresh.jpg",B_TMat);


	waitKey(0);

	destroyAllWindows();

}


/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/


string window_name = "binaryMat";

void threshod_Mat(int th, void* data) 

{
	Mat src = *(Mat*)(data);
	Mat dst;

	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);
	return;

}


void Thrid() {

	Mat srcMat;
	Mat gryMat;
	int LowTh = 30;
	int MaxTh = 255;

	srcMat = imread("1.png");

	if (!srcMat.data) {

		cout << "Wrong to load the image" << endl;

		return;

	}

	
	cvtColor(srcMat, gryMat,COLOR_RGB2GRAY);

	imshow(window_name, gryMat);

	createTrackbar("threshold", window_name, &LowTh, MaxTh, threshod_Mat, &gryMat);

	waitKey(0);


	return;



}
