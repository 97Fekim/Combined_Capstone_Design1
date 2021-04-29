#include "header.h"
/* 메인함수에서 화소처리*/
//int main()
//{
//	Mat img = imread("lenna.jpg", IMREAD_GRAYSCALE);
//	imshow("Original image", img);
//
//	for (int r = 0; r < img.rows; r++)
//		for (int c = 0; c < img.cols; ++c)
//			img.at<uchar>(r, c) = saturate_cast<uchar>(img.at<uchar>(r, c) + 30);
//
//	imshow("New image", img);
//	waitKey(0);
//
//	return 0;
//
//}

// 화소의 값을 변경할 때에는 at() 함수를 사용하여 화소의 자료형과 좌표를 전달받는다.
// 하지만 이경우 오버플로우가 일어나서 검은색 화면이 발생한다.  
// 그래서 saturate_cast() 함수를 사용한다. 이 경우에는 255가 넘으면 255로 고정시킨다.
// ex) 
// uchar u1 = 257; >> u1 = 이 된다.
// uchar u2 = saturate_cast<uchar>(257); >> u2 = 255 가 된다.


/* 함수정의를 이용한 밝기 조정 */
void brighten(Mat& img, int value)		// 함수에서 img를 받을때는 객체의 주소를 받으면 된다.
{
	for (int r = 0; r < img.rows; r++) 
	{
		for (int c = 0; c < img.cols; ++c)
			img.at<uchar>(r, c) = saturate_cast<uchar>(img.at<uchar>(r, c) + value);
	}
}

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
	Mat img = imread("미싱x.jpg", IMREAD_GRAYSCALE);
	imshow("원본", img);

	for (int r = 0; r < img.rows; r++)
	{
		for (int c = 0; c < img.cols; ++c)
			if (img.at<uchar>(r, c) > 45)
				img.at<uchar>(r, c) = 255;
	}

	imwrite("to_ppt.bmp", img);

	int histogram[256] = { 0 };
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++)
			histogram[(int)img.at<uchar>(y, x)]++;		// 히스토그램을 계산한다.
	drawHist(histogram, 'K');

	imshow("조정", img);

	waitKey(0);
	return 0;



}