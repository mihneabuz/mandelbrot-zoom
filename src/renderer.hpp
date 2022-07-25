#pragma once

#include "SDL2/SDL_render.h"
#include <SDL2/SDL.h>

#include "SDL2/SDL_stdinc.h"
#include "calculator.hpp"

class Renderer {
public:
  Renderer(int width, int height);
	void attach_calculator(Calculator *calc);
	void start(range re, range im);
	~Renderer();

private:
	int width, height;

  SDL_Window *window;
  SDL_Renderer *renderer;

	Uint8 *buffer;
	SDL_Texture *texture;

	bool has_calculator;
	Calculator *calculator;
};
