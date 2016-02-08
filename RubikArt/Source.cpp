#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "Cube.h"
#include "RubikColor.h"
#include "Square.h"
#include "Side.h"

#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

std::vector<Scalar> minColor{ Scalar(20, 100, 100), Scalar(5, 150, 150), Scalar(120, 120, 140), Scalar(80,180,190), Scalar(60,110,110), Scalar(70,20,130)};
std::vector<Scalar> maxColor{ Scalar(40, 255, 255), Scalar(15, 235, 250), Scalar(180, 250, 200), Scalar(120, 255, 255), Scalar(100, 220, 250), Scalar(180, 110, 255)};

int main(int argc, char* argv[])
{
	VideoCapture cap(0); // open the video file for reading

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	Mat frame_RGB;
	Mat filter;
	Mat frame_HSV;
	Mat frame_threshed;
	Mat imgray;
	Mat result;

	vector<vector<vector<Point>>> finalContours;

	while (1)
	{

		cap.read(frame_RGB); // read a new frame from video
		bilateralFilter(frame_RGB, filter, 9, 75, 75);
		cvtColor(filter, frame_HSV, COLOR_BGR2HSV);

		for (int i = 0; i < minColor.size(); i++){
			inRange(frame_HSV, minColor[i], maxColor[i], frame_threshed);
			imgray = frame_threshed;

			threshold(frame_threshed, result, 127, 255, 0);

			findContours(result, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
			finalContours.push_back(contours);
		}

		for (unsigned int j = 0; j < finalContours.size(); j++){
			for (unsigned int i = 0; i < finalContours[j].size(); i++){
				Rect rec = boundingRect(finalContours[j][i]);
				rectangle(frame_RGB, rec, Scalar(0, 255, 0), 2);
			}
		}
		

		imshow("MyVideo", frame_RGB);
		finalContours.clear();
		hierarchy.clear();
		if (waitKey(20) == 'q') return 0;
	}

	return 0;
}