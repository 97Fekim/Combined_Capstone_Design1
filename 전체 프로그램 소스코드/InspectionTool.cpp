#pragma once
#include "stdafx.h"
#include "InspectionTool.h"
#include "ROI_data.h"

/* 메인 검사 함수 */
IppRgbImage InspectionVoid(IppByteImage& img, int int_ratio)
{
	float ratio = (((float)int_ratio) / 100.0f);	// 검사 임계비율 실수형으로 형변환
	Mat src = getIppCloneMat(img);					// 인풋 이미지를 MFC Image 클래스 -> Mat 클래스 로 변환

	/* 결과이미지는 컬러이미지여야 하므로 컬러복사본 생성 */
	Mat src_color = src.clone();					
	cvtColor(src_color, src_color, COLOR_GRAY2BGR);

	/* 엉뚱한 이미지는 검사x, 따라서 예외처리 */
	if ((src.rows < 3095) || (src.cols < 3071))
	{
		IppRgbImage inspection_result = getMatCloneIppColor(src_color);
		AfxMessageBox(_T("Void 검사는 3072 x 3096 해상도의 영상만을 검사 가능합니다."), MB_OK, 0);
		return inspection_result;
	}

	/* 4종류로 세분화된 검사 영역을 각각 개별검사.
	   인자는 1)입력이미지, 2)결과가 쓰여질 컬러이미지,
	   3)검사할 좌표, 4)불량임계비율, 5)최적의 distance_th값 */
	for (int i = 0; i < 24; ++i)
		InspectVoid_bigBall(src, src_color, rect_Big[i], ratio, 7);
	for (int i = 0; i < 54; ++i)
		InspectVoid_smallBall(src, src_color, rect_Small[i], ratio, 12);
	for (int i = 0; i < 16; ++i)
		InspectVoid_thirdBall(src, src_color, rect_Third[i], ratio, 8);
	for (int i = 0; i < 84; ++i)
		InspectVoid_middleBall(src, src_color, rect_Mid[i], ratio, 7, 25);

	IppRgbImage inspection_result = getMatCloneIppColor(src_color);	// Mat 클래스를 MFC에서 출력이 가능한 이미지 클래스로 변환
	
	return inspection_result;	// 최종 결과영상 반환
}

