#include "header.h"

int main()
{
	Mat A = imread("fekim.jpg");
	Mat B = imread("sec.jpg");
	Mat roi(A, Rect(A.cols - B.cols, A.rows - B.rows, B.cols, B.rows));
	
	B.copyTo(roi);

	imshow("result", A);
	waitKey(0);
	return 0;
}