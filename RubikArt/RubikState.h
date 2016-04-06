#ifndef RUBIKSTATE_HEADER
#define RUBIKSTATE_HEADER	
#include <vector>
#include <iostream>
#include <algorithm>
#include "Utils.h"

#define NB_CAPTURE 6

class RubikState {	
	private:
		int camera_id;
		int square_count;
		bool filterRect(cv::Rect);
		cv::String window_name;
		cv::String defineColorText(int);

	public:
		RubikState();
		RubikState(int);
		RubikState(int, cv::String);
		void launchCapture();
		void setCameraId(int);
		int getCameraId();
		void setSquareCount(int);
		int getSquareCount();
		void setWindowName(cv::String);
		cv::String getWindowName();
		void printSide(std::vector<SquareRubik>);
		std::vector<SquareRubik> sortResult(std::vector<SquareRubik>);
		static bool sortXAxis(SquareRubik r1, SquareRubik r2) { return r1.position.x < r2.position.x; };
		static bool sortYAxis(SquareRubik r1, SquareRubik r2) { return r1.position.y < r2.position.y; };
};

#endif