/* 세분화된 검사 함수 */
void InspectVoid_bigBall(Mat Original, Mat& Original_RGB, Rect r, const float& ratio_th, const int distance_th)
{
	bool need_blur = false;			// 잡음제거를 위한 blur 시행 플래그
	int point_otsu = 0;				// 물체와 배경의 중간값
	int point_ballMode = -1;		// point_mode

	/* 이미지 변수들 선언 */
	Mat ROI = Original(r).clone();	
	Mat ROI_temp = ROI.clone();		
	Mat ROI_beforeBlur;				
	Mat ROI_afterBlur;				
	Mat ROI_dst;					

	point_otsu = threshold(ROI_temp, ROI_temp, 0, 255, THRESH_BINARY | THRESH_OTSU);	// 히스토그램 쌍봉의 중간값 찾기

	point_ballMode = get_point_ballMode(ROI, point_otsu);	// point_mode값 탐색

	threshold(ROI, ROI_beforeBlur, point_ballMode + distance_th, 255, THRESH_BINARY);	// 이진화 시행

	/* 잡음 제거 및 최종 이진화 부분 */
	need_blur = judge_need_blur(ROI_beforeBlur,8);	
	if (need_blur)
	{
		GaussianBlur(ROI_beforeBlur, ROI_beforeBlur, Size(3, 3), 0, 0);
		GaussianBlur(ROI_beforeBlur, ROI_beforeBlur, Size(5, 5), 0, 0);
		GaussianBlur(ROI_beforeBlur, ROI_afterBlur, Size(7, 7), 0, 0);

		threshold(ROI_afterBlur, ROI_dst, point_ballMode + distance_th, 255, THRESH_BINARY);
	}
	else
		threshold(ROI_beforeBlur, ROI_dst, point_ballMode + distance_th, 255, THRESH_BINARY);
	
	/* 최종 이진화 영상을 이용하여 결과이미지 그리기 */
	drawToOriginal_RGB(Original_RGB, ROI_dst, r, ratio_th);

}
void InspectVoid_smallBall(Mat Original, Mat& Original_RGB, Rect r, const float& ratio_th, const int distance_th)
{
	int point_otsu = 0;				// 물체와 배경의 중간값
	int point_ballMode = -1;

	Mat ROI = Original(r).clone();
	Mat ROI_temp = ROI.clone();		// point_otsu를 구하기 위한 임시 이미지
	Mat ROI_dst;

	point_otsu = threshold(ROI_temp, ROI_temp, 0, 255, THRESH_BINARY | THRESH_OTSU);	// 히스토그램 쌍봉의 중간값 찾기
	point_ballMode = get_point_ballMode(ROI, point_otsu);	// point_mode 구하기

	threshold(ROI, ROI_dst, point_ballMode + distance_th, 255, THRESH_BINARY);	// 이진화 시행

	drawToOriginal_RGB(Original_RGB, ROI_dst, r, ratio_th);	// 결과이미지 그리기
}
void InspectVoid_thirdBall(Mat Original, Mat& Original_RGB, Rect r, const float& ratio_th, const int distance_th)
{
	int point_otsu;					// 물체와 배경의 중간값
	int point_ballMode = -1;		// point_mode

	Mat ROI = Original(r).clone();
	Mat ROI_temp = ROI.clone();		// point_otsu를 구하기 위한 임시 이미지
	Mat ROI_dst;

	point_otsu = threshold(ROI_temp, ROI_temp, 0, 255, THRESH_BINARY | THRESH_OTSU);	// 히스토그램 쌍봉의 중간값 찾기
	point_ballMode = get_point_ballMode(ROI, point_otsu);	// point_mode 값 찾기

	threshold(ROI, ROI_dst, point_ballMode + distance_th, 255, THRESH_BINARY);	// 이진화 시행
	drawToOriginal_RGB(Original_RGB, ROI_dst, r, ratio_th);	// 검사결과 그리기
}
void InspectVoid_middleBall(Mat Original, Mat& Original_RGB, Rect r, const float& ratio_th, const int distance_th, const int distance_noise2back)
{
	int point_otsu = 0;				// 물체와 배경의 중간값
	int point_ballMode = -1;		// 배경을 제외한 물체의 최빈화소
	
	/* 이미지 변수들 선언 */
	Mat ROI = Original(r).clone();
	Mat ROI_temp = ROI.clone();	
	Mat ROI_whiteBack;
	Mat ROI_dst;

	point_otsu = threshold(ROI_temp, ROI_temp, 0, 255, THRESH_BINARY | THRESH_OTSU);	// 히스토그램 쌍봉의 중간값 찾기

	/* 잡음제거 부분 */
	ROI_whiteBack = getWhiteBackCircle(ROI, point_otsu);
	if ((point_ballMode = get_point_ballMode(ROI_whiteBack, point_otsu)) < point_otsu - distance_noise2back)
		point_ballMode = get_point_ballMode_dnoise(ROI_whiteBack, point_otsu - distance_noise2back, point_otsu);
	
	threshold(ROI_whiteBack, ROI_dst, point_ballMode + distance_th, 255, THRESH_BINARY);	// 이진화 시행
	drawToOriginal_RGB(Original_RGB, ROI_dst, r, ratio_th);		// 결과 그리기
}	

/* point_mode값 탐색 함수 */
int get_point_ballMode(Mat ROI, int point_otsu)
{
	int hist_max = -1;
	int point_ballMode = -1;
	int histogram[256] = { 0 };

	/* 히스토그램 생성 */
	for (int y = 0; y < ROI.rows; y++)
		for (int x = 0; x < ROI.cols; x++)
			histogram[(int)ROI.at<uchar>(y, x)]++;

	/* point_mode 값 탐색 */
	for (int i = 0; i < point_otsu; ++i)
	{
		if (histogram[i] > hist_max)
		{
			hist_max = histogram[i];
			point_ballMode = i;
		}
	}

	return point_ballMode;
}

