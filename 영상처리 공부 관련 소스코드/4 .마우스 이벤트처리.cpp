#include "header.h"


// 마우스 이벤트가 발생하면 호출되는 콜백 함수이다.
void onMouse(int event, int x, int y, int flags, void* param)
{
	if (event == EVENT_LBUTTONDOWN)		// 마우스 왼쪽버튼이 눌리면
	{
		Mat& img = *(Mat*)(param);
		circle(img, Point(x, y), 100, Scalar(0, 255, 0), 10);
		putText(img, "face!", Point(x+20, y + 100), FONT_HERSHEY_PLAIN, 2.0, 255, 2);
		imshow("src", img);				// 영상이 변경되면 다시 표시한다.
	}
	else if (event == EVENT_RBUTTONDOWN) {}
	else if (event == EVENT_MBUTTONDOWN) {}
	else if (event == EVENT_MOUSEMOVE) {
	}
}

int main()
{
	Mat src = imread("ksc.jpg", IMREAD_COLOR);
	if (src.empty()) { cout << "영상을 읽을 수 없음" << endl; }
	imshow("src", src);

	setMouseCallback("src", onMouse, &src);
	waitKey(0);
	return 0;

}
