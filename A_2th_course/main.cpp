/*This program has four subfunctions, which can run one by one after waitkey(0).
* 
And the result of histogram has been saved ""*/


#include<opencv2/opencv.hpp>
#include<iostream>
#include<conio.h>

using namespace cv;

void Separate_RGB();		//No.1
void Vedio_cut();			//No.2
void DrawOthers();			//No.3
void DrawHistogram();		//No.4&NO.5


int main() {


		Separate_RGB();

		Vedio_cut();

		DrawOthers();

		DrawHistogram();



	waitKey(0);

	return 0;

}

															//sepatate RGB 

void Separate_RGB() {

	Mat src_color = imread("First.png");

	std::vector<cv::Mat> Channels;
	split(src_color, Channels);
	Mat B = Channels.at(0);
	Mat G = Channels.at(1);
	Mat R = Channels.at(2);

	imshow("Red", R);
	imshow("Green", G);
	imshow("Blue", B);
	imshow("Original Mat", src_color);

	waitKey(0);

	destroyAllWindows();
}

															//camera and fpsget

void Vedio_cut() {
	VideoCapture cap;

	cap.open(0);

	if (!cap.isOpened()){

		std::cout << "Can't open the camera" << std::endl;
		return;

	}


	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps:" << fps << std::endl;

	std::cout << "press spacekey to stop it ";

	while (1) {
		
		cv::Mat frame;
		bool rSucess = cap.read(frame);
		if (!rSucess) {

			std::cout << "Can't get any fps from vedio" << std::endl;
			return;

		}
		else {

			cv::imshow("frame", frame);

		}

		waitKey(20);

		if (_kbhit()) {

			destroyAllWindows();
			break;
		}
	}

}


void DrawOthers() {
	
														//Creat a Mat for draw
	Mat Mat_0(200, 200, CV_8UC3, Scalar(255, 255, 255));


														//Circle 
	Point pt;
	pt.x = 100;
	pt.y = 100;
	circle(Mat_0, pt, 50, CV_RGB(12, 34, 56), 5, 8, 0);
	imshow("circle", Mat_0);

	
														//Line
	Mat_0 = Scalar(255, 255, 255);
	Point pt1, pt2;
	pt1.x = pt1.y = 0;
	pt2.x = pt2.y = 123;

	line(Mat_0, pt1, pt2, CV_RGB(0, 255, 255), 5, 8, 0);
	
	imshow("line", Mat_0);
	
														//Rect

	Mat_0 = Scalar(255, 255, 255);
	Rect rect;
	rect.x = rect.y = rect.width = rect.height = 100;

	rectangle(Mat_0, rect, CV_RGB(0, 0, 0), 1, 8, 0);
	imshow("rectangle", Mat_0);

	waitKey(0);

	destroyAllWindows();

	return;
}




													//show Histogram and draw

void DrawHistogram() {
	
	Mat M0 = imread("It_is_not_my_fault.jpg", 0);
	
	float histgram[256];
	for (int i = 0; i < 256; i++)
		histgram[i] = 0;

	int N = M0.rows * M0.cols;

													//count all point
	for (int i = 0; i < M0.rows; i++){

		uchar* point = M0.ptr<uchar>(i);
		
		for (int j = 0; j < M0.cols; j++) {

			histgram[ point[j] ] += 1;
		}
	}

	std::cout << "the hisgram of this picture is ::" << std::endl;
	
	int Max_h = 0;								//Find the Max %

	for (int i = 0; i < 256; i++) {
		histgram[i]=((histgram[i]/N)*100);				
		std::cout << histgram[i] << "%";

		if (histgram[i] > Max_h)
			Max_h = histgram[i];
		
	}
	std::cout << std::endl;

	int Mod = 100 / Max_h;						//Let the Max_h of histgram 100pt;

												//Draw and save

	Mat Mat_hist(100, 256, CV_8UC3, Scalar(255,255,255));

	for (int i = 0; i < 256; i++) {

		Point Pt1, Pt2;
		Pt1.x = Pt2.x = i;
		Pt1.y = 100;
		Pt2.y = 100 - (histgram[i] * Mod);

		line(Mat_hist, Pt1, Pt2, CV_RGB(0, 0, 0), 1, 8, 0);
	}

		imshow("histgram", Mat_hist);
		imwrite("Histgram_of_ItisXXX.jpg", Mat_hist);

		waitKey(0);
}