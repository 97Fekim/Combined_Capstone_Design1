#include "tools.h"

int main()
{
	Mat labels, centroids, img_color, stats;
	Mat img_RGB = imread("마우스.jpg", IMREAD_COLOR);
	Mat img = imread("마우스.jpg", IMREAD_GRAYSCALE);
	Mat img_edge;
	imshow("원본", img_RGB);
	imshow("흑백", img);

	threshold(img, img_edge, 85, 255, THRESH_BINARY_INV);
	

	int n = connectedComponentsWithStats(img_edge, labels, stats, centroids);

	vector<Vec3b> colors(n + 1);
	colors[0] = Vec3b(0, 0, 0);


	for (int i = 1; i <= n; i++)
		colors[i] = Vec3b(rand() % 256, rand() % 256, rand() % 256);

	img_color = Mat::zeros(img_edge.size(), CV_8UC3);

	for (int y = 0; y < img_color.rows; y++)
		for (int x = 0; x < img_color.cols; x++)
		{
			int label = labels.at<int>(y, x);
			img_color.at<Vec3b>(y, x) = colors[label];
		}

	imshow("img_color", img_color);

	waitKey(0);
	return 0;
}