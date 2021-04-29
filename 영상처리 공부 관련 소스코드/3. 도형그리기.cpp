#include "header.h"


int main()
{
	Mat image = imread("void.bmp",IMREAD_GRAYSCALE); //Mat(400, 600, CV_8UC3, Scalar(0, 0, 0));	// 가로600, 세로400의 컬러영상 생성 즉 함수안은 세로,가로 순이다.

	cvtColor(image,image,COLOR_GRAY2BGR);

	//line(image, Point(100, 50), Point(300, 300), Scalar(0, 0, 255) , 7);	// (이미지,시작점,끝점,색깔,두께) 참고할점 : 왼쪽이 가로, 오른쪽이 세로, 색깔은 BGR 순서대로.
	rectangle(image, Point(610, 349), Point(720, 470), Scalar(0, 255, 0), 1);	// (이미지,왼쪽위,오른쪽아래,색깔,두께) 
	//circle(image, Point(100, 300), 60, Scalar(255, 0, 0), 3);				// (이미지, 중심, 반지름, 색깔, 두께 )
	//ellipse(image, Point(300, 350), Point(100, 60), 45, 130, 270, Scalar(255, 255, 255), 5);	// (이미지, 중심, 장축과단축, 회전각도, 시작각도, 종료각도, 색깔, 두께)

	imshow("이름이양", image);

	waitKey(0);
	return 0;
}