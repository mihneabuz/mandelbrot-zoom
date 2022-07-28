#pragma once

#include <complex>
#include <thread>
#include <vector>

#include "calculator.hpp"

#define MAX_ITER 200

class CPU_Calculator : public Calculator {
public:
	CPU_Calculator() {}

	void compute(range re, range im, int x, int y, Uint8* buffer);
};
