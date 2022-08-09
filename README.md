# mandlebrot-zoom
Mandlebrot zoomer with 2 implementations:
  * multi-threaded cpu implementation using all available cores
  * cuda implementation

## Building
 `make cpu` for cpu version

 `make cuda` for cuda version

## Running
  `mandelbrot [width] [height]`

### TODO
64bit floats run out of precision pretty quick, an implementaions using 128bit precision should be able to zoom more but would be considerably slower.
