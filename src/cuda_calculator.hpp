#pragma once

#include <iostream>

#include "calculator.hpp"
#include "cuda/compute.h"

class Cuda_Calculator : public Calculator {
public:
  int max_iter;

	Cuda_Calculator(int x): max_iter(x) {};

	float getZoomStep() { return 0.01; };

	void compute(range re, range im, int x, int y, Uint8* buffer) {
		cuda_compute(re.start, re.end, im.start, im.end, x, y, buffer, max_iter);
	};
};
