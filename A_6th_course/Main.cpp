/**********************************************************/
//��һ�ܵ���ҵ����ת�����ţ�������ͶӰ
//����ʱ��2020.11.11
//��ע����Point��x,y)��ͼ��ӳ���У�x��Ӧweith��col����y��Ӧheight(row),���ԣ�0��height����Ӧ�ñ�ʾ���½ǡ���

//���ʵ����Ȼ����ѧ������ô�������о�����ȱ��һЩ�������⣬

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void Ex1_Canny();								//��ϰ1 canny���Ӳ���
void Ex2_ROTandRooming();						//��ϰ2 ��ת������
void Ex3_Affine();								//��ͨ����
void Ex4_Perspective();							//ͶӰ
void Ex5();										//��б�ŵ�ͼ��ת��


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
		imshow("Canny���Ӳ���",result);
		
		waitKey(10);
		i++;
		
	}
	destroyWindow("Canny���Ӳ���");
}


/************************************/
//������ת�����ű任�Ӻ���
void Ex2_ROTandRooming() {

	Mat srcMat = imread("1.jpg");
	Mat ROTMat, RoomingMat;
	if (srcMat.empty())
	{
		cout << "SomethingWrong in Exercise2" << endl;
		return;
	}

	/***��ת-10�ȣ����ų߶�Ϊ1***/
	float angle = -10;
	float scale = 1;
	Point2f center(srcMat.cols * 0.5, srcMat.rows * 0.5);

	//��ת
	const Mat ROT_matrix = getRotationMatrix2D(center, angle, scale);
	warpAffine(srcMat, ROTMat, ROT_matrix, srcMat.size());
	imshow("ROTMat", ROTMat);

	//����
	const Mat Rooming= getRotationMatrix2D(center, 0, 0.5);
	warpAffine(srcMat, RoomingMat, Rooming, srcMat.size());
	imshow("RoomingMat", RoomingMat);

	waitKey(0);
	destroyAllWindows();
	return;
}
/*****************************************************/
//���з���任��ͶӰ�任
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

//��ͼƬŤ��
//�ö�ֵ���ڰ�ͼ�õ����������ɨ�߽��Ҷ��㣬�ٽ��з���
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

	//�ӵ�һ�п�ʼ����ɨ�裬Ѱ�ҵ�һ����
	for (int i = 0, j = 0; j < width; j++) {
		if (ThreshMat.at<uchar>(i, j)!=255) {
			pt1.x = j;
			pt1.y = i;
		}
		//�����һ��ûɨ��ɨ��һ��
		if (j == width - 1 && pt1.y == 0){
			i = 1;
			j = 0;
		}
	}

	//ɨ���һ���ҵ��ڶ�����
	for (int i = 0, j = 0; i < height; i++) {

		if (ThreshMat.at<uchar>(i, j)!=255) {
			pt2.x = j;
			pt2.y = i;
		}
	}

	//ɨ���һ���ҵ�������
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