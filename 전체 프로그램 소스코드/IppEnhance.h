#pragma once

#include "IppImage.h"

void IppInverse(IppByteImage& img);
void IppBrightness_Contrast(IppByteImage& img, int alpha, int beta);
void IppHistogram(IppByteImage& img, float histo[256]);
IppRgbImage getHistImg(IppByteImage& img);
void IppEverageBlur(IppByteImage& ,int);
void IppGaussianBlur(IppByteImage&, int);
void IppMedianBlur(IppByteImage&, int);
IppRgbImage getLabledImage(IppByteImage&);
void IppSobelEdge(IppByteImage&);
IppRgbImage getHoughCircleImage(IppByteImage&, int, int, int, int);
void IppStretchHistogram(IppByteImage&);
void IppEqualizeHistogram(IppByteImage&);
void IppErode(IppByteImage&, int);
void IppDilate(IppByteImage&, int);