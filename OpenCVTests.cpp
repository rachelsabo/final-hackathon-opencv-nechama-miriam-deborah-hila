#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int detect_obj_by_color()
{
	VideoCapture cap(0); //capture the video from web cam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	namedWindow("Control", WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 0; int iHighH = 179;
	int iLowS = 0; int iHighS = 255;
	int iLowV = 0; int iHighV = 255;

	createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_RECT, Size(3, 3)));

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", imgOriginal); //show the original image

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
}

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

	waitKey(0); //waits until something is pressed
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

	//exampleVerticalAndHorizontalLines();

	detect_obj_by_color();

	return 0;
}