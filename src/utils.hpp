#pragma once

#include <algorithm>

struct range {
	double start, end;
	range(double x, double y): start(std::min(x, y)), end(std::max(x, y)) {};
};
