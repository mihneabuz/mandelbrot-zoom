#include "renderer.hpp"

#include <iostream>

Renderer::Renderer(int width, int height) {
  this->width = width;
  this->height = height;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Error: SDL failed to initialize\nSDL Error: '%s'\n" << SDL_GetError();
    exit(1);
  }

  window = SDL_CreateWindow("Mandlebrot zoomer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
  if (!window) {
    std::cout << "Error: Failed to open window\nSDL Error: '%s'\n" << SDL_GetError();
    exit(2);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cout << "Error: Failed to create renderer\nSDL Error: '%s'\n" << SDL_GetError();
    exit(3);
  }

  buffer = new Uint8[width * height * 3];
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

  has_calculator = false;
}

void Renderer::attach_calculator(Calculator *calc) {
  calculator = calc;
  has_calculator = true;
}

void Renderer::start(range re, range im) {
  if (!has_calculator) {
    std::cout << "Error: No calculator injected\n";
    exit(4);
  }

  void *pixels;
  int pitch;

  bool done = false;
  while (!done) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        done = true;
        break;

      default:
        break;
      }
    }

		calculator->compute(re, im, width, height, buffer);

    SDL_LockTexture(texture, NULL, &pixels, &pitch);
    for (auto y = 0; y < height; y++) {
      auto dst = (Uint32*)((Uint8*)pixels + y * pitch);
      for (auto x = 0; x < width; x++) {
        auto color = &buffer[3 * (y * width + x)];
        *dst++ = (0xFF000000 | color[0] << 16 | color[1] << 8 | color[2]);
      }
    }
    SDL_UnlockTexture(texture);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
