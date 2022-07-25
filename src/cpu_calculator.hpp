#pragma once

#include <complex>
#include <iostream>
#include <complex.h>

#include "calculator.hpp"

bool is_mandlebrot(std::complex<double> c) {
	std::complex<double> z{0, 0};

	for (int i = 0; i < 200; i++) {
		z = z * z + c;
	}

	return (z.real() * z.real()) + (z.imag() * z.imag()) < 1000;
}

class CPU_Calculator : public Calculator {
public:
	CPU_Calculator() {}

	void compute(range re, range im, int x, int y, Uint8* buffer) {
		double re_step = (re.end - re.start) / x;
		double im_step = (im.end - im.start) / y;

		for (auto i = 0; i < x; i++) {
			for (auto j = 0; j < y; j++) {
				double point_re, point_im;
				point_re = re.start + re_step * i;
				point_im = im.start + im_step * j;

				auto complex = std::complex<double>{point_re, point_im};
				auto converges = is_mandlebrot(complex);

        auto color = &buffer[3 * (j * x + i)];
				color[0] = converges ?  50 : 0;
				color[1] = converges ? 150 : 0;
				color[2] = converges ? 250 : 0;
			}
		}

		return;
	}
};
