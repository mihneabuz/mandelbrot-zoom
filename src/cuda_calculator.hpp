#pragma once

#include <iostream>

#include "calculator.hpp"
#include "cuda/compute.h"

class Cuda_Calculator : public Calculator {
public:
	Cuda_Calculator() {}

	void compute(range re, range im, int x, int y, Uint8* buffer) {
		std::cout << "cuda calculator!\n";
		cuda_compute(x, y);
	};
};
