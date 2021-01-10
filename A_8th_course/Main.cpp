/***********************************/
//������ϰ���ݣ�ͨ���ж�ͼ�������ķ����ҵ���������������
//ʱ�䣺2020.11.18
//������ʱ�� 2021.1.10


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
	find_chip();
	find_bowlcover();

	return 0;
}


/**********************************/
//��ϰһ��ͨ��Բ�ζ��ҵ�ͼƬ�е�СԲ�ײ����,�жϰ뾶��Сȷ���ǲ���Ҫ��Բ

void find_circle() 
{
	Mat srcMat = imread("1.png");
	Mat GrayMat, BinMat;
	imshow("ԭͼ", srcMat);
																			//�õ��Ҷ�ͼ�������ֵ��
	cvtColor(srcMat, GrayMat, COLOR_RGB2GRAY);
	threshold(GrayMat, BinMat, 101, 255, THRESH_BINARY_INV);

																			/*��ʼԲ�ζ�ƥ�䲢��Բ*/
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
																			//����뾶С��20���ص㣬��Ϊ����Ҫ�ҵ�
			if (r < 20)
				continue;
			circle(srcMat,Center,r,Scalar(100,100,0),-1,8);
		}
		
		imshow("��ɫ��", srcMat);

	}
	waitKey(0);
	destroyAllWindows();

}


/**********************************/
//��ϰ����ͨ���Ծ���ϵ���ҵ�оƬ�����,ͬ���ڵ�һ��

void find_chip()
{
	Mat srcMat = imread("2.jpg");
	Mat GrayMat,OTSUMat,Ele,OpenMat;
	cvtColor(srcMat, GrayMat, COLOR_RGB2GRAY);					//�Ҷ�ͼ
	threshold(GrayMat, OTSUMat, 100, 255, THRESH_OTSU);			//��򷨶�ֵ��
	Ele = getStructuringElement(MORPH_RECT, Size(4,4));			//����������С������
	morphologyEx(OTSUMat, OpenMat,MORPH_OPEN,Ele);
	
	imshow("ԭͼ",srcMat);
	imshow("OTSU���", OTSUMat);
	imshow("��������", OpenMat);


	//��ʼ���о���ϵ���ж�
	vector<vector<Point>> contours;
	findContours(OpenMat, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
															//���������һ��С20����Ϊ����оƬ
		if (rbox.size.width < 20 || rbox.size.height < 20)
			continue;
		
		double k = rbox.size.width / rbox.size.height;
		
		if (k > 1.1 || k < 0.9)
			continue;

		Point2f pts[4];										//�����ı��ε��ĸ�����,���£����ϣ����ϣ�����
		rbox.points(pts);
															//��оƬ����С����ı���
		line(srcMat, pts[0], pts[1], Scalar(255, 255, 0), 3);
		line(srcMat, pts[1], pts[2], Scalar(255, 255, 0), 3);
		line(srcMat, pts[2], pts[3], Scalar(255, 255, 0), 3);
		line(srcMat, pts[3], pts[0], Scalar(255, 255, 0), 3);

	}

	imshow("���", srcMat);

	waitKey(0);
	destroyAllWindows();
}


/*********************************/
//��ϰ�������ɫƿ�ǣ���HSV���Ǻ�ɫ�����жϴ�С��
//�ٶȵ�һ���㷨�ǵõ�HSV���Ǻ�ͨ��canny���ӵõ���Ե���ٻ���任��Բ�����ж������ҵ�ƿ�ǣ����㷨����Ӧ���������Ѱ��

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
		opencv ��H��Χ��0~180����ɫ��H��Χ�����(0~8)��(120,180)
		S�Ǳ��Ͷȣ�һ���Ǵ���һ��ֵ,S���;��ǻ�ɫ���ο�ֵS>80)��
		V�����ȣ����;��Ǻ�ɫ�����߾��ǰ�ɫ(�ο�ֵ220>V>50)��
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

																	//ֱ�Ӷ�hsvͼ����лҶȻ�����ֵ������Ϊ�Ǻ�ɫ�����Ǻ�ɫ������û��Ӱ�죩
	Mat GrayMat,BinMat,Ele,closeMat;
	cvtColor(hsv, GrayMat, COLOR_RGB2GRAY);
	threshold(GrayMat, BinMat, 100, 255, THRESH_BINARY);			//ֱ�Ӷ�hsvͼ���ֵ���õ���ɫ������Ĥ
	Ele = getStructuringElement(MORPH_RECT, Size(4, 4));			//�ղ���ʹ��ɫ��������
	morphologyEx(BinMat, closeMat, MORPH_CLOSE, Ele);
	imshow("��ɫ����",closeMat);

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

	imshow("���", ssrcMat);

	waitKey(0);
	destroyAllWindows();

}







