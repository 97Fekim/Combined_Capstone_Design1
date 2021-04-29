#include "tools.h"

int main()
{
	Mat input = imread("lenna.jpg", IMREAD_GRAYSCALE);
	Mat output = imread("ksc.jpg", IMREAD_GRAYSCALE);

	Point2f inputp[4], outputp[4];

	inputp[0] = Point2f(0, 0);
	inputp[1] = Point2f(0, input.rows); 
	inputp[2] = Point2f(input.cols, input.rows);
	inputp[3] = Point2f(input.cols, 0);

	outputp[0] = Point2f(20, 20);
	outputp[1] = Point2f(30, 50);
	outputp[2] = Point2f(60, 40);
	outputp[3] = Point2f(45, 15);

	Mat h = getPerspectiveTransform(inputp, outputp);
	warpPerspective(input, output, h, output.size(),INTER_LINEAR, BORDER_TRANSPARENT);

	imshow("input", input);
	imshow("warped", output);

	waitKey(0);
}