/* 불량비율 계산 함수 */
float getRatio(Mat ROI_dst)
{
	Mat lables, stats, centroids;
	int sum_solder = 0;
	int sum_void = 0;

	/* 이미지 레이블링 시행 */
	int n = connectedComponentsWithStats(ROI_dst, lables, stats, centroids);

	vector<Vec3b> colors(n);
	for (int i = 0; i < n; ++i)
		colors[i] = Vec3b(i, i, i);

	Mat ROI_RGB = Mat::zeros(ROI_dst.size(), CV_8UC3);

	/* 레이블 넘버별 색으로 채워진 영상 생성 */
	for (int y = 0; y < ROI_RGB.rows; y++)
		for (int x = 0; x < ROI_RGB.cols; x++)
		{
			int label = lables.at<int>(y, x);
			ROI_RGB.at<Vec3b>(y, x) = colors[label];
		}

	/* 영상의 화소갯수 계산 */
	for (int y = 0; y < ROI_RGB.rows; y++)
	{
		for (int x = 0; x < ROI_RGB.cols; x++)
		{
			if (ROI_RGB.at<Vec3b>(y, x) == colors[0])
				sum_solder += 1;
			else if (ROI_RGB.at<Vec3b>(y, x) == colors[1])
				;
			else
				sum_void += 1;
		}
	}
	/* void 비율 계산 */
	float ratio = (float)sum_void / float(sum_void + sum_solder);

	return ratio;	// 불량 비율 반환
}

/* big ball의 잡음여부 판단 함수 */
bool judge_need_blur(Mat ROI_beforeBlur, const int& th_val)
{
	Mat lables, stats, centroids;

	/* 레이블링 시행 */
	int n = connectedComponentsWithStats(ROI_beforeBlur, lables, stats, centroids);

	/* 라벨의 갯수가 비정상적으로 높다면 플래그 올림 */
	if (n > th_val)
		return true;
	else
		return false;
}

