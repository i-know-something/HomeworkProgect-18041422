#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;



void Exercise1(void);
void Exercise2(void);
void Exercise3(void);
void Exercise4(void);





int main() {


	Exercise1();			//Some Basic Operation

	Exercise2();			//ConnectedComponentMark

	Exercise3();			// BinzationCount();

	Exercise4();			// ClipsCounting();

	return 0;
}


void Exercise1()
{

	Mat srcMat = imread("1.jpg", 0);
		imshow("Gray_SrcMat", srcMat);

	Mat BinMat,OTSUMat,TriangleMat;
		threshold(srcMat, BinMat, 100, 255, THRESH_BINARY);					//查看不同二值化后的结果
		threshold(srcMat, OTSUMat, 100, 255, THRESH_OTSU);
		threshold(srcMat, TriangleMat, 100, 255, THRESH_TRIANGLE);

		imshow("TMAT", BinMat);
		imshow("OTSU_MAT", OTSUMat);
		imshow("TriangelMat", TriangleMat);									//发现三角二值化效果最好，为了体现后续操作，选手动确定阈值的BINAEY

	waitKey(0);
		destroyWindow("OTSU_MAT");
		destroyWindow("TriangelMat");

	Mat ErodeMat, DilateMat, OpenMat, CloseMat;
	Mat Ele = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));			//5*5椭圆区域
																		//此处可区域以借鉴阈值可调那个搞一个滑动条确定
	erode(BinMat, ErodeMat, Ele);
	dilate(BinMat, DilateMat, Ele);
	morphologyEx(BinMat, OpenMat, MORPH_OPEN, Ele);
	morphologyEx(BinMat, CloseMat, MORPH_CLOSE, Ele);

		imshow("腐蚀Eeode", ErodeMat);
		imshow("膨胀Dilate", DilateMat);
		imshow("OPEN", OpenMat);
		imshow("CLOSE", CloseMat);

	waitKey(0);
	destroyAllWindows();

	return;
}


void Exercise2() {

	Mat srcMat = imread("1.jpg",0);


	Mat BinMat,ImgLabels,ImgStates,ImgCentroids;

	threshold(srcMat, BinMat, 100, 255, THRESH_BINARY);

	
	int i, n;
	n = connectedComponentsWithStats(BinMat, ImgLabels, ImgStates, ImgCentroids);
	cout << n << endl;

	Rect rect;

	for (i = 1;i < n; i++)
	{	
		rect.x = ImgStates.at<int>(i , 0);
		rect.y = ImgStates.at<int>(i , 1);
		rect.width = ImgStates.at<int>(i , 2);
		rect.height = ImgStates.at<int>(i , 3);

		rectangle(BinMat, rect, CV_RGB(255,255,255), 1, 8, 0);

	}
	imshow("markcomponent",BinMat);

	waitKey(0);
	destroyAllWindows();
	return;



}

void Exercise3() {

	Mat srcMat = imread("2.jpg",0);
	imshow("srcMat", srcMat);
	Mat OTSUMat;
	threshold(srcMat, OTSUMat, 100, 255,THRESH_OTSU);
	imshow("OTSUMAT", OTSUMat);


	//思路：：
	//先进行一次闭运算去掉小的点（噪声），再求竖向黑色的最大宽度以确定合适的结构元素大小，
	//然后进行一次闭运算使得图像只剩圆点，进行连通域标记计数
	
	Mat CloseMat1, CloseMat2;
	Mat Ele1= getStructuringElement(MORPH_ELLIPSE, Size(5, 5));

	morphologyEx(OTSUMat, CloseMat1, MORPH_CLOSE, Ele1);
	imshow("去噪后的二值图", CloseMat1);


	int i, j;
	int i_max = int(CloseMat1.rows/4);						//只扫1/16图像
	int j_max = int(CloseMat1.cols/4);
	int Diam = 0;											//黑色线的最大宽度即为圆点的直径
	int Max_pre_rows =0;									//每一竖行黑色线的最大宽度
	int width_now=0;										//黑色线的宽度（此时）


	for (j = 0; j < j_max; j++,width_now=0) {
		for (i = 0; i < i_max; i++) {

			if (!CloseMat1.at<uchar>(i, j))
				width_now++;
			else{
				Max_pre_rows = (width_now >Max_pre_rows) ? width_now : Max_pre_rows;
				width_now = 0;
			}
		}
		Diam = (Max_pre_rows > Diam) ? Max_pre_rows : Diam;
	}

	cout << "圆点直径（像素）"<<Diam << endl;

	Mat Ele2=getStructuringElement(MORPH_ELLIPSE, Size(Diam - 10, Diam - 10));
	morphologyEx(CloseMat1, CloseMat2, MORPH_CLOSE, Ele2);
	imshow("圆点circle", CloseMat2);
	
	Mat INVMat, ImgLabels;
	threshold(CloseMat2, INVMat, 100, 255, THRESH_BINARY_INV);				//反色处理
	int N = connectedComponents(INVMat, ImgLabels);							//标记连通域
	cout << "图中共有圆点" << N - 1 << "个" << endl;

	waitKey(0);
	destroyAllWindows();

	return;
}

void Exercise4()

//思路：：调用 connectedComponentsWithStats 函数，
//根据面积来判断是否为回形针

//想不到其他招了，，，（用长和宽太不靠谱，弃之
{
	Mat srcMat = imread("3.jpg", 0);
	Mat OTSUMat,  ClearMat;
	threshold(srcMat, OTSUMat, 100, 255, THRESH_BINARY_INV|THRESH_OTSU);	//大津并取反

	Mat ELE= getStructuringElement(MORPH_ELLIPSE, Size(3,3));				//开运算去除白色噪点
	morphologyEx(OTSUMat, ClearMat, MORPH_OPEN, ELE);
	imshow("Clear_INV_OTSU_MAT", ClearMat);

	int N=0;												
	Mat Labels, States,Centrodis;
	N=connectedComponentsWithStats(ClearMat, Labels, States, Centrodis);

	cout <<endl<<endl<< N << endl<<endl;
	cout << States << endl << endl << endl;
	//cout << Centrodis << endl << endl;

	int Average_S = 0;

	for (int i = 1; i < N; i++) {
		Average_S += States.at<int>(i, 4);
	}
	Average_S = int(Average_S / (N - 1));

	//cout << Average_S << endl;

	bool* Flag = new bool[N];												//判断是否为回形针的标志位数组
	*Flag = false;															//背景不是连通域
	int NumberAll = 0;


	int Max_S = int(Average_S * 1.2);										//认为面积误差大度20%的不是回形针
	int Min_S = int(Average_S * 0.8);

	for (int i = 1; i < N; i++) {											
		if (States.at<int>(i, 4) < Min_S || States.at<int>(i, 4) > Max_S)
			Flag[i] = false;
		else
			Flag[i] = true;

		if(Flag[i])
			NumberAll++;
	}

	cout << "图中有回形针" << NumberAll << "个" << endl;
	waitKey(0);

	delete[] Flag;
	destroyAllWindows();
	return;

}

