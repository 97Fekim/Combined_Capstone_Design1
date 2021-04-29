#include "header.h"

int main()
{
	Mat img1 = Mat::zeros(Size(400, 200), CV_8UC1);
	Mat img2 = Mat::zeros(Size(400, 200), CV_8UC1);

	Mat t1 = img1(Range(20, 180), Range(50, 200));
	t1 = 255;
	imshow("img1", img1);
	Mat t2 = img2(Range(100, 150), Range(150, 300));
	t2 = 255;
	imshow("img2", img2);

	Mat result;
	bitwise_and(img1, img2, result);
	imshow("and", result);
	bitwise_or(img1, img2, result);
	imshow("or", result);

	waitKey(0);
	return 0;

}