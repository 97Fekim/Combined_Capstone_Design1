#include "header.h"


// 예제코드
int main()
{
	Mat img;
	img = imread("ksc.jpg", IMREAD_COLOR);
	if (img.empty()) { cout << "영상을 읽을 수 없음" << endl; }

	imshow("img", img);
	int x = 200;
	int y = 300;
	while (1)
	{
		int key = waitKey(100);		// 100ms 동안 사용자가 키를 누르기를 기다린다.
		if (key == 'q')break;
		else if (key == 'a')
			x -= 10;
		else if (key == 'w')
			y -= 10;
		else if (key == 'd')
			x += 10;
		else if (key == 's')
			y += 10;
		circle(img, Point(x, y), 100, Scalar(0, 255, 0), 3);	//키가 눌리면 현재 위치에 반지름이 200인 녹색 원을 그린다.
		imshow("img", img);
	}

	return 0;
}


// 예제코드 변형 (한 사진에 초록원이 하나만 존재하게)
/*int main()
{
	Mat img;
	img = imread("dog.jpg", IMREAD_COLOR);
	if (img.empty()) { cout << "영상을 읽을 수 없음" << endl; }

	imshow("img", img);
	int x = 300;
	int y = 300;
	while (1)
	{
		img = imread("dog.jpg", IMREAD_COLOR);
		int key = waitKey(100);		// 100ms 동안 사용자가 키를 누르기를 기다린다.
		if (key == 'q')break;
		else if (key == 'a')
			x -= 10;
		else if (key == 'w')
			y -= 10;
		else if (key == 'd')
			x += 10;
		else if (key == 's')
			y += 10;
		circle(img, Point(x, y), 150, Scalar(0, 215, 0), 5);	//키가 눌리면 현재 위치에 반지름이 200인 녹색 원을 그린다.
		imshow("img", img);
	}

	return 0;
}*/