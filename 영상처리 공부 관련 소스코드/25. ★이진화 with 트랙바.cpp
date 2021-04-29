#include "header.h"

Mat src, src_gray, dst;
int threshold_value = 0;	// 트랙바 사용을 위해 변수들을 전역변수로 정의한다.
int threshold_type = 0;

void Threshold_Demo(int, void*)
{
	threshold(src_gray, dst, threshold_value, 255, threshold_type);
	imshow("결과영상", dst);
}


int main()
{
	src = imread("lenna.jpg");
	cvtColor(src, src_gray, CV_BGR2GRAY);

	namedWindow("결과영상", CV_WINDOW_AUTOSIZE);

	createTrackbar("임계값", "결과영상", &threshold_value, 255, Threshold_Demo);

	Threshold_Demo(0, 0);

	while (1)
	{
		int c;
		c = waitKey(20);
		if ((char)c == 27)	// ESC 키가 입력되면 무한루프 종료.
			break;
	}
	return 0;
}