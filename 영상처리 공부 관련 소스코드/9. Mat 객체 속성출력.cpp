#include "header.h"

int main()
{
	Mat img = imread("lenna.jpg");
	imshow("img", img);
	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);

	cout << "행의 수 = " << img.rows << endl;
	cout << "열의 수 = " << img.cols << endl;
	cout << "행렬의 크기 = " << img.size() << endl;
	cout << "전체 화소 개수 = " << img.total() << endl;
	cout << "한 화소 크기 = " << gray.elemSize() << endl;
	cout << "타입 = " << img.type() << endl;
	cout << "채널 = " << img.channels() << endl;

	cout << img << endl;


	waitKey(0);
	return 0;
	

}