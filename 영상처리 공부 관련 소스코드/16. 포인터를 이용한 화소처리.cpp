#include "header.h"

int main()
{
	Mat img = imread("lenna.jpg", IMREAD_GRAYSCALE);
	imshow("Original Image", img);

	for (int r = 0; r < img.rows; r++)
	{
		uchar* p = img.ptr<uchar>(r);
		for (int c = 0; c < img.cols; ++c)
			p[c] = saturate_cast<uchar>(p[c] + 30);
	}

	imshow("New Imagae", img);
	waitKey(0);

	return 0;
}