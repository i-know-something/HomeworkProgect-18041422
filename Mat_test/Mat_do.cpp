#include <opencv2/opencv.hpp>

#include <iostream>



using namespace cv;

int flod(Mat);

int main()
{
	Mat M1;
	Mat M2;

	M1.create (2,2,CV_8UC2);
	M2 = imread("timg9.jpg");
	imshow("M2_0", M2);



	std::cout << M1 << std::endl;

	flod(M2);

	

	imshow("M2——ugly", M2);

	waitKey(0);

	return 0;

}

int flod(Mat M) {

	int hight = M.rows;						//M1's 行数
	int width = M.cols;						//M1's 每行元素总和
	int deepth = M.channels();

	for (int i=0; i < hight; i++) {

		uchar* data = M.ptr <uchar>(i);

		for (int j = 0; j < width / 2;j++)
			for(int k =0; k<deepth;k++){

				data[(width-j-1) * deepth+k] = data[j*deepth+k];
			}
	}

	return 0;
}