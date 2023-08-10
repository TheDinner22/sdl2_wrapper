#include "errors.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void print_sdl_error(const char* msg) {
    std::cout << msg << std::endl << SDL_GetError() << std::endl << std::endl;
}

void print_sdl_img_error(const char* msg) {
    std::cout << msg << std::endl << IMG_GetError() << std::endl << std::endl;
}

