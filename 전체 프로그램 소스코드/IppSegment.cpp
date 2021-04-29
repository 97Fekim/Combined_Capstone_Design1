/******************************************************************************
*
* IppSegment.cpp
*
* Copyright (c) 2015~<current> by Sun-Kyoo Hwang <sunkyoo.ippbook@gmail.com>
*
* This source code is included in the book titled "Image Processing
* Programming By Visual C++ (2nd Edition)"
*
*****************************************************************************/
#pragma once
#include "StdAfx.h"
#include "IppSegment.h"
#include "IppEnhance.h"
#include <map>

void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold)
{
	imgDst.CreateImage(imgSrc.GetWidth(), imgSrc.GetHeight());

	int size = imgSrc.GetSize();
	BYTE* pSrc = imgSrc.GetPixels();
	BYTE* pDst = imgDst.GetPixels();

	for (int i = 0; i < size; i++)
	{
		pDst[i] = (pSrc[i] <= threshold) ? 0 : 255;
	}
}

int IppBinarizationIterative(IppByteImage& imgSrc)
{
	float hist[256] = { 0, };
	IppHistogram(imgSrc, hist); // ����ȭ�� ������׷�. hist �迭�� ������ [0, 1].

	// �ʱ� �Ӱ谪 ���� - �׷��̽����� ���� ��ü ���

	int i, T, Told;

	float sum = 0.f;
	for (i = 0; i < 256; i++)
		sum += (i * hist[i]);

	T = static_cast<int>(sum + .5f);

	// �ݺ��� ���� �Ӱ谪 ����

	float a1, b1, u1, a2, b2, u2;
	do {
		Told = T;

		a1 = b1 = u1 = 0.f;
		for (i = 0; i <= Told; i++)
		{
			a1 += (i*hist[i]);
			b1 += hist[i];
		}

		if (b1 != 0.f)
			u1 = a1 / b1;

		a2 = b2 = u2 = 0.f;
		for (i = Told + 1; i < 256; i++)
		{
			a2 += (i*hist[i]);
			b2 += hist[i];
		}

		if (b2 != 0.f)
			u2 = a2 / b2;

		T = static_cast<int>((u1 + u2) / 2 + 0.5f);
	} while (T != Told);

	return T;
}


void IppThreshold_adaptiveMean(IppByteImage& img)
{
	/* �Է¿��� -> Mat ��ȯ�� �Դϴ�. */
	int cols = img.GetWidth();
	int rows = img.GetHeight();

	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}

	adaptiveThreshold(src, src, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2);

	/* ��� �������� ��ȯ�� �Դϴ�. */
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}

}

void IppThreshold_adaptiveGaussian(IppByteImage& img)
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

	adaptiveThreshold(src, src, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);

	/* ��� �������� ��ȯ�� �Դϴ�. */
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}

}

void IppThreshold_otsu(IppByteImage& img)
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

	threshold(src, src, 0, 255, THRESH_BINARY | THRESH_OTSU);

	/* ��� �������� ��ȯ�� �Դϴ�. */
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			p[row][col] = src.at<uchar>(row, col);
		}


}