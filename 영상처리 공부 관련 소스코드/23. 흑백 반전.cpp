#include "header.h"

int main()
{
	Mat src;
	src = imread("lenna.jpg",IMREAD_GRAYSCALE);
	imshow("원영상", src);

	Mat dst;
	dst = 255 - src;
	imshow("변경된 영상", dst);

	waitKey(0);
	return 0;

}