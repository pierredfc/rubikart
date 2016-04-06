#ifndef UTILS_HEADER
#define UTILS_HEADER	

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using cv::Scalar;
using cv::String;
using cv::Rect;
using cv::VideoCapture;
using cv::Mat;
using cv::Vec4i;

enum ColorRubik{
	white = 0,
	green = 1,
	red = 2,
	blue = 3,
	orange = 4,
	yellow = 5
};

struct SquareRubik{
	cv::Point2f position;
	ColorRubik color;

	SquareRubik(cv::Point2f point, ColorRubik col) : position(point), color(col) {}
};

#endif