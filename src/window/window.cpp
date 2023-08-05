#include <iostream> //
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h> //
#include <stdexcept> //
#include <string> //

#include "window.hpp" //

namespace Wrapper {

void print_sdl_error(const char* msg) {
    std::cout << msg << SDL_GetError() << std::endl;
}

void print_img_error(const char* msg) {
    std::cout << msg << IMG_GetError() << std::endl;
}

void init_sdl_and_libs(unsigned int flags){
    // init SDL
    bool success = SDL_Init( flags ) == 0;
    if (!success) {
        print_sdl_error("could not init sdl: ");
        throw std::runtime_error("could not init sdl");
    }

    // init IMG
    int img_init_flags = IMG_INIT_PNG;
    bool img_init_worked = IMG_Init(img_init_flags) & img_init_flags;
    if (!img_init_worked) {
        print_img_error("SDL_image could not initialize: ");
        throw std::runtime_error("SDL_image could not initialize");
    }
}

Window::Window(
    const char* window_name,
    int screen_width,
    int screen_height,
    unsigned int flags
)
{
    init_sdl_and_libs(flags);

    //Create window
    window = SDL_CreateWindow( 
        window_name,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screen_width,
        screen_height,
        SDL_WINDOW_SHOWN
    );
    if( window == NULL )
    {
        print_sdl_error("could not create window: ");
        throw std::runtime_error("could not create window");
    }
    window_surface = SDL_GetWindowSurface(window);

    // create renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == NULL) {
        print_sdl_error("could not create renderer");
    }
    // set renderer color
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255); 
}

Window::~Window(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(this->renderer);

    IMG_Quit();
    SDL_Quit();
}

}
