#include "tools.h"

int main()
{
	Mat mid = imread("mid.jpg", IMREAD_GRAYSCALE);
	Mat mid_stretch = imread("mid_stretched.jpg", IMREAD_GRAYSCALE);
	Ptr<CLAHE> clahe = createCLAHE();
	clahe->setClipLimit(4);

	Mat dst;
	clahe->apply(mid, dst);

	imshow("mid", mid);
	imshow("mid,_stretched", mid_stretch);
	imshow("mid_clahe", dst);

	Mat small = imread("small.jpg", IMREAD_GRAYSCALE);
	Mat small_stretch = imread("small_stretched.jpg", IMREAD_GRAYSCALE);
	clahe->setClipLimit(4);

	clahe->apply(small, dst);

	imshow("small", small);
	imshow("small,_stretched", small_stretch);
	imshow("small_clahe", dst);

	Mat third = imread("third.jpg", IMREAD_GRAYSCALE);
	Mat third_stretch = imread("third_stretched.jpg", IMREAD_GRAYSCALE);
	clahe->setClipLimit(4);

	clahe->apply(third, dst);

	imshow("third", third);
	imshow("third,_stretched", third_stretch);
	imshow("third_clahe", dst);

	waitKey();
	
}