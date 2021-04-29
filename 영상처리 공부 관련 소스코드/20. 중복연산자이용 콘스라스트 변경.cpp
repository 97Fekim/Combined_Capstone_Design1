#include "header.h"

int main()
{
	double alpha = 1.0;
	int beta = 0;

	Mat image = imread("fekim.jpg");
	Mat oimage;

	cout << "알파값을 입력하세요: [1.0 ~ 3.0]";
	cin >> alpha;
	cout << "베타값을 입력하세요: [0 ~ 50]";
	cin >> beta;

	/* Mat 이라는 객체안에 +연산이 정의되어 있기 때문에 가능한 연산 
	또한 그냥 beta를 써주면 blue성분에만 beta가 추가되므로 Scalar를 이용한
	연산을 이용해야 한다. */
	oimage = image * alpha + Scalar(beta,beta,beta);		

	imshow("Original Image", image);
	imshow("New Image", oimage);

	waitKey(0);
	return 0;

}