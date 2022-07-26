#pragma once

#include <algorithm>

struct range {
	double start, end;
	range(double x, double y): start(std::min(x, y)), end(std::max(x, y)) {};

	void shrink(double factor) {
		auto amount = (this->end - this->start) * factor;
		this->start += amount;
		this->end   -= amount;
	}

	void shift(double factor) {
		auto amount = (this->end - this->start) * factor;
		this->start += amount;
		this->end   += amount;
	}
};
