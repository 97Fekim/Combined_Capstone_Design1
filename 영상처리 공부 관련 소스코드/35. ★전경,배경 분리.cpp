#include "header.h"


/*   히스토그램 출력함수 프로토타입   */
void drawHist(const char* name, int histogram[]);

int main()
{

	Mat src, dst;

	src = imread("lenna.jpg", IMREAD_GRAYSCALE);
	imshow("Image", src);
	if (src.empty())return -1;

	Mat threshold_image;
	// 100보다 작으면0, 100보다 크면 255,, 마지막 param을 CV_THRESSH_BINARY | CV_THRESH_OTSU로 바꾸면 향상된 이진화 가능.
	// OTSU를 넣으면 100의 값은 무의미,, 임곗값은 알아서 찾아줌
	threshold(src, threshold_image, 100, 255, THRESH_BINARY|CV_THRESH_OTSU);
	imshow("Threshold Image", threshold_image);



	/*     히스토그램을 출력하는 부분     */

	int histogram_image[256] = { 0 };
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			histogram_image[(int)src.at<uchar>(y, x)]++;
	drawHist("image",histogram_image);



	int histogram_new_image[256] = { 0 };
	for (int y = 0; y < threshold_image.rows; y++)
		for (int x = 0; x < threshold_image.cols; x++)
			histogram_new_image[(int)threshold_image.at<uchar>(y, x)]++;
	drawHist("new image",histogram_new_image);



	waitKey(0);

	return 0;

}

/*     히스토그램 출력함수     */
void drawHist(const char* name, int histogram[])
{
	int hist_w = 780;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);	// 반올림하는 함수.

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));	// 512 x 400 의 8bit 3채널, 흰색바탕 이미지 하나 생성.

	int max = histogram[0];
	for (int i = 0; i < 256; i++)
	{
		if (max < histogram[i])				// 히스토그램의 최댓값을 찾는다.
			max = histogram[i];
	}

	for (int i = 0; i < 256; i++)
	{
		histogram[i] = floor(((double)histogram[i] / max) * histImage.rows);	// 히스토그램의 값이 hist_h보다 커서 초과하는 것 방지, 즉 0~255값으로 정규화
	}

	for (int i = 0; i < 256; i++)
	{
		line(histImage, Point(bin_w * (i), hist_h), Point(bin_w * (i), hist_h - histogram[i]), Scalar(0, 0, 0));	// 책 161p 참고
	}

	imshow(name, histImage);
}