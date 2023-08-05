#pragma once

#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h> //

namespace Wrapper {

void print_sdl_error(const char* msg);

void print_sdl_img_error(const char* msg);

class Window {
private:
    SDL_Window* window;
    SDL_Surface* window_surface;

    SDL_Renderer* renderer = NULL;
public:
    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;

    // flags should be OR'd together 
    // (if more than one)
    Window(
            const char* window_name,
            int screen_width,
            int screen_height,
            unsigned int flags = SDL_INIT_VIDEO
          );

    ~Window();

    // you are responsible for this pointer!
    // TODO surface class
    SDL_Surface* load_surface(const char* path) const;
};

}

