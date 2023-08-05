#pragma once

#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h> //

namespace Wrapper {

class Window {
    private:
        SDL_Window* window;
        SDL_Surface* window_surface;
    public:
        // flags should be OR'd together 
        // (if more than one)
        Window(
                const char* window_name,
                int screen_width,
                int screen_height,
                unsigned int flags = SDL_INIT_VIDEO
              );

        ~Window();
};

}

