#ifndef RUBIKSTATE_HEADER
#define RUBIKSTATE_HEADER	
#include <vector>
#include <iostream>
#include <algorithm>
#include "Utils.h"


class RubikState {	
	private:
		int camera_id;
		bool filterRec(Rect);

	public:
		RubikState();
		RubikState(int);
		void launchCapture();
		void setCameraId(int);
		int getCameraId();
		void printSide(std::vector<SquareRubik>);
		std::vector<SquareRubik> sortResult(std::vector<SquareRubik>);
		static bool sortXAxis(SquareRubik r1, SquareRubik r2) { return r1.position.x < r2.position.x; };
		static bool sortYAxis(SquareRubik r1, SquareRubik r2) { return r1.position.y < r2.position.y; };
};

#endif