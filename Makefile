test_sdl:
	g++ -Isdl/include -Lsdl/lib -o test test_sdl.cpp -lmingw32 -lSDL2main -lSDL2

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
