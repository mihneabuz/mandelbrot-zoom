#pragma once

#include <complex>
#include <thread>
#include <vector>

#include "calculator.hpp"

#define MAX_ITER 100

template <typename T, int I> inline int is_mandlebrot(const std::complex<T> c) {
	std::complex<T> z{0, 0};

	auto i = 0;
	while (std::abs(z) <= 2 && i < I) {
		z = z * z + c;
		i++;
	}

	return i;
}

template <int I> inline void iter_to_color(const int iter, Uint8 *color) {
	auto gradient =  (double)(iter * iter) / (I * I);
	color[0] =  50 * gradient;
	color[1] = 150 * gradient;
	color[2] = 250 * gradient;
}

template <typename T>
struct thread_args {
	T re_start, re_step;
	T im_start, im_step;
	int start_x, end_x, x, y;
	Uint8* buffer;
};

template <typename T, int I> void thread_func(thread_args<T> args) {
	T point_re = args.re_start + args.re_step * args.start_x;
	for (auto i = args.start_x; i < args.end_x; i++) {
		T point_im = args.im_start;
		for (auto j = 0; j < args.y; j++) {
			const auto iter = is_mandlebrot<T, I>(std::move(std::complex<T>{point_re, point_im}));
			const auto color = &args.buffer[3 * (j * args.x + i)];

			iter_to_color<I>(iter, color);

			point_im += args.im_step;
		}

		point_re += args.re_step;
	}
}

template <typename T, int I> class CPU_Calculator : public Calculator {
public:
	CPU_Calculator<T, I>() {};

	void compute(range re, range im, int x, int y, Uint8* buffer) {
		const T re_step = (re.end - re.start) / x;
		const T im_step = (im.end - im.start) / y;

		thread_args<T> args;
		args.im_step = im_step;
		args.re_step = re_step;
		args.x = x;
		args.y = y;
		args.buffer = buffer;

		const int num_processors = std::thread::hardware_concurrency();
		std::vector<std::thread> threads(num_processors);

		for (auto i = 0; i < num_processors; i++) {
			args.start_x = (x / num_processors) * i;
			args.end_x   = (x / num_processors) * (i + 1);
			threads.emplace_back(thread_func<T, I>, args);
		}

		for (auto &thread: threads) {
			if (thread.joinable())
				thread.join();
		}
	}
};
