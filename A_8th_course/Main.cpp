/***********************************/
//������ϰ���ݣ�ͨ���ж�ͼ�������ķ����ҵ���������������
//ʱ�䣺2020.11.18

#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace cv;
using namespace std;

void find_circle();			//��ϰһ
void find_chip();			//��ϰ��
void find_bowlcover();		//��ϰ��


int main()
{
	find_circle();
	//find_chip();
	//find_bowlcover();

	return 0;
}

/**********************************/
//��ϰһ��ͨ��Բ�ζ��ҵ�ͼƬ�е�СԲ�ײ����
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
	imshow("�����",BinMat);
	
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
//��ϰ����ͨ���Ծ���ϵ���������ж�����оƬ����Χ����


/*********************************/
//��ϰ������Ǻ�ɫƿ�ǣ��������Һ�ɫ�������жϴ�С��








