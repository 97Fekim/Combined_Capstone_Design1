#include "header.h"

int main()
{
	Mat src = imread("lenna.jpg", IMREAD_GRAYSCALE);
	if (src.empty())return -1;

	Mat dst(src.size(), CV_8U, Scalar(0));

	// 비정상적인 메모리 접근을 막기 위해 x는 1부터 x-1 까지, y는 1부터 y-1까지만 반복한다.
	for (int y = 1; y < src.rows-1; y++)			
	{
		for (int x = 1; x < src.cols-1; x++)
		{
			int sum = 0;
			sum += src.at<uchar>(y - 1, x - 1);
			sum += src.at<uchar>(y , x - 1);
			sum += src.at<uchar>(y + 1, x - 1);
			sum += src.at<uchar>(y - 1, x);
			sum += src.at<uchar>(y, x);
			sum += src.at<uchar>(y + 1, x);
			sum += src.at<uchar>(y - 1, x + 1);
			sum += src.at<uchar>(y, x + 1);
			sum += src.at<uchar>(y + 1, x + 1);
			dst.at<uchar>(y, x) = sum/9;
		}
	}

	imshow("initial", src);
	imshow("final", dst);
	waitKey(0);
	return 0;


}