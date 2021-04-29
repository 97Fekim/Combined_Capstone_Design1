#include "header.h"

// // 히스토그램 출력 프로토타입.
//void drawHist1(int histogram[]);
//void drawHist2(int histogram[]);
void printHist(Mat src, const char * w_name)
{
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

	imshow(w_name, histImage);
}

int main()
{
	Mat src = imread("ksc1.jpg", IMREAD_COLOR);
	if (src.empty())return-1;

	vector<Mat> bgr_planes;
	split(src, bgr_planes);


	for (Mat plane : bgr_planes)
		equalizeHist(plane, plane);
		
	Mat dst;
	merge(bgr_planes, dst);

	imshow("img_src", src);
	imshow("img_dst", dst);

	printHist(src, "hist_src");
	printHist(dst, "hist_dst");


	/*Mat dst;

	equalizeHist(src, dst);
	imshow("원본", src);
	imshow("평활화", dst);*/

	/*int histogram_src[256] = { 0 };
	int histogram_dst[256] = { 0 };

	
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			histogram_src[(int)src.at<uchar>(y, x)]++;

	for (int y = 0; y < dst.rows; y++)
		for (int x = 0; x < dst.cols; x++)
			histogram_dst[(int)dst.at<uchar>(y, x)]++;

	drawHist1(histogram_src);
	drawHist2(histogram_dst);*/


	waitKey(0);
	return 0;
}




// //히스토그램 출력 바디
//void drawHist1(int histogram[])
//{
//	int hist_w = 512;
//	int hist_h = 400;
//	int bin_w = cvRound((double)hist_w / 256);	// 반올림하는 함수.
//
//	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));	// 512 x 400 의 8bit 3채널, 흰색바탕 이미지 하나 생성.
//
//	int max = histogram[0];
//	for (int i = 0; i < 255; i++)
//	{
//		if (max < histogram[i])				// 히스토그램의 최댓값을 찾는다.
//			max = histogram[i];
//	}
//
//	for (int i = 0; i < 255; i++)
//	{
//		histogram[i] = floor(((double)histogram[i] / max) * histImage.rows);	// 히스토그램의 값이 hist_h보다 커서 초과하는 것 방지, 즉 0~255값으로 정규화
//	}
//
//	for (int i = 0; i < 255; i++)
//	{
//		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - histogram[i]), Scalar(0, 0, 255));	// 책 161p 참고
//	}
//
//	imshow("histogram1", histImage);
//}
//
//void drawHist2(int histogram[])
//{
//	int hist_w = 512;
//	int hist_h = 400;
//	int bin_w = cvRound((double)hist_w / 256);	// 반올림하는 함수.
//
//	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));	// 512 x 400 의 8bit 3채널, 흰색바탕 이미지 하나 생성.
//
//	int max = histogram[0];
//	for (int i = 0; i < 255; i++)
//	{
//		if (max < histogram[i])				// 히스토그램의 최댓값을 찾는다.
//			max = histogram[i];
//	}
//
//	for (int i = 0; i < 255; i++)
//	{
//		histogram[i] = floor(((double)histogram[i] / max) * histImage.rows);	// 히스토그램의 값이 hist_h보다 커서 초과하는 것 방지, 즉 0~255값으로 정규화
//	}
//
//	for (int i = 0; i < 255; i++)
//	{
//		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - histogram[i]), Scalar(0, 0, 255));	// 책 161p 참고
//	}
//
//	imshow("histogram2", histImage);
//}