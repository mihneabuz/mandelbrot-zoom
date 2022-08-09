CXX = g++
LIB = -lSDL2main -lSDL2
SDL = -Isdl/include -Lsdl/lib
OPT = -Ofast
CUDA = -L/opt/cuda/targets/x86_64-linux/lib -lcuda -lcudart

cpu: build/renderer.o build/cpu_calculator.o src/main.cpp
	$(CXX) $(SDL) -o mandelbrot src/main.cpp build/*.o $(LIB) $(OPT)

cuda: build/renderer.o build/cpu_calculator.o build/cuda_compute.o src/main.cpp
	$(CXX) $(SDL) -o mandelbrot src/main.cpp build/*.o $(LIB) $(OPT) $(CUDA)

build/renderer.o: src/renderer.cpp
	$(CXX) $(SDL) -c -o build/renderer.o src/renderer.cpp $(LIB) $(OPT)

build/cpu_calculator.o: src/cpu_calculator.cpp
	$(CXX) $(SDL) -c -o build/cpu_calculator.o src/cpu_calculator.cpp $(LIB) $(OPT)

build/cuda_compute.o: src/cuda/compute.cu
	nvcc -c -o build/cuda_compute.o src/cuda/compute.cu

clean:
	rm -f mandlebrot test build/*.o

test: test_sdl.cpp
	$(CXX) $(SDL) -o test test_sdl.cpp $(LIB)

download_sdl:
	rm -rf sdl
	wget https://www.libsdl.org/release/SDL2-devel-2.0.22-mingw.zip
	unzip SDL2-devel-2.0.22-mingw.zip
	mkdir sdl
	mv ./SDL2-2.0.22/x86_64-w64-mingw32/lib ./sdl
	mv ./SDL2-2.0.22/x86_64-w64-mingw32/include ./sdl
	mv ./SDL2-2.0.22/x86_64-w64-mingw32/bin/SDL2.dll .
	rm -f SDL2-devel-2.0.22-mingw.zip
	rm -rf SDL2-2.0.22
