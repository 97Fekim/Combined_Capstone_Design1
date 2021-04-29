#include "header.h"

int main()
{
	Mat A;
	A = imread("lenna.jpg", IMREAD_COLOR);

	Rect r(20, 20, 100, 100);
	Mat D = A(r);					// 객체 D는 (10,10) 영역에서 100 x 100 크기의 부분영상을 나타낸다.
	//Mat D = A(r).clone();			// D를 변경하면 A도 바뀐다. 공유하고 있기 때문에. 그래서 clone을 붙여줘야 독립시킬 수 있다.

	imshow("full", A);
	D = Scalar(0, 0, 0);			// 관심영역의 모든 화소가 (0,0,0)이 된다.
	imshow("black roi", A);
	waitKey(0);
	return 0;

}
