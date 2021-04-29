#include"header.h"


// 예제를 흑백으로 변경시켜보았다.
int main() 
{
	Mat src = imread("ksc.jpg", IMREAD_COLOR);
	
	Mat gray;

	cvtColor(src, gray,COLOR_BGR2GRAY);

	imshow("gray", gray);

	while (1)
	{
		int key = waitKeyEx();		// 키보드 왼쪽키는 2424832를 리턴, 키보드 오른쪽키는 2555904를 리턴
		cout << key << " ";	
		if (key == 'q')break;
		else if (key == 2424832)	// 왼쪽키가 눌리면 밝기를 50낮춤.
			gray -= 50;				
		else if (key == 2555904)	// 오른쪽키가 눌리면 밝기를 50높임
			gray += 50;
		imshow("gray", gray);
	}

	return 0;
}