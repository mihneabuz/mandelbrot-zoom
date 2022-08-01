#pragma once

#include <complex>
#include <thread>
#include <vector>

#include "calculator.hpp"

#define MAX_ITER 200

class CPU_Calculator : public Calculator {
public:
	CPU_Calculator() {}

	float getZoomStep() { return 0.1; };

	void compute(range re, range im, int x, int y, Uint8* buffer);
};
