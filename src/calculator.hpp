#pragma once

#include "SDL2/SDL_stdinc.h"
#include "utils.hpp"

class Calculator {
public:
	virtual void compute(range re, range im, int x, int y, Uint8* buffer) = 0;
};
