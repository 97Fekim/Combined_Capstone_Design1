#pragma once
#include "stdafx.h"
#include "IppEnhance.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;



void IppInverse(IppByteImage &img)
{
	
	BYTE** p = img.GetPixels2D();

	int cols = img.GetWidth();
	int rows = img.GetHeight();

	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row,col) = 255 - p[row][col];
		}

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}
}

void IppBrightness_Contrast(IppByteImage& img, int alpha, int beta)
{
	int cols = img.GetWidth();
	int rows = img.GetHeight();

	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);
	
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}
	
	float alpha2 = alpha;

	src.convertTo(src, -1, 1+alpha2/100, beta);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}
}

void IppHistogram(IppByteImage& img, float histo[256])
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	int cnt[256];
	memset(cnt, 0, sizeof(int) * 256);

	for (int i = 0; i < size; ++i)
		cnt[p[i]]++;

	for (int i = 0; i < 256; ++i)
	{
		histo[i] = static_cast<float>(cnt[i]) / size;
	}
}

IppRgbImage getHistImg(IppByteImage& img)
{
	/* 입력영상 Mat 클래스로 변환부 입니다. */
	int cols = img.GetWidth();
	int rows = img.GetHeight();
	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}
		

	/* 히스토그램 이미지 생성부 입니다.*/
	/* -------------------------------- */
	int histogram[256] = {0};

	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			histogram[(int)src.at<uchar>(y, x)]++;

	int hist_h = 400;
	Mat histimg(hist_h, 512, CV_8UC3, Scalar(255, 255, 255));

	Scalar color = Scalar(200,0,200);

	int max = -30;
	for (int i = 0; i < 256; i++)
		if (max < histogram[i])
			max = histogram[i];

	for (int i = 0; i < 256; i++)
		histogram[i] = floor(((double)histogram[i] / max) * hist_h);

	for (int i = 0; i < 256; i++)
		line(histimg, Point(2 * i, hist_h), Point(2 * i, hist_h - histogram[i]), color);
	/* ---------------------------------- */


	/* 출력영상으로 변환부 입니다. */
	IppRgbImage RGB_O;
	RGB_O.CreateImage(histimg.cols, histimg.rows);
	RGBBYTE** P_RGB = RGB_O.GetPixels2D();

	{
		int c = 0;
		for (int row = 0; row < histimg.rows; row++)
		{
			for (int col = 0; col < histimg.cols; col++)
			{
				P_RGB[row][col].b = histimg.at<Vec3b>(row, col)[c];
			}
		}

		c = 1;
		for (int row = 0; row < histimg.rows; row++)
		{
			for (int col = 0; col < histimg.cols; col++)
			{
				P_RGB[row][col].g = histimg.at<Vec3b>(row, col)[c];
			}
		}

		c = 2;
		for (int row = 0; row < histimg.rows; row++)
		{
			for (int col = 0; col < histimg.cols; col++)
			{
				P_RGB[row][col].r = histimg.at<Vec3b>(row, col)[c];
			}
		}
	}

	return RGB_O;
}

void IppEverageBlur(IppByteImage& img, int size)
{
	int cols = img.GetWidth();
	int rows = img.GetHeight();

	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);
	
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}

	blur(src, src, Size(size, size));

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}
}

void IppGaussianBlur(IppByteImage& img, int size)
{
	int cols = img.GetWidth();
	int rows = img.GetHeight();

	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}

	GaussianBlur(src, src, Size(size, size), 2, 2);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}
}

void IppMedianBlur(IppByteImage& img, int size)
{
	int cols = img.GetWidth();
	int rows = img.GetHeight();

	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}

	medianBlur(src, src, size);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}

}

IppRgbImage getLabledImage(IppByteImage& img)
{
	/* 인풋영상 -> Mat 변환부 입니다. */
	int cols = img.GetWidth();
	int rows = img.GetHeight();
	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}


	/* 레이블링 알고리즘 실현부 입니다. */
	Mat dst, lables, centroids, stats;
	int n = connectedComponentsWithStats(src, lables, stats, centroids);
	printf("Lable number : %d\n", n);
	vector<Vec3b> colors(n + 1);
	colors[0] = Vec3b(0, 0, 0);

	for (int i = 1; i <= n; i++)
		colors[i] = Vec3b(rand() % 256, rand() % 256, rand() % 256);

	dst = Mat::zeros(src.size(), CV_8UC3);

	for (int y = 0; y < dst.rows; y++)
		for (int x = 0; x < dst.cols; x++)
		{
			int lable = lables.at<int>(y, x);
			dst.at<Vec3b>(y, x) = colors[lable];
		}

	/* 출력영상으로 변환부 입니다. */
	IppRgbImage RGB_O;
	RGB_O.CreateImage(dst.cols, dst.rows);
	RGBBYTE** P_RGB = RGB_O.GetPixels2D();

	{
		int c = 0;
		for (int row = 0; row < dst.rows; row++)
		{
			for (int col = 0; col < dst.cols; col++)
			{
				P_RGB[row][col].b = dst.at<Vec3b>(row, col)[c];
			}
		}

		c = 1;
		for (int row = 0; row < dst.rows; row++)
		{
			for (int col = 0; col < dst.cols; col++)
			{
				P_RGB[row][col].g = dst.at<Vec3b>(row, col)[c];
			}
		}

		c = 2;
		for (int row = 0; row < dst.rows; row++)
		{
			for (int col = 0; col < dst.cols; col++)
			{
				P_RGB[row][col].r = dst.at<Vec3b>(row, col)[c];
			}
		}
	}

	return RGB_O;
}

