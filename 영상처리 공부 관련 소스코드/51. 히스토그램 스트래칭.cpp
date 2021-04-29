#include "tools.h"

int main()
{
	Mat src = imread("11.jpg", IMREAD_GRAYSCALE);


	int histogram[256] = { 0 };
	int max = -1;
	int min = 300;
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			histogram[(int)src.at<uchar>(y, x)]++;

	for (int i = 0; i < 256; ++i)
	{
		if (histogram[i] > max)
		{
			max = i;
		}
	}

	for (int i = 0; i < 256; ++i)
	{
		if (histogram[i] < min)
		{
			min = i;
		}
	}
	cout << max << endl << min << endl;
	return 0;
}