#include "SDL_surface.h"
#include <iostream> //
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h> //
#include <stdexcept> //
#include <string> //

namespace Wrapper {

void print_sdl_error(const char* msg) {
    std::cout << msg << SDL_GetError() << std::endl;
}

void print_img_error(const char* msg) {
    std::cout << msg << IMG_GetError() << std::endl;
}

class SdlSurface {
private:
    SDL_Surface* surface;
public:
    // trys to load the path as an image
    SdlSurface(const char* path){
        // could this be this class TODO
        SDL_Surface* loaded_surface = IMG_Load(path);
        if(loaded_surface == NULL){
            std::string err_msg = "could not load surface: ";
            err_msg += path;
            print_img_error(err_msg.data());
            throw std::runtime_error(err_msg.data());
        }

        this->surface = SDL_ConvertSurfaceFormat(
            loaded_surface,
            1, // TTODOTODOTODOTODOTODOTODOTODOTODOTODOODO
            0
        );
        if (this->surface == NULL){
            std::string err_msg = "could not optimize surface: ";
            err_msg += path;
            print_img_error(err_msg.data());
            throw std::runtime_error(err_msg.data());
        }

        SDL_FreeSurface(loaded_surface);
    }

    ~SdlSurface(){
        SDL_FreeSurface(surface);
    }
};

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
    )
    {
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
    }

    ~Window(){
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

}
