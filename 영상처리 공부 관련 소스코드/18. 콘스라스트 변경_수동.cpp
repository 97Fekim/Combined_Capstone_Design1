#include "header.h"

int main()
{
	double alpha = 1.0;
	int beta = 0;
	Mat image = imread("fekim.jpg");
	Mat oimage = Mat::zeros(image.size(), image.type());	// 모든 화소를 검정색으로 초기화함.
	cout << "알파값을 입력하세요 : [1.0 - 3.0]";
	cin >> alpha;
	cout << "베타값을 입력하세요 : [0 - 300]";
	cin >> beta;

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for(int c = 0; c < 3; c++)
			oimage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * (image.at<Vec3b>(y, x)[c]) + beta);	// <Vec3b>는 컬러영상이므로 BRG를 뜻한다. 즉 컬러에 접근하려면 Vec3b를 써줘야 한다.
																											// (y,c)[c] 에서 y는 행, x는 열, c는 B,R,G를 뜻한다. 
		}

	}
	imshow("Original Image", image);
	imshow("New Image", oimage);

	waitKey(0);
	
	return 0;
}