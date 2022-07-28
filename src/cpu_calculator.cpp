#include "cpu_calculator.hpp"

inline int is_mandlebrot(const std::complex<double> c) {
	std::complex<double> z{0, 0};

	auto i = 0;
	while (std::abs(z) <= 2 && i < MAX_ITER) {
		z = z * z + c;
		i++;
	}

	return i;
}

inline void iter_to_color(const int iter, Uint8 *color) {
	float gradient = (float)(iter * iter) / (MAX_ITER * MAX_ITER);
	color[0] =  70 * gradient;
	color[1] =  20 * gradient;
	color[2] = 250 * gradient;
}

typedef struct {
	double re_start, re_step;
	double im_start, im_step;
	int start_x, end_x, x, y;
	Uint8* buffer;
} thread_args;


void thread_func(thread_args args) {
	double point_re = args.re_start + args.re_step * args.start_x;
	for (auto i = args.start_x; i < args.end_x; i++) {
		double point_im = args.im_start;
		for (auto j = 0; j < args.y; j++) {
			const auto iter = is_mandlebrot(std::move(std::complex<double>{point_re, point_im}));
			const auto color = &args.buffer[3 * (j * args.x + i)];

			iter_to_color(iter, color);

			point_im += args.im_step;
		}

		point_re += args.re_step;
	}
}

void CPU_Calculator::compute(range re, range im, int x, int y, Uint8* buffer) {
	const double re_step = (re.end - re.start) / x;
	const double im_step = (im.end - im.start) / y;

	thread_args args;
	args.im_start = im.start;
	args.re_start = re.start;
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
		threads.emplace_back(thread_func, args);
	}

	for (auto &thread: threads) {
		if (thread.joinable())
			thread.join();
	}
}
