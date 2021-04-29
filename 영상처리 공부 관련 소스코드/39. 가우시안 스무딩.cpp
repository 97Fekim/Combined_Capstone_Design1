#include "header.h"


/*  가중치를 부여한 평균값 필터링 중앙이 가중치가 가장 높고,
	멀어질수록 가중치가 낮아진다.	  */
int main()
{
	Mat src = imread("lenna.jpg", 1);
	Mat dst;
	imshow("src", src);

	for (int i = 1; i < 61; i = i + 2)
	{
		GaussianBlur(src, dst, Size(i, i), 0, 0);
		imshow("dst", dst);

		waitKey(500);			// 500ms마다 영상이 흐려진다.
	}

	return 0;
}