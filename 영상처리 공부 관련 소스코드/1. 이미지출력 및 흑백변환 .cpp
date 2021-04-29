#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("lenna.jpg", IMREAD_COLOR);	// src라는 Mat 변수 생성 후 lenna이미지를 컬러로 저장
	if (src.empty()) { cout << "영상을 읽을 수 없음" << endl; }	// 영상이 없을 경우 글자출력
	imshow("사진이름이당", src);		// Mat객체인 src에 저장된 src 영상 출력 앞의 ""속은 창의 이름

	Mat gray, edge, output;		// Mat 변수 3개 생성
	cvtColor(src, gray, CV_BGR2GRAY);	// src를 gray에 넣는데 BGR을 흑백으로 변경해서 넣는다.

	imshow("사진이름이당2", gray);	// 출력
	imwrite("gray.jpg", gray);		// gray를 gray.jpg로 저장

	waitKey(0);
	return 0;
}
