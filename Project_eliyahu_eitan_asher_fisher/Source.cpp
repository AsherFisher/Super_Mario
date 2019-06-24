/*Program : Super Mario game
Written by: Eliyahu Eitan & Asher Fisher*/

#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#else
#error "Unrecognized configuration!"
#endif

#include "Controller.h"

int main() try
{
		std::srand(unsigned int(std::time(NULL)));

		Controller c;
		c.run();

	return 0;
}
catch (std::ios_base::failure e) {
	std::cout << e.what() << std::endl;
	std::cout << "Press Enter to close the program" << std::endl;
	getchar();
}
catch (...) {}