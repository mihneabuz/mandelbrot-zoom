#include <cstdint>

void cuda_compute(
		double re_start, double re_end,
		double im_start, double im_end,
		int x, int y,
		uint8_t* buffer
	);
