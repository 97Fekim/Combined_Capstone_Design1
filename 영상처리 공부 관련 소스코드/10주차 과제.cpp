#include "tools.h"

int main()
{
	Mat img = imread("ksc3.jpg", IMREAD_COLOR);
	if (img.empty()) { return -1; }

	Mat imgHSV;
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	Mat imgThresholed;
	inRange(imgHSV, Scalar(7, 0, 0), Scalar(10, 255, 255), imgThresholed);

	imshow("Origaianl", img);
	imshow("THreshed", imgThresholed);
	waitKey(0);
	return 0;
}