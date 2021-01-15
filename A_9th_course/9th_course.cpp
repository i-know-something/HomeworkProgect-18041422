/*����9�οε�ʵ��

���ݣ��ֶ�ʵ��ͼ��HOG���ݶ�ֱ��ͼ��������ȡ���Ƚ�����ͼ������ƶ�

Ҫ��cell size=16���Ƕ�����Ϊ8��

˼·��	���Ȼ������򣬵õ�cell����sobel���Ӽ����ݶ�ֱ��ͼ���Ƕ�������8ά
		Ȼ����2*2���һ��block����һ����õ�һ��������ֱ��ͼ*4��32ά
		ÿcell�ƶ�һ��,��������ͼ����Ͽɵ�HOG�����ӣ�
*/

//��ʵ�����ڣ�2021.1.11

#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace cv;
using namespace std;




//����ͼ���HOG�����Ӽ��㺯��������Mat��HOG�����ַ��������������HOG��ַ��
void cal_HOG(const Mat Mat_0, float HOG[],const int CellSize, const int BlockSize,const int nAngle);




int main()
{
	const int CellSize = 16;
	const int BlockSize = 1;
	const int nAngle = 8;
	//����ֱ��ʹ������cell��HOG���HOG�����ӣ�����BLOCKSize��СΪ1��

	Mat src1Mat = imread("1.jpg");
	Mat src2Mat = imread("2.jpg");
	Mat src3Mat = imread("3.jpg");


	//����HOG����ά��,ÿ��cell��16*16��������ɣ�ÿ��bolck��cell������ɣ���һ��cellΪ����ɨ������ͼ���õ�bins��
	int bins = 0;
	int nX = src1Mat.rows / CellSize;
	int nY = src1Mat.cols / CellSize;

	bins = (nX - BlockSize + 1) * (nY - BlockSize + 1) * BlockSize * BlockSize * nAngle;
	
	cout << "cols" << nY << "rows" << nX << endl;

	float* ref_HOG = new float[bins];
	memset(ref_HOG, 0, sizeof(ref_HOG));
	float* pl_HOG = new float[bins];
	memset(pl_HOG, 0, sizeof(ref_HOG));
	float* bg_HOG = new float[bins];
	memset(bg_HOG, 0, sizeof(ref_HOG));

	cal_HOG(src1Mat, ref_HOG, CellSize, BlockSize, nAngle);
	cal_HOG(src2Mat, pl_HOG, CellSize, BlockSize, nAngle);
	cal_HOG(src3Mat, bg_HOG, CellSize, BlockSize, nAngle);

	float dis1 = normL2Sqr(ref_HOG, pl_HOG, bins);
	float dis2 = normL2Sqr(ref_HOG, bg_HOG, bins);

	cout << "ԭͼ���һ��ͼ�����ƶ�Ϊ" << dis1 << endl;
	cout << "ԭͼ��ڶ���ͼ�����ƶ�Ϊ" << dis2 << endl;

	imshow("1", src1Mat);
	imshow("2", src2Mat);
	imshow("3", src3Mat);

	delete[] ref_HOG,pl_HOG,bg_HOG;

	waitKey(0);


	return 0;
}


// �ڱ�дcell����block���������ӵĳ����ʱ����������⣬����ֻ��ʹ��blockSzie��Ϊ1�����д��
void cal_HOG(const Mat Mat_0, float HOG[],int CellSize,int BlockSize, int nAngle)
{
	Mat gx, gy;
	Mat mag, angle;
	Sobel(Mat_0, gx, CV_32F, 1, 0, 1);
	Sobel(Mat_0, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);

	if (BlockSize != 1){
		cout << "�����ܲ������ƣ��޷�ʵ�ֱ�׼HOG���㣬�뽫BLOCK����Ϊ1" << endl;
		return;
	}
		
	int nX = Mat_0.rows / CellSize;
	int nY = Mat_0.cols / CellSize;

	for (int i = 0; i < nX; i++) 
		for (int j = 0; j < nY; j++)
		{
			Mat roiMat;
			Mat roiMag;
			Mat roiAgl;

			Range roi;
			roi.x = i * CellSize;
			roi.y = j * CellSize;

			roiMat = Mat_0.operator(roi);
			roiMag = mag.operator(roi);
			roiAgl = angle.operator(roi);

			int head = (i * nX + j) * nAngle;

			for (int n=0;n<)


		}




	



}