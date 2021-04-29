#include "header.h"

int main()
{
	Mat src;
	src = imread("lenna.jpg",IMREAD_GRAYSCALE);
	imshow("원영상", src);
	Mat dst;

	src.convertTo(dst, CV_32F);

	dst.convertTo(src, CV_8UC1);
	imshow("변경된 영상", src);

	waitKey(0);
	return 0;

}