#include "RubikRobot.h"
//#include "RubikState.h"


int main(int argc, char* argv[])
{
	std::string str("COM3");

	RubikRobot robot(str);

	//robot.setPort("COM3");
/*	if (rubikrobot.init()){
		std::cout << "Communication is ready" << std::endl;
	} else {
		std::cout << "Communication is not ready" << std::endl;
	}*/

/*	RubikState rubikState(1);
	rubikState.launchCapture();*/

	return 0;
}