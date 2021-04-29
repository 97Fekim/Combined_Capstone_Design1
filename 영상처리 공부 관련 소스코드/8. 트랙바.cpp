#include "header.h"

Mat img,img_color,circles;
int red=1, green=1, blue=1;

void HoughCircle(int, void* param)
{
	vector<Vec3f> circles;
	HoughCircles(img, circles, HOUGH_GRADIENT, 1, img.rows, 200, blue, (int)(img.rows / 4), (int)((double)img.rows / 2.5));

	for (size_t i = 0; i < circles.size(); ++i)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(img_color, center, radius, Scalar(255, 0, 0), -1, 8, 0);
	}

	imshow("img_color", img_color);
}

int main()
{
	img = imread("ksc.jpg",IMREAD_GRAYSCALE);
	cvtColor(img_color, img_color, COLOR_GRAY2BGR);
	img_color = img.clone();

	namedWindow("img_color", WINDOW_FREERATIO);

	createTrackbar("Á¤È®µµ", "img_color", &blue, 255, HoughCircle);
	createTrackbar("min", "img_color", &red, 255, HoughCircle);


	HoughCircle(0, 0);
	waitKey(0);
	
	return 0;

}