#include "header.h"

// 히스토그램을 출력하는 함수, 맨 아래에 있음
//void drawHist(int histogram[]);
//void drawHist2(int histogram[]);

int stretch(int x, int r1, int s1, int r2, int s2)
{
	float result;
	if (0 <= x && x <= r1)
		result = s1 / r1 * x;
	else if (r1 < x && x <= r2)
		result = ((s2 - s1) / (r2 - r1)) * (x - r1) + s1;
	else if (r2 < x && x <= 255)
		result = ((255 - s2) / (255 - r2)) * (x - r2) + s2;

	return result;
}

int main()
{
	Mat image = imread("fekim.jpg");
	Mat new_image = image.clone();
	int histogram_image[256] = { 0 };
	int histogram_new_image[256] = { 0 };
	int r1, r2, s1, s2;

	cout << "r1을 입력하세요"; cin >> r1;
	cout << "r2을 입력하세요"; cin >> r2;
	cout << "s1을 입력하세요"; cin >> s1;
	cout << "s2을 입력하세요"; cin >> s2;

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				int output = stretch(image.at<Vec3b>(y, x)[c], r1, s1, r2, s2);
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(output);
			}
		}
	}


	imshow("입력영상", image);
	imshow("출력영상", new_image);


	// 원본, 스트레칭 영상의 히스토그램 계산과 출력
	/*for (int y = 0; y < image.rows; y++)
		for (int x = 0; x < image.cols; x++)
			histogram_image[(int)image.at<uchar>(y, x)]++;

	for (int y = 0; y < new_image.rows; y++)
		for (int x = 0; x < new_image.cols; x++)
			histogram_new_image[(int)new_image.at<uchar>(y, x)]++;

	drawHist(histogram_new_image);
	drawHist2(histogram_new_image);*/

	waitKey(0);
	return 0;
}


//void drawHist(int histogram[])
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
//	imshow("histogram", histImage);
//}


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
