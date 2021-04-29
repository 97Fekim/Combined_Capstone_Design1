#include "header.h"

int main()
{
	Mat src = imread("lenna.jpg");
	Mat dst;

	blur(src, dst, Size(25, 25));	// 11x11 사이즈로 평균값 필터링 시행.

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}