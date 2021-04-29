#include "tools.h"

int main()
{
	Mat src = imread("ksc2.jpg", IMREAD_COLOR);

	imshow("original", src);

	cvtColor(src, src, COLOR_BGR2HSV);

	Mat bgr[3];
	split(src, bgr);

	equalizeHist(bgr[2], bgr[2]);

	merge(bgr,3, src);

	cvtColor(src, src, COLOR_HSV2BGR);

	imshow("dst", src);

	waitKey(0);

	return 0;

}