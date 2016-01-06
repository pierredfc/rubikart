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

struct c
{
	unsigned char r, g, b;
};

c colors[] = { { 17, 140, 92 },			// green
{ 2, 50, 210 },			// blue
{ 138, 30, 45 },			// red
{ 179, 100, 1 },			// orange
{ 195, 220, 2 },			// yellow
{ 199, 225, 255 } };			// white

int defineColorAndDraw(Mat *f, int x1, int y1, int x2, int y2){
	float r = 0, g = 0, b = 0;

	int pixels = 0;

	for (int i = y1; i < y2; i++)
	{
		for (int j = x1; j < x2; j++)
		{
			b += f->at<cv::Vec3b>(i, j)[0];
			g += f->at<cv::Vec3b>(i, j)[1];
			r += f->at<cv::Vec3b>(i, j)[2];
			pixels++;
		}
	}

	r /= pixels;
	g /= pixels;
	b /= pixels;

	float min_dist = -1;
	int min_index = -1;

	for (int i = 0; i < 6; i++)
	{
		float d = (r - colors[i].r)*(r - colors[i].r) +
			(g - colors[i].g)*(g - colors[i].g) +
			(b - colors[i].b)*(b - colors[i].b);

		if (d < min_dist || min_dist == -1)
		{
			min_dist = d;
			min_index = i;
		}
	}

	if (min_index != -1)
	{
		int c = min_index;

		rectangle(*f, Point(x1, y1),
			Point(x2, y2),
			Scalar(colors[c].b, colors[c].g, colors[c].r), -1, 8);
	}

	return min_index;
}

Side detect_cube(Mat frame){
	int picture_x = frame.cols;
	int picture_y = frame.rows;

	Side side(3);

	float xr1 = 0.3;
	float xr2 = 0.7;

	float yr1 = 0.25;
	float yr2 = 0.75;

	for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	{
		float cell_x = (xr2 - xr1) / 3.0;
		float cell_y = (yr2 - yr1) / 3.0;

		float buffer_x = cell_x * 0.2;
		float buffer_y = cell_y * 0.2;

		int x1 = (i * cell_x + xr1 + buffer_x) * picture_x;
		int y1 = (j * cell_y + yr1 + buffer_y) * picture_y;

		int x2 = ((i + 1) * cell_x + xr1 - buffer_x) * picture_x;
		int y2 = ((j + 1) * cell_y + yr1 - buffer_y) * picture_y;

		int final_color = defineColorAndDraw(&frame, x1, y1, x2, y2);
		side.setValue(3 * j + i, Square(RubikColor(final_color)));
	}

	imshow("Rubik Pixel Art", frame); //show the frame in "MyVideo" window

	return side;
}


void display(Side side){
	for (int i = 0; i < 9; i++){
		cout << side.getValue(i).getColor().getColorName();
		if ((i + 1) % 3 == 0)
			cout << "\n";
	}
}

int main(int argc, char* argv[])
{
	bool capture = true;
	int nb_capture = 0;
	Cube cubetest(3);

	VideoCapture cap(0);

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	// Creation of a window
	namedWindow("Rubik Pixel Art", CV_WINDOW_AUTOSIZE);

	while (capture)
	{
		Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}

		Side side = detect_cube(frame);

		// Space for taking Sides of the Rubiks
		if (waitKey(30) == 32)
		{
			cubetest.setSide(nb_capture, side);
			cout << "Capture " << nb_capture << "\n";
			if (nb_capture++ == 5)
				capture = false;
		}
	}

	// Display the sides of the cube
	for (int i = 0; i < 6; i++){
		cout << "Side " << i << ": \n";
		display(cubetest.getSide().at(i));
		cout << "\n";
	}

	system("pause");

	return 0;

}