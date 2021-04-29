#include"header.h"

int main()
{
	Mat void1 = imread("¿øº»27.bmp", IMREAD_GRAYSCALE);

	Mat ROI = void1(rect_Mid[0]).clone();

	resize(ROI, ROI, Size(120, 120), 0, 0, 1);

	imwrite("27_1.jpg", ROI);

	waitKey(0);

	return 0;

}