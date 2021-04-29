#pragma once
#include "stdafx.h"
#include "InspectionTool.h"
#include "ROI_data.h"

/* ���� �˻� �Լ� */
IppRgbImage InspectionVoid(IppByteImage& img, int int_ratio)
{
	float ratio = (((float)int_ratio) / 100.0f);	// �˻� �Ӱ���� �Ǽ������� ����ȯ
	Mat src = getIppCloneMat(img);					// ��ǲ �̹����� MFC Image Ŭ���� -> Mat Ŭ���� �� ��ȯ

	/* ����̹����� �÷��̹������� �ϹǷ� �÷����纻 ���� */
	Mat src_color = src.clone();					
	cvtColor(src_color, src_color, COLOR_GRAY2BGR);

	/* ������ �̹����� �˻�x, ���� ����ó�� */
	if ((src.rows < 3095) || (src.cols < 3071))
	{
		IppRgbImage inspection_result = getMatCloneIppColor(src_color);
		AfxMessageBox(_T("Void �˻�� 3072 x 3096 �ػ��� ������ �˻� �����մϴ�."), MB_OK, 0);
		return inspection_result;
	}

	/* 4������ ����ȭ�� �˻� ������ ���� �����˻�.
	   ���ڴ� 1)�Է��̹���, 2)����� ������ �÷��̹���,
	   3)�˻��� ��ǥ, 4)�ҷ��Ӱ����, 5)������ distance_th�� */
	for (int i = 0; i < 24; ++i)
		InspectVoid_bigBall(src, src_color, rect_Big[i], ratio, 7);
	for (int i = 0; i < 54; ++i)
		InspectVoid_smallBall(src, src_color, rect_Small[i], ratio, 12);
	for (int i = 0; i < 16; ++i)
		InspectVoid_thirdBall(src, src_color, rect_Third[i], ratio, 8);
	for (int i = 0; i < 84; ++i)
		InspectVoid_middleBall(src, src_color, rect_Mid[i], ratio, 7, 25);

	IppRgbImage inspection_result = getMatCloneIppColor(src_color);	// Mat Ŭ������ MFC���� ����� ������ �̹��� Ŭ������ ��ȯ
	
	return inspection_result;	// ���� ������� ��ȯ
}

