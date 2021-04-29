#include "header.h"

int main()
{
	Mat img = imread("lenna.jpg", IMREAD_GRAYSCALE);
	imshow("Original Image", img);

	Mat oimage;
	img.convertTo(oimage, -1, 1, 30); // -1은 rType, 1은 alpha, 30은 beta이다.
	// 수식적으로, oimage(x,y) = saturate_cast<rType>(alpha(*input)(x,y)+beta)가 된다.
	// 간단하게 알파를 곱해서 베타를 더한다 라는 뜻이다.

	imshow("New Image", oimage);
	waitKey(0);
	return 0;

}