/* object의 경계선 추출 함수 */
Mat getGradadient(Mat ROI_dst)
{
	int scale = 1; int delta = 0;
	Mat grad, grad_x, grad_y, abs_grad_x, abs_grad_y;

	/* sobel edge detecting을 이용하여 경계선 추출 */
	Sobel(ROI_dst, grad_x, CV_16S, 1, 0, 1, scale, delta, BORDER_DEFAULT);
	Sobel(ROI_dst, grad_y, CV_16S, 0, 1, 1, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	return grad;
}

/* 불량비율 출력을 위한 float -> 문자열 변환 함수 */
char* getRatioString(float ratio)
{
	/* 결함비율을 "00.00"의 format으로 출력하기 위해 
	float -> string으로 바꾸는 알고리즘 */
	int rat[4] = { 0 };
	ratio *= 100;

	rat[0] = (int)ratio / 10;
	rat[1] = ((int)ratio % 10);
	rat[2] = (int)(ratio * 10.0) % 10;
	rat[3] = (int)(ratio * 100.0) % 10;
	static char str[6] = { NULL };
	str[0] = rat[0] + 48;
	str[1] = rat[1] + 48;
	str[2] = '.';
	str[3] = rat[2] + 48;
	str[4] = rat[3] + 48;

	return str;
}

/* 검사결과 이미지 그리기 함수 */
void drawToOriginal_RGB(Mat Original_RGB, Mat ROI_dst, Rect r, float ratio_th)
{
	Mat grad;
	float ratio = 0.0f;
	char str_ratio[6] = { NULL };

	ratio = getRatio(ROI_dst);			// 불량 비율 계산
	grad = getGradadient(ROI_dst);		// 경계선 추출
	strcpy_s(str_ratio, getRatioString(ratio));	// 불량 비율을 검사 결과에 출력을 위해 string으로 변환

	/* ROI 표시 */
	rectangle(Original_RGB, Point(r.x, r.y), Point(r.x + r.width, r.y + r.height), Scalar(200, 200, 200), 2);	

	/* 불량 비율이 임곗값보다 낮은경우(정상인경우) */
	if (ratio < ratio_th)
	{
		putText(Original_RGB, str_ratio, Point(r.x + r.width / 12, r.y + (r.height * 10) / 11), FONT_HERSHEY_PLAIN, 1, Scalar(10, 10, 10), 0.7);

		/* 추출한 경계선을 이용하여 결과그리기 */
		for (int row = r.x; row < r.x + r.width; row++)
			for (int col = r.y; col < r.y + r.height; col++)
			{
				if (grad.at<uchar>(col - r.y, row - r.x) != 0)
					circle(Original_RGB, Point(row, col), 0.5, Scalar(0, 255, 0), 0.5);
			}
	}/* 불량 비율이 임곗값보다 높은경우(불량인경우) */
	else
	{
		char defect[5] = "VOID";
		putText(Original_RGB, defect, Point(r.x, r.y), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 0.7);
		putText(Original_RGB, str_ratio, Point(r.x + r.width / 12, r.y + (r.height * 10) / 11), FONT_HERSHEY_PLAIN, 1, Scalar(10, 10, 10), 0.7);

		/* 추출한 경계선을 이용하여 결과 그리기 */
		for (int row = r.x; row < r.x + r.width; row++)
			for (int col = r.y; col < r.y + r.height; col++)
			{
				if (grad.at<uchar>(col - r.y, row - r.x) != 0)
					circle(Original_RGB, Point(row, col), 0.5, Scalar(0, 0, 255), 0.5);
			}
	}
}

/* mid ball의 잡음제거 함수1 */
Mat getWhiteBackCircle(Mat ROI,int point_otsu)
{
	Mat ROI_whiteBack = ROI.clone();

	Mat ROI_beforeFitCircle;
	Mat ROI_Gaussianed;

	Mat ROI_BGR;
	cvtColor(ROI, ROI_BGR, COLOR_GRAY2BGR);

	Mat mask = ROI_BGR.clone();
	mask = Scalar(255, 255, 255);

	vector<Vec3f> circles;


	threshold(ROI, ROI_beforeFitCircle, point_otsu, 255, THRESH_BINARY_INV);

	GaussianBlur(ROI_beforeFitCircle, ROI_Gaussianed, Size(3, 3), 2, 2);
	GaussianBlur(ROI_Gaussianed, ROI_Gaussianed, Size(5, 5), 2, 2);
	
	HoughCircles(ROI_Gaussianed, circles, HOUGH_GRADIENT, 1, ROI.rows, 200, 6, (int)(ROI.rows / 4), (int)((double)ROI.rows / 2.5));

	for (size_t i = 0; i < circles.size(); ++i)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(mask, center, radius, Scalar(0, 0, 0), -1, 8, 0);
	}

	cvtColor(mask, mask, COLOR_BGR2GRAY);

	bool flag = true;
	for (int y = 0; y < mask.rows; y++)
		for (int x = 0; x < mask.cols; x++)
		{
			if (!mask.at<uchar>(y, x))
				flag = false;
		}

	if (flag)
		return ROI_whiteBack;


	for (int y = 0; y < mask.rows; y++)
		for (int x = 0; x < mask.cols; x++)
		{
			if (mask.at<uchar>(y, x))
				ROI_whiteBack.at<uchar>(y, x) = 255;
		}

	return ROI_whiteBack;
}

/* mid ball의 잡음제거 함수2 */
int get_point_ballMode_dnoise(Mat ROI_whiteBack, int start_point, int point_otsu)
{

	int hist_max = -1;
	int point_ballMode = -1;
	int histogram[256] = { 0 };

	for (int y = 0; y < ROI_whiteBack.rows; y++)
		for (int x = 0; x < ROI_whiteBack.cols; x++)
			histogram[(int)ROI_whiteBack.at<uchar>(y, x)]++;

	for (int i = start_point; i < point_otsu; ++i)
	{
		if (hist_max < histogram[i])
		{
			hist_max = histogram[i];
			point_ballMode = i;
		}
	}
	return point_ballMode;
}

/* MFC의 이미지 클래스와 Mat 클래스 변환을 위한 함수 둘 */
Mat getIppCloneMat(IppByteImage& img)
{
	int cols = img.GetWidth();
	int rows = img.GetHeight();
	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	/* MFC 이미지 클래스 > Mat 클래스 변환 */
	for (int row = 0; row < rows; ++row)
		for (int col = 0; col < cols; ++col)
		{
			src.at<uchar>(row, col) = p[row][col];
		}
	return src;
}
IppRgbImage getMatCloneIppColor(Mat& src_color)
{
	IppRgbImage color_image;
	color_image.CreateImage(src_color.cols, src_color.rows);

	/* Mat 클래스를 출력이 가능한 MFC 이미지로 변환 */
	RGBBYTE** P_RGB = color_image.GetPixels2D();
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

	return color_image;
}
