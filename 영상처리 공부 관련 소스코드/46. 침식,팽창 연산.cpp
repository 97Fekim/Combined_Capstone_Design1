#include "header.h"


void main()
{
	Mat src, dst, erosion_dst, dilation_dst;
	src = imread("ksc.jpg", IMREAD_GRAYSCALE);

	imshow("original", src);
	threshold(src, dst, 127, 255, THRESH_BINARY);
	imshow("thresholed", dst);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));

	//침식연산
	erode(dst, erosion_dst, element);

	//팽창연산
	//dilate(dst, dilation_dst, element);

	imshow("Erosion Demo", erosion_dst);
	//imshow("Dilation Demo", dilation_dst);

	waitKey(0);

}

