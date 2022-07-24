#include <cstdlib>
#include <iostream>

#include "renderer.hpp"

int main (int argc, char *argv[])
{
	if (argc < 3) {
		std::cout << "Usage: mandlebrot [height] [width]" << std::endl;
		return 1;
	}

	auto height = atoi(argv[1]);
	auto width  = atoi(argv[2]);

	if (height <= 0 || width <= 0) {
		std::cout << "Bad window resolution" << std::endl;
		return 1;
	}

	std::cout << height << 'x' << width << std::endl;

	auto renderer = create_renderer(height, width);
	if (renderer == nullptr) {
		return 1;
	}

	return 0;
}
