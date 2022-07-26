CXX = g++.exe
LIB = -lmingw32 -lSDL2main -lSDL2
SDL = -Isdl/include -Lsdl/lib
OPT = -O3

mandlebrot: build/renderer.o src/main.cpp
	$(CXX) $(SDL) -o mandlebrot.exe src/main.cpp build/*.o $(LIB) $(OPT)

build/renderer.o: src/renderer.cpp
	$(CXX) $(SDL) -c -o build/renderer.o src/renderer.cpp $(LIB) $(OPT)

clean:
	rm -f mandlebrot.exe test.exe build/*.o

test: test_sdl.cpp
	$(CXX) $(SDL) -o test.exe test_sdl.cpp $(LIB)

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
