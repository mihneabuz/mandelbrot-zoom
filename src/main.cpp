#include <iostream>

#include "renderer.hpp"
#include "cpu_calculator.hpp"
#include "cuda_calculator.hpp"

int main (int argc, char *argv[])
{
	if (argc < 3) {
		std::cout << "Usage: mandlebrot [width] [height]" << std::endl;
		return 1;
	}

	auto width  = atoi(argv[1]);
	auto height = atoi(argv[2]);

	if (height <= 0 || width <= 0) {
		std::cout << "Bad window resolution" << std::endl;
		return 1;
	}

	std::cout << width << 'x' << height << std::endl;

	auto renderer = Renderer(width, height);

#ifdef CUDA
	renderer.attach_calculator(new Cuda_Calculator());
#else
	renderer.attach_calculator(new CPU_Calculator());
#endif

	renderer.start({-2, 1}, {-1, 1});

	return 0;
}
