#include "header.h"


Mat img;
int drawing = false;

void drawCircle(int event, int x, int y, int, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
		drawing = true;
	else if (event == CV_EVENT_MOUSEMOVE)
	{
		if (drawing == true)
			circle(img, Point(x, y), 2, Scalar(0, 0, 255), 4);
	}
	else if (event == CV_EVENT_LBUTTONUP)
		drawing = false;
	imshow("ksc", img);


}

int main()
{
	img = imread("ksc.jpg", IMREAD_COLOR);

	imshow("ksc", img);

	setMouseCallback("ksc", drawCircle);

	waitKey(0);

	imwrite("ksc_with_drawing.jpg", img);

	return 0;


}