/* ����ȭ�� �˻� �Լ� */
void InspectVoid_bigBall(Mat Original, Mat& Original_RGB, Rect r, const float& ratio_th, const int distance_th)
{
	bool need_blur = false;			// �������Ÿ� ���� blur ���� �÷���
	int point_otsu = 0;				// ��ü�� ����� �߰���
	int point_ballMode = -1;		// point_mode

	/* �̹��� ������ ���� */
	Mat ROI = Original(r).clone();	
	Mat ROI_temp = ROI.clone();		
	Mat ROI_beforeBlur;				
	Mat ROI_afterBlur;				
	Mat ROI_dst;					

	point_otsu = threshold(ROI_temp, ROI_temp, 0, 255, THRESH_BINARY | THRESH_OTSU);	// ������׷� �ֺ��� �߰��� ã��

	point_ballMode = get_point_ballMode(ROI, point_otsu);	// point_mode�� Ž��

	threshold(ROI, ROI_beforeBlur, point_ballMode + distance_th, 255, THRESH_BINARY);	// ����ȭ ����

	/* ���� ���� �� ���� ����ȭ �κ� */
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
	
	/* ���� ����ȭ ������ �̿��Ͽ� ����̹��� �׸��� */
	drawToOriginal_RGB(Original_RGB, ROI_dst, r, ratio_th);

}
void InspectVoid_smallBall(Mat Original, Mat& Original_RGB, Rect r, const float& ratio_th, const int distance_th)
{
	int point_otsu = 0;				// ��ü�� ����� �߰���
	int point_ballMode = -1;

	Mat ROI = Original(r).clone();
	Mat ROI_temp = ROI.clone();		// point_otsu�� ���ϱ� ���� �ӽ� �̹���
	Mat ROI_dst;

	point_otsu = threshold(ROI_temp, ROI_temp, 0, 255, THRESH_BINARY | THRESH_OTSU);	// ������׷� �ֺ��� �߰��� ã��
	point_ballMode = get_point_ballMode(ROI, point_otsu);	// point_mode ���ϱ�

	threshold(ROI, ROI_dst, point_ballMode + distance_th, 255, THRESH_BINARY);	// ����ȭ ����

	drawToOriginal_RGB(Original_RGB, ROI_dst, r, ratio_th);	// ����̹��� �׸���
}
void InspectVoid_thirdBall(Mat Original, Mat& Original_RGB, Rect r, const float& ratio_th, const int distance_th)
{
	int point_otsu;					// ��ü�� ����� �߰���
	int point_ballMode = -1;		// point_mode

	Mat ROI = Original(r).clone();
	Mat ROI_temp = ROI.clone();		// point_otsu�� ���ϱ� ���� �ӽ� �̹���
	Mat ROI_dst;

	point_otsu = threshold(ROI_temp, ROI_temp, 0, 255, THRESH_BINARY | THRESH_OTSU);	// ������׷� �ֺ��� �߰��� ã��
	point_ballMode = get_point_ballMode(ROI, point_otsu);	// point_mode �� ã��

	threshold(ROI, ROI_dst, point_ballMode + distance_th, 255, THRESH_BINARY);	// ����ȭ ����
	drawToOriginal_RGB(Original_RGB, ROI_dst, r, ratio_th);	// �˻��� �׸���
}
void InspectVoid_middleBall(Mat Original, Mat& Original_RGB, Rect r, const float& ratio_th, const int distance_th, const int distance_noise2back)
{
	int point_otsu = 0;				// ��ü�� ����� �߰���
	int point_ballMode = -1;		// ����� ������ ��ü�� �ֺ�ȭ��
	
	/* �̹��� ������ ���� */
	Mat ROI = Original(r).clone();
	Mat ROI_temp = ROI.clone();	
	Mat ROI_whiteBack;
	Mat ROI_dst;

	point_otsu = threshold(ROI_temp, ROI_temp, 0, 255, THRESH_BINARY | THRESH_OTSU);	// ������׷� �ֺ��� �߰��� ã��

	/* �������� �κ� */
	ROI_whiteBack = getWhiteBackCircle(ROI, point_otsu);
	if ((point_ballMode = get_point_ballMode(ROI_whiteBack, point_otsu)) < point_otsu - distance_noise2back)
		point_ballMode = get_point_ballMode_dnoise(ROI_whiteBack, point_otsu - distance_noise2back, point_otsu);
	
	threshold(ROI_whiteBack, ROI_dst, point_ballMode + distance_th, 255, THRESH_BINARY);	// ����ȭ ����
	drawToOriginal_RGB(Original_RGB, ROI_dst, r, ratio_th);		// ��� �׸���
}	

