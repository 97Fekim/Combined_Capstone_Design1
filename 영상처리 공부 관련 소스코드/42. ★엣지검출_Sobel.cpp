#include "header.h"

Mat getGrad(Mat src)
{
	Mat grad;
	int scale = 1;
	int delta = 0;

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	Sobel(src, grad_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	Sobel(src, grad_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);

	convertScaleAbs(grad_x, abs_grad_x,1);
	convertScaleAbs(grad_y, abs_grad_y,1);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	return grad;
}

int main()
{
	/*Mat grad;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	int scale = 1;
	int delta = 0;*/
	
	Mat src1 = imread("small.jpg", IMREAD_GRAYSCALE);
	Mat src2 = imread("small_stretched.jpg", IMREAD_GRAYSCALE);
	Mat grad_1;
	Mat grad_2;
	//// 화소의 x방향의 그래디언트 값 계산, scale ~ 마지막param은 default,, 3은 3x3을 의미
	//// 마스크에 화소가 곱해질 때 overflow를 방지하기 위해 16signed type을 이용.
	//Sobel(src, grad_x, CV_16S, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	//Sobel(src, grad_y, CV_16S, 0, 1, 3, scale, delta, BORDER_DEFAULT);


	//convertScaleAbs(grad_x, abs_grad_x);		
	//convertScaleAbs(grad_y, abs_grad_y);
	//// 절댓값을 계산하여서 8비트 행렬로 변환시킨다.


	//// 그래디언트의 크기를 계산, 2개 행렬의 가중치 합을 계산하는 함수. 보통 0.5 x Gx + 0.5 x Gy 로 계산을 한다. 0적혀있는건 감마이다. 뒤에 더해지는,,
	//addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	grad_1 = getGrad(src1);
	grad_2 = getGrad(src2);

	imshow("원본", src1);
	imshow("스트레칭된 원본", src2);

	imshow("원본의 엣지", grad_1);
	imshow("스트레칭된 원본의 엣지", grad_2);

	resize(src1, src1, Size(180, 180));
	resize(src2, src2, Size(180, 180));
	resize(grad_1, grad_1, Size(180, 180));
	resize(grad_2, grad_2, Size(180, 180));

	for (int y = 0; y < src1.rows; y++)
		for (int x = 0; x < src1.cols; x++)
		{
			src2.at<uchar>(y,x) += grad_1.at<uchar>(y, x);
		}

	

	imshow("Mask", src2);
	
	waitKey(0);
	return 0;
}