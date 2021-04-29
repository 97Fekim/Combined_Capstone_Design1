#include "header.h"



int main(int argc, char** argv)
{
	Mat src = imread("lenna.jpg", IMREAD_COLOR);

	vector<Mat> bgr_planes;			// b,g,r 의 벡터 하나 생성, 
	split(src, bgr_planes);			// src를 b,g,r 별로 쪼개 bgr_planes의 3개의 마스크에 저장.
	int histSize = 256;				// 256개의 사이즈 변수 생성
	float range[] = { 0, 256 };		// 
	const float* histRange = { range };	//	여기는 진짜 모르겠다.
	bool uniform = true, accumulate = false;	// 
	Mat b_hist, g_hist, r_hist;		// 히스토그램이 저장 될 빨,파,초 별 마스크 생성

	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);	// b_hist 에 히스토그램이 저장.
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	int hist_w = 512;
	int hist_h = 400;											// 가로 세로 결정		
	int bin_w = cvRound((double)hist_w / histSize);				// 각각의 선들의 크기 지정
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));	// 히스토그램 출력 될 창 생성

	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());		// 화면을 넘어가지 않게 정규화
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 0; i < 255; i++) 
	{
		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - b_hist.at<float>(i)), Scalar(255, 0, 0));
		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - g_hist.at<float>(i)), Scalar(0, 255, 0));		// 히스토그램 출력
		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - r_hist.at<float>(i)), Scalar(0, 0, 255));
	}
	
	imshow("Histogram", histImage);

	waitKey(0);
	return 0;

}