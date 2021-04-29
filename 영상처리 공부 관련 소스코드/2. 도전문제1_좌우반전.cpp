#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("lenna.jpg", IMREAD_COLOR);
	if (src.empty()) { cout << "영상을 읽을 수 없음" << endl; }
	imshow("src",src);

	Mat dst;
	flip(src, dst, 1);		// src의 사진을 좌우반전시켜 dst에 넣는다.
	imshow("사진이름일뿐!", dst);


	waitKey(0);
	return 0;
}