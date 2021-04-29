#pragma once
#include "IppImage.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

IppRgbImage InspectionVoid(IppByteImage& img,int);
void InspectVoid_bigBall(Mat, Mat&, Rect, const float&, const int);
void InspectVoid_smallBall(Mat, Mat&, Rect, const float&, const int);
void InspectVoid_thirdBall(Mat, Mat&, Rect, const float&, const int);
void InspectVoid_middleBall(Mat, Mat&, Rect, const float&, const int, const int);

Mat getIppCloneMat(IppByteImage& img);
bool judge_need_blur(Mat, const int&);
int get_point_ballMode(Mat,int);
float getRatio(Mat);
Mat getGradadient(Mat);
char* getRatioString(float);
void drawToOriginal_RGB(Mat, Mat, Rect, float);
IppRgbImage getMatCloneIppColor(Mat& src_color);

/* Third ball에서만 사용하는 함수입니다. */
Mat getWhiteBackCircle(Mat, int);
int get_point_ballMode_dnoise(Mat, int, int);