/* point_mode�� Ž�� �Լ� */
int get_point_ballMode(Mat ROI, int point_otsu)
{
	int hist_max = -1;
	int point_ballMode = -1;
	int histogram[256] = { 0 };

	/* ������׷� ���� */
	for (int y = 0; y < ROI.rows; y++)
		for (int x = 0; x < ROI.cols; x++)
			histogram[(int)ROI.at<uchar>(y, x)]++;

	/* point_mode �� Ž�� */
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

/* �ҷ����� ��� �Լ� */
float getRatio(Mat ROI_dst)
{
	Mat lables, stats, centroids;
	int sum_solder = 0;
	int sum_void = 0;

	/* �̹��� ���̺� ���� */
	int n = connectedComponentsWithStats(ROI_dst, lables, stats, centroids);

	vector<Vec3b> colors(n);
	for (int i = 0; i < n; ++i)
		colors[i] = Vec3b(i, i, i);

	Mat ROI_RGB = Mat::zeros(ROI_dst.size(), CV_8UC3);

	/* ���̺� �ѹ��� ������ ä���� ���� ���� */
	for (int y = 0; y < ROI_RGB.rows; y++)
		for (int x = 0; x < ROI_RGB.cols; x++)
		{
			int label = lables.at<int>(y, x);
			ROI_RGB.at<Vec3b>(y, x) = colors[label];
		}

	/* ������ ȭ�Ұ��� ��� */
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
	/* void ���� ��� */
	float ratio = (float)sum_void / float(sum_void + sum_solder);

	return ratio;	// �ҷ� ���� ��ȯ
}

/* big ball�� �������� �Ǵ� �Լ� */
bool judge_need_blur(Mat ROI_beforeBlur, const int& th_val)
{
	Mat lables, stats, centroids;

	/* ���̺� ���� */
	int n = connectedComponentsWithStats(ROI_beforeBlur, lables, stats, centroids);

	/* ���� ������ ������������ ���ٸ� �÷��� �ø� */
	if (n > th_val)
		return true;
	else
		return false;
}

/* object�� ��輱 ���� �Լ� */
Mat getGradadient(Mat ROI_dst)
{
	int scale = 1; int delta = 0;
	Mat grad, grad_x, grad_y, abs_grad_x, abs_grad_y;

	/* sobel edge detecting�� �̿��Ͽ� ��輱 ���� */
	Sobel(ROI_dst, grad_x, CV_16S, 1, 0, 1, scale, delta, BORDER_DEFAULT);
	Sobel(ROI_dst, grad_y, CV_16S, 0, 1, 1, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	return grad;
}

/* �ҷ����� ����� ���� float -> ���ڿ� ��ȯ �Լ� */
char* getRatioString(float ratio)
{
	/* ���Ժ����� "00.00"�� format���� ����ϱ� ���� 
	float -> string���� �ٲٴ� �˰��� */
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

/* �˻��� �̹��� �׸��� �Լ� */
void drawToOriginal_RGB(Mat Original_RGB, Mat ROI_dst, Rect r, float ratio_th)
{
	Mat grad;
	float ratio = 0.0f;
	char str_ratio[6] = { NULL };

	ratio = getRatio(ROI_dst);			// �ҷ� ���� ���
	grad = getGradadient(ROI_dst);		// ��輱 ����
	strcpy_s(str_ratio, getRatioString(ratio));	// �ҷ� ������ �˻� ����� ����� ���� string���� ��ȯ

	/* ROI ǥ�� */
	rectangle(Original_RGB, Point(r.x, r.y), Point(r.x + r.width, r.y + r.height), Scalar(200, 200, 200), 2);	

	/* �ҷ� ������ �Ӱ찪���� �������(�����ΰ��) */
	if (ratio < ratio_th)
	{
		putText(Original_RGB, str_ratio, Point(r.x + r.width / 12, r.y + (r.height * 10) / 11), FONT_HERSHEY_PLAIN, 1, Scalar(10, 10, 10), 0.7);

		/* ������ ��輱�� �̿��Ͽ� ����׸��� */
		for (int row = r.x; row < r.x + r.width; row++)
			for (int col = r.y; col < r.y + r.height; col++)
			{
				if (grad.at<uchar>(col - r.y, row - r.x) != 0)
					circle(Original_RGB, Point(row, col), 0.5, Scalar(0, 255, 0), 0.5);
			}
	}/* �ҷ� ������ �Ӱ찪���� �������(�ҷ��ΰ��) */
	else
	{
		char defect[5] = "VOID";
		putText(Original_RGB, defect, Point(r.x, r.y), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 0.7);
		putText(Original_RGB, str_ratio, Point(r.x + r.width / 12, r.y + (r.height * 10) / 11), FONT_HERSHEY_PLAIN, 1, Scalar(10, 10, 10), 0.7);

		/* ������ ��輱�� �̿��Ͽ� ��� �׸��� */
		for (int row = r.x; row < r.x + r.width; row++)
			for (int col = r.y; col < r.y + r.height; col++)
			{
				if (grad.at<uchar>(col - r.y, row - r.x) != 0)
					circle(Original_RGB, Point(row, col), 0.5, Scalar(0, 0, 255), 0.5);
			}
	}
}

/* mid ball�� �������� �Լ�1 */
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

/* mid ball�� �������� �Լ�2 */
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

/* MFC�� �̹��� Ŭ������ Mat Ŭ���� ��ȯ�� ���� �Լ� �� */
Mat getIppCloneMat(IppByteImage& img)
{
	int cols = img.GetWidth();
	int rows = img.GetHeight();
	BYTE** p = img.GetPixels2D();
	Mat src(rows, cols, CV_8UC1);

	/* MFC �̹��� Ŭ���� > Mat Ŭ���� ��ȯ */
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

	/* Mat Ŭ������ ����� ������ MFC �̹����� ��ȯ */
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
