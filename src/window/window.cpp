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

void print_sdl_img_error(const char* msg) {
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
        print_sdl_img_error("SDL_image could not initialize: ");
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

SDL_Surface* Window::load_surface(const char* path) const {
    // final optimized image
    SDL_Surface* optimized_surface = NULL;

    SDL_Surface* loaded_surface = IMG_Load( path );
    if (loaded_surface == NULL) {
        std::string err_msg = "could not load image with path: ";
        err_msg += path;
        print_sdl_img_error(err_msg.data());
        throw std::runtime_error(err_msg.data());
    }

    optimized_surface = SDL_ConvertSurface(loaded_surface, this->window_surface->format, 0);
    if (optimized_surface == NULL) {
        std::string err_msg ="unable to optimze surface with path: "; 
        err_msg += path;
        print_sdl_error(err_msg.data());
        throw std::runtime_error(err_msg.data());
    }

    SDL_FreeSurface(loaded_surface);

    return optimized_surface;
}

}
