#include "header.h"




void drawHist(int hist[], char mode)
{
	int hist_h = 400;	// 히스토그램 영상의 높이
	Mat histimg(hist_h, 512, CV_8UC3, Scalar(255, 255, 255)); // 영상버퍼

	Scalar color;	// 히스토그램 색상

	switch (mode)
	{
		case 'B':color = Scalar(255, 0, 0); break;
		case 'G':color = Scalar(0, 255, 0); break;
		case 'R':color = Scalar(0, 0, 255); break;
		case 'K':color = Scalar(0, 0, 0); break;
	}

	int max = -30;
	for (int i = 0; i < 256; i++)
		if (max < hist[i]) max = hist[i];

	for (int i = 0; i < 256; i++)
		hist[i] = floor(((double)hist[i] / max) * hist_h);

	for (int i = 0; i < 256; i++)
		line(histimg, Point(2 * i, hist_h), Point(2 * i, hist_h - hist[i]), color);

	switch (mode)
	{
	case 'B':imshow("Histogram Blue", histimg); break;
	case 'G':imshow("Histogram Green", histimg); break;
	case 'R':imshow("Histogram Red", histimg); break;
	case 'K':imshow("Histogram Gray_scale", histimg); break;
	}

}

int main()
{
	Mat src = imread("lenna.jpg", IMREAD_COLOR);
	imshow("Input image", src);
	

	if (src.channels() == 1)
	{
		int histogram[256] = { 0 };
		for (int y = 0; y < src.rows; y++)
			for (int x = 0; x < src.cols; x++)
				histogram[(int)src.at<uchar>(y, x)]++;		// 히스토그램을 계산한다.
		drawHist(histogram,'K');
	}
	else
	{
		int histogram[3][256] = { 0 };

		for (int y = 0; y < src.rows; ++y)
			for (int x = 0; x < src.cols; ++x)
				for(int c = 0; c < 3; ++c)
				histogram[c][(int)src.at<Vec3b>(y, x)[c]]++;
		drawHist(histogram[0], 'B');
		drawHist(histogram[1], 'G');
		drawHist(histogram[2], 'R');
	}

	


	waitKey(0);
	return 0;
}