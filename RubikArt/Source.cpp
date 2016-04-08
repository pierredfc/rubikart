#include "RubikRobot.h"
#include "RubikState.h"

int main(int argc, char* argv[])
{
	RubikRobot robot("COM3", 0);

	if (robot.initPort()){
		std::cout << "Communication is ready" << std::endl;

		robot.send('f');
		if (robot.read() == 'f'){
			std::cout << "Movement done" << std::endl;
		}

		robot.send('e');
		if (robot.read() == 'e'){
			std::cout << "Movement done" << std::endl;
		}

	} else {
		std::cout << "Communication is not ready" << std::endl;
	}

	getchar();

	robot.getState().launchCapture();

	return 0;
}