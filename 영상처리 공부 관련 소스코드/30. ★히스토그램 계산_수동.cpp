#include "header.h"



int main()
{
	Mat src = imread("lenna.jpg", IMREAD_GRAYSCALE);
	imshow("Input image", src);
	int histogram[256] = { 0 };

	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			histogram[(int)src.at<uchar>(y, x)]++;	
	// (y,x) 는 (0,0) ~ (y,x) 까지 도는데, src의 (y,x)가 가지고 있는 
	// 화소의 값이 예를들어 100이다. 그럼 histogram[100]의 값이 1 증가하는 것.
	// 얘는 꼭 기억해야 될듯 >> src.at<uchar>(y,x) ,,

	//for (int count : histogram)	// for문을 신기하게 돌리는 이 형태도 기억해 놓자.
	//	cout << count << ",";
	int sum = 0;
	for (int i = 0; i < 256; ++i)
	{
		cout << "[" << i << "]" << " = " << histogram[i] << endl;
		sum += histogram[i];
	}

	waitKey(0);

	return 0;
}