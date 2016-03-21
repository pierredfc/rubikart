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

// White - Green - Red - Blue - Orange - Yellow
std::vector<Scalar> minColor{ Scalar(70, 20, 130), Scalar(60, 110, 110), Scalar(120, 120, 140), Scalar(80, 180, 190), Scalar(5, 150, 150), Scalar(20, 100, 100) };
std::vector<Scalar> maxColor{ Scalar(180, 110, 255), Scalar(100, 220, 250), Scalar(180, 250, 200), Scalar(120, 255, 255), Scalar(15, 235, 250), Scalar(40, 255, 255) };


bool filterRec(Rect rec){

	if (rec.width == 60 && rec.height == 60){
		return true;
	}

	if (rec.width > 55 && rec.width < 65){
		if (rec.height > 55 && rec.height < 65){
			return true;
		}
	}

	return false;
}

// Yellow / Orange / Red / Blue / Green / White

int main(int argc, char* argv[])
{
	VideoCapture cap(0); // open the video file for reading
	cap.set(CV_CAP_PROP_SETTINGS, 1);

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

	int nb_capture = 0;
	Cube rubiksCube(3);

	while (nb_capture < 6)
	{
		vector<Point2f> points;

		Side side(3);

		int count = 0;
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
			String text = "";
			switch (j){
				case 0:
					text = "W";
					break;
				case 1:
					text = "G";
					break;
				case 2:
					text = "R";
					break;
				case 3:
					text = "B";
					break;
				case 4:
					text = "O";
					break;
				case 5:
					text = "Y";
					break;
				default:
					break;
			}

			for (unsigned int i = 0; i < finalContours[j].size(); i++){
				Rect rec = boundingRect(finalContours[j][i]);
				
				if (filterRec(rec)){
					count++;
					rectangle(frame_RGB, rec, Scalar(0, 255, 0), 2);
					putText(frame_RGB, text, Point2f(rec.x + rec.width / 2, rec.y + rec.height / 2), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0, 0));
					points.push_back(Point2f(rec.x, rec.y));
				}
			}
		}

		imshow("MyVideo", frame_RGB);

		// Found all cube of a side!
		if (count == 9){
			for (int i = 0; i < points.size(); i++){
				// TODO emplacement
			}

			rubiksCube.setSide(nb_capture, side);
			nb_capture++;
			waitKey();
		}

		finalContours.clear();
		hierarchy.clear();
		if (waitKey(20) == 'q') return 0;
	}

	return 0;
}