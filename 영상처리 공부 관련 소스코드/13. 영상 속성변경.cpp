#include "header.h"

//int main()
//{
//	Mat LoadedImage = imread("lenna.jpg", IMREAD_COLOR);
//	imshow("Original Image", LoadedImage);
//
//	resize(LoadedImage, LoadedImage, Size(100, 100));
//	imshow("New image", LoadedImage);
//
//	waitKey(0);
//	return 0;
//}

// reshape함수는 책 101p 참조.

int main(void)
{
	Mat img1 = imread("lenna.jpg");
	Mat img2 = imread("dog.jpg");
	imshow("Original Image", img1);

	img1.push_back(img2);			// 열의 화소수 ??? x !!! 에서 ???의 갯수가 일치해야 붙일 수 있다.

	imshow("New Image", img1);
	waitKey(0);

	return 0;
}