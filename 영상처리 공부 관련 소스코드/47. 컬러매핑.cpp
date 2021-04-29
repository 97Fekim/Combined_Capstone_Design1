#include "tools.h"

int main()
{
	Mat img = imread("lenna.jpg");
	Mat img_color;
	applyColorMap(img, img_color, COLORMAP_HOT);
	imshow("img_color", img_color);
	waitKey(0);

	return 0;
}