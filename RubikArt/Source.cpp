#include "RubikRobot.h"
#include "RubikState.h"

int main(int argc, char* argv[])
{
	RubikRobot robot("COM3", 1);

	if (robot.initPort()){
		std::cout << "Communication is ready" << std::endl;

		if (robot.send('d')) {
			std::cout << "Movement done" << std::endl;
		}

		if (robot.send('c')) {
			std::cout << "Movement done" << std::endl;
		}
	} else {
		std::cerr << "Communication is not ready" << std::endl;
	}

	getchar();

	//robot.getState().launchCapture();

	return 0;
}