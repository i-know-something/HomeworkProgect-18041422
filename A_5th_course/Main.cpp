#include<iostream>
#include<opencv2/opencv.hpp>
#include<conio.h>



/*
//ֻд�˻�����Ŀ1,2,3,4
//δ��ɼ�ªĥƤ����ı�д
//���β�֪����
*/


using namespace cv;
using namespace std;


void Exercise1_2_3(Mat);				//Mid_Mat,Mean_Mat,Gaus_Mat;

void Exercise4(Mat);					//��Ե��ȡ


int main()
{	
	VideoCapture cap;
	Mat S_srcMat,srcMat;
	cap.open(0);
	int i = 0;			//���i



	while(i<3){

		cap >> S_srcMat;

		if (!S_srcMat.data) {
			cout << "��ȡ����ͷʧ��" << endl; 
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

	medianBlur(srcMat, Mid_Mat, 15);					//��ֵ�˲�
	blur(srcMat, Mean_Mat, Size(5, 5));					//��ֵ�˲�
	GaussianBlur(srcMat, Gaus_Mat, Size(5, 5), 1, 1);	//��˹�˲�

	imshow("srcMat", srcMat);
	imshow("Mid_Mat/��ֵ�˲�", Mid_Mat);
	imshow("Mean_Mat/��ͨ��ֵ�˲�", Mean_Mat);
	imshow("Gaus_Mat/��˹�˲�", Gaus_Mat);

	waitKey(10);

}


void Exercise4(Mat srcMat) {

	Mat grad_x, grad_y;
	Mat ColGetMat, RowGetMat;

	Sobel(srcMat, grad_y, CV_16SC1, 1, 0,3);
	convertScaleAbs(grad_y, RowGetMat);

	Sobel(srcMat, grad_x, CV_16SC1, 0, 1, 3);
	convertScaleAbs(grad_x, ColGetMat);

	imshow("Row����", RowGetMat);
	imshow("Col����", ColGetMat);


	Mat CombMat, GrayMat,OTSUMat;
	
	addWeighted(RowGetMat, 0.5, ColGetMat, 0.5, 0, CombMat);
	cvtColor(CombMat, GrayMat, COLOR_RGB2GRAY);
	threshold(GrayMat, OTSUMat,100, 255, THRESH_OTSU);

	imshow("��Ե��ֵͼ", OTSUMat);

	waitKey(10);

}
