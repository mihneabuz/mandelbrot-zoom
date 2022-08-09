#include "compute.h"

#include <thrust/complex.h>

#include <cstdint>

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess)
   {
      fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}

__global__ void kernel(
		double re_start, double re_step,
		double im_start, double im_step,
		int start_x, int start_y,
		int x, int y,
		uint8_t* buffer,
    int max_iter
) {
	const auto i = start_x + blockIdx.x;
	const auto j = start_y + threadIdx.x;

	if (i >= x || j >= y)
		return;

	const double point_re = re_start + re_step * i;
	const double point_im = im_start + im_step * j;

	const thrust::complex<double> c(point_re, point_im);
	thrust::complex<double> z(0, 0);

	auto iter = 0;
	while (thrust::abs(z) <= 200 && iter < max_iter) {
		z = z * z + c;
		iter++;
	}

	float gradient = (float)(iter * iter) / (max_iter * max_iter);
	int addr = 3 * (j * x + i);

	buffer[addr]     =  70 * gradient;
	buffer[addr + 1] =  20 * gradient;
	buffer[addr + 2] = 250 * gradient;
}

const int kern = 720;

void cuda_compute(
		double re_start, double re_end,
		double im_start, double im_end,
		int x, int y,
		uint8_t* buffer,
    int max_iter
	) {

	int bufferSize = x * y * 3 * sizeof(uint8_t);
	uint8_t *cudaBuffer;
	cudaMalloc(&cudaBuffer, bufferSize);

	const double re_step = (re_end - re_start) / x;
	const double im_step = (im_end - im_start) / y;

	auto i = 0;
	while (i < x) {
		auto j = 0;
		while (j < y) {
			kernel<<<kern, kern>>>(re_start, re_step, im_start, im_step, i, j, x, y, cudaBuffer, max_iter);
			j += kern;
		}
		i += kern;
	}

	cudaDeviceSynchronize();

  cudaMemcpy(buffer, cudaBuffer, bufferSize, cudaMemcpyDeviceToHost);

  cudaFree(cudaBuffer);
}
