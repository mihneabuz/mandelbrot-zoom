#pragma once

#include <complex>
#include <thread>
#include <vector>

#include "calculator.hpp"

class CPU_Calculator : public Calculator {
public:
  int max_iter;

	CPU_Calculator(int x): max_iter(x) {}

	float getZoomStep() { return 0.1; };

	void compute(range re, range im, int x, int y, Uint8* buffer);
};
