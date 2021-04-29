#include"header.h"

Mat src, src_gray, dst, detected_edges;
int lowTh, ratio = 3, kernel_size = 3, max_lowTh = 100;

static void CannyThreshold(int, void*)
{
	blur(src, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, lowTh, lowTh * ratio, kernel_size);
	dst = Scalar::all(0);
	src.copyTo(dst, detected_edges);
	imshow("detected",detected_edges);
	imshow("Image", src);
	imshow("Canny", dst);
}

void main()
{
	src = imread("11.jpg", IMREAD_GRAYSCALE);
	dst.create(src.size(), src.type());
	namedWindow("Canny", CV_WINDOW_AUTOSIZE);
	createTrackbar("Min Threshold:", "Canny", &lowTh, max_lowTh, CannyThreshold);
	CannyThreshold(0, 0);
	waitKey(0);
}