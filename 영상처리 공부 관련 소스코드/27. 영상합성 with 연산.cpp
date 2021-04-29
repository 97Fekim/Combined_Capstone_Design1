#include "header.h"

int main()
{
	Mat src1 = imread("dog.jpg");
	Mat src2 = imread("fekim.jpg");
	Mat dst;
	dst = src1 + src2;
	imshow("dog", src1);
	imshow("fekim", src2);
	imshow("New", dst);
	waitKey(0);
	return 0;
}