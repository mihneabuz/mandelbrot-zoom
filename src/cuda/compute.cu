#include "compute.h"

#include <thrust/complex.h>

#include <cstdint>

#define MAX_ITER 100

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
		int x, int y,
		uint8_t* buffer
) {

	printf("heloo!!!??");

	int i, j;
	i = blockIdx.x;
	j = threadIdx.x;

	double point_re = re_start + re_step * x;
	double point_im = im_start + im_step * y;

	thrust::complex<double> c(point_re, point_im);
	thrust::complex<double> z(0, 0);

	auto iter = 0;
	while (thrust::abs(z) <= 2 && iter < MAX_ITER) {
		z = z * z + c;
		iter++;
	}

	int addr = 3 * (j * x + i);
	buffer[addr] = 255;
	buffer[addr + 1] = 255;
	buffer[addr + 1] = 255;
}


void cuda_compute(
		double re_start, double re_end,
		double im_start, double im_end,
		int x, int y,
		uint8_t* buffer
	) {

	int bufferSize = x * y * 3 * sizeof(uint8_t);
	uint8_t *cudaBuffer;
	gpuErrchk(cudaMalloc(&cudaBuffer, bufferSize));

	const double re_step = (re_end - re_start) / x;
	const double im_step = (im_end - im_start) / y;

  kernel<<<100, 100>>>(re_start, re_step, im_start, im_step, x, y, cudaBuffer);

	gpuErrchk(cudaPeekAtLastError());
	gpuErrchk(cudaDeviceSynchronize());

  cudaMemcpy(buffer, cudaBuffer, bufferSize, cudaMemcpyDeviceToHost);

  cudaFree(cudaBuffer);
}
