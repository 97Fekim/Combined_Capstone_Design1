#include "header.h"

int main()
{
	double alpha = 1.0;
	int beta = 0;

	Mat src = imread("small.jpg", IMREAD_GRAYSCALE);
	Mat img, th1, th2, th3, th4;

	cout << "알파값을 입력하세요: [1.0 ~ 3.0]";
	cin >> alpha;
	cout << "베타값을 입력하세요: [0 ~ 50]";
	cin >> beta;

	src.convertTo(th1, -1, alpha, beta);
	imshow("Original Image",src);
	imshow("New Image",th1);

	waitKey(0);
	return 0;

}