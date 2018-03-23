#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "catch.h"

int main(int argc, char* argv[]) 
{
	int result = Catch::Session().run(argc, argv);

	std::cout << "press any key to exit..." << std::endl;
	std::getchar();
	return result;
}