void IppSobelEdge(IppByteImage& img)
{
	/* 입력영상 -> Mat 변환부 입니다. */
	int cols = img.GetWidth();
	int rows = img.GetHeight();

	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);
	
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}

	/* 엣지검출 알고리즘 실현부입니다. */
	int scale = 1;
	int delta = 0;
	Mat grad;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	Sobel(src, grad_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	Sobel(src, grad_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, src);

	/* 출력 영상으로 변환부 입니다. */
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}

}

IppRgbImage getHoughCircleImage(IppByteImage& img, int accuracy, int Circle2Circle, int min_radius, int max_radius)
{
	/* 인풋영상 -> Mat 변환부 입니다. */
	int cols = img.GetWidth();
	int rows = img.GetHeight();
	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}

	Mat src_color = src.clone();
	cvtColor(src_color, src_color, COLOR_GRAY2BGR);

	/* 허프서클 알고리즘 구현부 입니다. */
	vector<Vec3f> circles;
	HoughCircles(src, circles, HOUGH_GRADIENT, 1, (double(Circle2Circle) / 100.0f)*src.rows, 200, accuracy, 
		(int)(((float)min_radius / 100.0f) * (float)src.rows), (int)(((float)max_radius / 100.0f) * (float)src.rows));
	
	printf("pixel distance of Circle center to other center : %lf pixel\n", (double(Circle2Circle) / 100.0f)*src.rows);
	printf("pixel distance of Circle's min radius : %d pixel\n", (int)(((float)min_radius / 100.0f) * (float)src.rows));
	printf("pixel distance of Circle's max radius : %d pixel\n\n", (int)(((float)max_radius / 100.0f) * (float)src.rows));

	for (size_t i = 0; i < circles.size(); ++i)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(src_color, center, radius, Scalar(0, 0, 255), 2, 8, 0);
	}

	/* 출력영상으로의 변환부 입니다. */
	IppRgbImage RGB_O;
	RGB_O.CreateImage(src_color.cols, src_color.rows);
	RGBBYTE** P_RGB = RGB_O.GetPixels2D();


	{
		int c = 0;
		for (int row = 0; row < src_color.rows; row++)
		{
			for (int col = 0; col < src_color.cols; col++)
			{
				P_RGB[row][col].b = src_color.at<Vec3b>(row, col)[c];
			}
		}

		c = 1;
		for (int row = 0; row < src_color.rows; row++)
		{
			for (int col = 0; col < src_color.cols; col++)
			{
				P_RGB[row][col].g = src_color.at<Vec3b>(row, col)[c];
			}
		}

		c = 2;
		for (int row = 0; row < src_color.rows; row++)
		{
			for (int col = 0; col < src_color.cols; col++)
			{
				P_RGB[row][col].r = src_color.at<Vec3b>(row, col)[c];
			}
		}
	}

	return RGB_O;

}

void IppStretchHistogram(IppByteImage& img)
{
	int size = img.GetSize();
	BYTE* p = img.GetPixels();

	// 최대, 최소 그레이스케일 값 계산
	BYTE gray_max, gray_min;
	gray_max = gray_min = p[0];
	for (int i = 1; i < size; i++)
	{
		if (gray_max < p[i]) gray_max = p[i];
		if (gray_min > p[i]) gray_min = p[i];
	}

	if (gray_max == gray_min)
		return;

	// 히스토그램 스트레칭
	for (int i = 0; i < size; i++)
	{
		p[i] = (p[i] - gray_min) * 255 / (gray_max - gray_min);
	}
}

void IppEqualizeHistogram(IppByteImage& img)
{
	/* 입력영상 -> Mat 변환부 입니다. */
	int cols = img.GetWidth();
	int rows = img.GetHeight();

	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}

	equalizeHist(src, src);
	
	/* 출력 영상으로 변환부 입니다. */
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}

}

void IppErode(IppByteImage& img, int size)
{
	int cols = img.GetWidth();
	int rows = img.GetHeight();

	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}

	Mat element = getStructuringElement(MORPH_RECT, Size(size, size), Point(-1, -1));

	erode(src, src, element);

	/* 출력 영상으로 변환부 입니다. */
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}
}

void IppDilate(IppByteImage& img, int size)
{
	int cols = img.GetWidth();
	int rows = img.GetHeight();

	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}

	Mat element = getStructuringElement(MORPH_RECT, Size(size, size), Point(-1, -1));

	dilate(src, src, element);

	/* 출력 영상으로 변환부 입니다. */
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}
}

