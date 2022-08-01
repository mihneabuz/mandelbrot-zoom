#pragma once

#include <iostream>

#include "calculator.hpp"
#include "cuda/compute.h"

class Cuda_Calculator : public Calculator {
public:
	Cuda_Calculator() {}

	void compute(range re, range im, int x, int y, Uint8* buffer) {
		std::cout << "incepem!" << x << ' ' << y << "\n";
		cuda_compute(re.start, re.end, im.start, im.end, x, y, buffer);

		for (int i = 0; i < x * y * 3; i++) {
			if (buffer[i] !=0 )
				std::cout << buffer[i];
		}
	};
};
