/******************************************************************************
*
* IppSegment.h
*
* Copyright (c) 2015~<current> by Sun-Kyoo Hwang <sunkyoo.ippbook@gmail.com>
*
* This source code is included in the book titled "Image Processing
* Programming By Visual C++ (2nd Edition)"
*
******************************************************************************/

#pragma once

#include <vector>
#include "IppImage.h"
#include "IppFeature.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class IppLabelInfo
{
public:
	std::vector<IppPoint> pixels;
	int cx, cy;
	int minx, miny, maxx, maxy;

public:

};

void IppBinarization(IppByteImage& imgSrc, IppByteImage& imgDst, int threshold);
int  IppBinarizationIterative(IppByteImage& imgSrc);
void IppThreshold_adaptiveMean(IppByteImage&);
void IppThreshold_adaptiveGaussian(IppByteImage&);
void IppThreshold_otsu(IppByteImage&);