#include "header.h"

int main()
{
	Mat image = imread("lenna.jpg", IMREAD_GRAYSCALE);

	float weights[] = {
		1 / 9.0f, 1 / 9.0f, 1 / 9.0f,
		1 / 9.0f, 1 / 9.0f, 1 / 9.0f,
		1 / 9.0f, 1 / 9.0f, 1 / 9.0f
	};

	Mat mask(3, 3, CV_32F, weights);
	Mat blur;
	filter2D(image, blur, -1, mask);		// mask를 가지고 image에 블러 수행 >> blur에 저장.
	blur.convertTo(blur, CV_8U);

	imshow("image", image);
	imshow("blur", blur);
	waitKey(0);

	return 0;
} 