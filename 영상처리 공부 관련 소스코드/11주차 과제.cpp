#include "tools.h"
#include <math.h>

Mat getFilter(Size size)
{
	Mat tmp = Mat(size, CV_32F);
	Point center = Point(tmp.cols / 2, tmp.rows / 2);
	double radius, D = 50, n = 2;

	for (int i = 0; i < tmp.rows; i++)
	{
		for (int j = 0; j < tmp.cols; j ++)
		{
			radius = (double)sqrt(pow((j - center.x), 2.0) + pow((double)(i-center.y),2.0));
			tmp.at<float>(i, j) = (float)(1 / (1 + (sqrt(2.0)-1.0)*pow((double)(radius / D), (double)(2 * n))));
		}
	}

	Mat toMerge[] = { tmp,tmp };
	Mat filter;
	merge(toMerge, 2, filter);
	return filter;
}

void shuffleDFT(Mat& src)
{
	int cX = src.cols / 2;
	int cY = src.rows / 2;

	Mat q1(src,Rect(0, 0, cX, cY));
	Mat q2(src,Rect(cX, 0, cX, cY));
	Mat q3(src, Rect(0, cY, cX, cY));
	Mat q4(src, Rect(cX, cY, cX, cY));
	Mat tmp;

	q1.copyTo(tmp);
	q4.copyTo(q1);
	tmp.copyTo(q4);
	
	q2.copyTo(tmp);
	q3.copyTo(q2);
	tmp.copyTo(q3);
}



int main()
{
	Mat src = imread("ksc.jpg", IMREAD_GRAYSCALE);
	Mat src_float, dft_image, result, inverted_image;
	imshow("src", src);

	src.convertTo(src_float, CV_32FC1, 1.0 / 255.0);
	dft(src_float, dft_image, DFT_COMPLEX_OUTPUT);
	shuffleDFT(dft_image);
	//displayDFT(dft_image);

	Mat lowpass = getFilter(dft_image.size());
	multiply(dft_image,lowpass,result);

	shuffleDFT(result);
	idft(result, inverted_image, DFT_SCALE | DFT_REAL_OUTPUT);

	imshow("inverted", inverted_image);
	waitKey(0);

	return 1;

}