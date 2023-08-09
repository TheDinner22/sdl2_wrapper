#pragma once

#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h> //
#include <string> //
#include <stdexcept> //
#include <iostream>

#include "texture/texture.hpp" //

void print_sdl_error(const char* msg);

void print_sdl_img_error(const char* msg);

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    // haha no copying this class
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

    MyTexture load_texture_from_file(const char* img_path) const;

    void update_screen() const;
};

