#include "header.h"

int main()
{
	Mat src, src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	src = imread("rome.jpg", IMREAD_GRAYSCALE);

	//GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Mat abs_dst;
	
	Laplacian(src, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	//	src, dst, CV_16S, 3, 1, 0, µðÆúÆ®,,	

	convertScaleAbs(dst, abs_dst);

	imshow("image", src);
	imshow("Laplacian", abs_dst);
	waitKey(0);

	return 0;
}