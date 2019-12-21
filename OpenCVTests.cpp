#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void exampleGetStructuringElement()
{
	Mat image = imread("checkers_before_filter.jpg", IMREAD_GRAYSCALE);
	Mat kernel = getStructuringElement(MORPH_CROSS, Size(7, 7)) * 255;
	Mat eroded;

	erode(image, eroded, kernel);

	namedWindow("Original Image", WINDOW_FREERATIO);
	namedWindow("Eroded Image", WINDOW_FREERATIO);
	namedWindow("Kernel", WINDOW_FREERATIO);
	imshow("Original Image", image);
	imshow("Eroded Image", eroded);
	imshow("Kernel", kernel);

	waitKey(0); //waits until somthing is pressed
}

void exampleOwnKernel()
{
	Mat image = imread("checkers_before_filter.jpg", IMREAD_GRAYSCALE);

	Mat kernel = Mat::zeros(Size(7, 7), CV_8U);
	kernel.at<uint8_t>(0, 0) = 255;
	kernel.at<uint8_t>(3, 3) = 255;
	kernel.at<uint8_t>(6, 6) = 255;

	Mat eroded;
	erode(image, eroded, kernel);

	namedWindow("Original Image", WINDOW_FREERATIO);
	namedWindow("Eroded Image", WINDOW_FREERATIO);
	namedWindow("Kernel", WINDOW_FREERATIO);
	imshow("Original Image", image);
	imshow("Eroded Image", eroded);
	imshow("Kernel", kernel);

	waitKey(0);
}

void exampleVerticalAndHorizontalLines()
{
	Mat image = imread("grid_before_filter.png", IMREAD_GRAYSCALE);
	image = ~image; //switches between black and white

	Mat horizontalSE = getStructuringElement(MORPH_RECT, Size(image.cols / 15, 1));
	Mat verticalSE = getStructuringElement(MORPH_RECT, Size(1, image.rows / 11));

	Mat hErode, vErode;

	erode(image, hErode, horizontalSE);
	erode(image, vErode, verticalSE);

	imshow("image", image);

	image = image - hErode - vErode;

	imshow("h", hErode);
	imshow("v", vErode);
	imshow("Numbers", image);

	waitKey(0);
}

int main()
{
	//exampleGetStructuringElement();

	//exampleOwnKernel();

	exampleVerticalAndHorizontalLines();

	return 0;
}