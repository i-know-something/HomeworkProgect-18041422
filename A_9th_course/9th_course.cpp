/*补第9次课的实验

内容：手动实现图像HOG（梯度直方图）特征提取并比较三幅图相的相似度

要求：cell size=16，角度量化为8，

思路：	首先划分区域，得到cell，用sobel算子计算梯度直方图，角度量化后，8维
		然后用2*2组成一个block，归一化后得到一个特征：直方图*4，32维
		每cell移动一次,遍历整幅图像，组合可得HOG描述子，
*/

//补实验日期：2021.1.11

#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace cv;
using namespace std;




//定义图像的HOG描述子计算函数，输入Mat，HOG数组地址，计算结果将放入HOG地址中
void cal_HOG(const Mat Mat_0, float HOG[],const int CellSize, const int BlockSize,const int nAngle);




int main()
{
	const int CellSize = 16;
	const int BlockSize = 1;
	const int nAngle = 8;
	//本题直接使用所有cell的HOG组成HOG描述子，所以BLOCKSize大小为1。

	Mat src1Mat = imread("1.jpg");
	Mat src2Mat = imread("2.jpg");
	Mat src3Mat = imread("3.jpg");


	//计算HOG特征维数,每个cell由16*16个像素组成，每个bolck由cell本身组成，以一个cell为步长扫过整幅图，得到bins数
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

	cout << "原图与第一幅图的相似度为" << dis1 << endl;
	cout << "原图与第二幅图的相似度为" << dis2 << endl;

	imshow("1", src1Mat);
	imshow("2", src2Mat);
	imshow("3", src3Mat);

	delete[] ref_HOG,pl_HOG,bg_HOG;

	waitKey(0);


	return 0;
}


// 在编写cell——block——描述子的程序的时候出现了问题，所以只好使用blockSzie恒为1的情况写。
void cal_HOG(const Mat Mat_0, float HOG[],int CellSize,int BlockSize, int nAngle)
{
	Mat gx, gy;
	Mat mag, angle;
	Sobel(Mat_0, gx, CV_32F, 1, 0, 1);
	Sobel(Mat_0, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);

	if (BlockSize != 1){
		cout << "程序功能不够完善，无法实现标准HOG计算，请将BLOCK调整为1" << endl;
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