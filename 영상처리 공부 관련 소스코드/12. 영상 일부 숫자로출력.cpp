#include "header.h"

int main()
{
	Mat img = imread("fekim.jpg");
	imshow("img", img);
	Mat roi(img, Rect(10, 10, 2, 2));

	cout << "행의 수 = " << roi.cols << endl;
	cout << "열의 수 = " << roi.rows << endl;
	cout << "roi = " << endl << roi << endl << endl;
	waitKey(0);

	return 0;

}