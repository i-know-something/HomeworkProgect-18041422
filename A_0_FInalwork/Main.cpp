#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int  main() {
	
	//��һ������
	//��ͼƬ���任Ϊ�Ҷ�ͼ��ʹ�ô�򷨶�ֵ���������б�����ȥ��С�����

	Mat srcMat = imread("2.jpg");
	Mat GrayMat,BinMat;

	cvtColor(srcMat, GrayMat, COLOR_RGB2GRAY);
	threshold(GrayMat, BinMat, 100, 255, THRESH_BINARY);

	Mat CloseMat, Ele1;
	Ele1 = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
	morphologyEx(BinMat, CloseMat, MORPH_CLOSE, Ele1);

	imshow("ԭͼ", srcMat);
	imshow("ȥ����Ķ�ֵͼ", CloseMat);



	//�ڶ�������
	//����ɨ��1/16ͼ��Χ����Ϊ��ɫ���ص��������heightΪԲ���ֱ�����Դ�ȷ����һ�α�����ģ���С
	//Ȼ�����һ�α�����ʹ��ͼ��ֻʣԲ�㣬������ͨ���Ǽ���

	int i, j;
	int i_max = int(CloseMat.rows / 4);						//ֻɨ1/16ͼ��
	int j_max = int(CloseMat.cols / 4);
	int Diam = 0;											//��ɫ�ߵ�����ȼ�ΪԲ���ֱ��
	int Max_pre_rows = 0;									//ÿһ���к�ɫ�ߵ������
	int width_now = 0;										//��ɫ�ߵĿ�ȣ���ʱ��

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
	cout << "Բ��ֱ�������أ�" << Diam << endl;

	Mat Ele2;
	Mat LastMat;
	Ele2 = getStructuringElement(MORPH_ELLIPSE, Size(Diam*0.8, Diam*0.8));	//��0.8��ֱ����Ϊ�ṹԪ�ش�Сȥֱ��
	morphologyEx(CloseMat, LastMat, MORPH_CLOSE, Ele2);
	imshow("Բ��circle", LastMat);


	//������ ����
	//ʹ����ͨ���Ǻ������Բ�㲢������
	Mat INVMat;
	Mat ImgLabels;
	Mat States;
	Mat Centroids;
	
	threshold(LastMat, INVMat, 100, 255, THRESH_BINARY_INV);				//��ɫ����
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
	//���Բ��

	imshow("��ǽ��",srcMat);

	cout << "ͼ�й���Բ��" << N - 1 << "��" << endl;


	waitKey(0);
	destroyAllWindows();

	return 0;
}