#include "renderer.hpp"

#include <iostream>

SDL_Renderer* create_renderer(int height, int width) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error: SDL failed to initialize\nSDL Error: '%s'\n" << SDL_GetError();
        return nullptr;
    }

    SDL_Window *window = SDL_CreateWindow("Mandlebrot zoomer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    if (!window) {
        std::cout << "Error: Failed to open window\nSDL Error: '%s'\n" << SDL_GetError();
        return nullptr;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Error: Failed to create renderer\nSDL Error: '%s'\n" << SDL_GetError();
        return nullptr;
    }

    return renderer;
}
