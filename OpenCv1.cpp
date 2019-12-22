#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, erosion_dst, dilation_dst, open_dst, close_dst;

int erosion_elem = 0;
int erosion_size = 3;
//
//int open_elem = 0;
//int open_size = 3;
//
//int close_elem = 0;
//int close_size = 3;
//
int dilation_elem = 0;
int dilation_size = 3;

int const max_elem = 2;
int const max_kernel_size = 21;

void Erosion(int, void*);
void Dilation(int, void*);
void Open(int, void*);
void Close(int, void*);

int main(int argc, char** argv)
{
	CommandLineParser parser(argc, argv, "{@input |cat.PNG | input image}");
	src = imread(samples::findFile(parser.get<String>("@input")), IMREAD_COLOR);
	if (src.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -1;
	}
#pragma region namedWindow
	//namedWindow("Erosion Demo", WINDOW_AUTOSIZE);
	//namedWindow("Dilation Demo", WINDOW_AUTOSIZE);
	//moveWindow("Dilation Demo", src.cols, 0);
#pragma endregion

#pragma region slides
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
		&erosion_elem, max_elem,
		Erosion);
	createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
		&erosion_size, max_kernel_size,
		Erosion);
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
		&dilation_elem, max_elem,
		Dilation);
	createTrackbar("Kernel size:\n 2n +1", "Dilation Demo",
		&dilation_size, max_kernel_size,
		Dilation);

#pragma endregion 
	imshow("source img", src);
	Erosion(0, 0);
	Dilation(0, 0);
	Open(0, 0);
	Close(0, 0);
	waitKey(0);
	return 0;
}
void Erosion(int, void*)
{
	int erosion_size = 5;
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	erode(src, erosion_dst, element);
	imshow("Erosion Demo", erosion_dst);
}

void Dilation(int, void*)
{
	int dilation_size = 5;
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));

	dilate(src, dilation_dst, element);
	imshow("Dilation Demo", dilation_dst);
}

void Open(int, void*)
{
	int open_size = 3;
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * open_size + 1, 2 * open_size + 1),
		Point(open_size, open_size));

	morphologyEx(src, open_dst, MORPH_OPEN, element);
	imshow("Open Demo", open_dst);
}

void Close(int, void*)
{
	int close_size = 3;
	Mat element = getStructuringElement(MORPH_CROSS,
		Size(2 * close_size + 1, 2 * close_size + 1),
		Point(close_size, close_size));

	morphologyEx(src, close_dst, MORPH_CLOSE, element);
	imshow("Close Demo", close_dst);
}