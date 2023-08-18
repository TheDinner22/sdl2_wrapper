#pragma once

// forward declarations
class Window;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdexcept>
#include <optional>

#include "errors/errors.hpp"

class RBGColor {
public:
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    // default was taken :p
    static RBGColor defaultt() {
        RBGColor color = {255, 255, 255};
        return color;
    }
};

//Texture wrapper class
class MyTexture {
public:
    // starts as initial image dimensions
    int width;
    int height;
private:
    friend class Window;

    SDL_Texture* texture;

    // info about the window and render
    SDL_Window* window;
    SDL_Renderer* renderer;

    // cannot make this class directly 
    // call the method on the window class
    MyTexture(const char* img_path, SDL_Window* window, SDL_Renderer* renderer, std::optional<RBGColor> color_key_color = std::nullopt) 
    : window(window), renderer(renderer)
    {
        // load the surface
        SDL_Surface* loaded_surface = this->load_unoptimized_surface(img_path);
        if (loaded_surface == NULL) {
            std::cout << "unreachable" << std::endl;
        }

        // color key image
        // pass the surface to color key, the second arg is whether or not to enable
        // color keying, and the third is the pixel we want to color key with
        // SDL_MapRGB lets us create a pixel from a color and format these values map to cyan pixels
        if(color_key_color.has_value()) {
            SDL_SetColorKey(
                loaded_surface,
                SDL_TRUE,
                SDL_MapRGB(loaded_surface->format, color_key_color->r, color_key_color->g, color_key_color->b)
            );
        }

        // convert into texture
        this->texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (this->texture == NULL) {
            std::string err_msg = "unable to create texture from surface with path:";
            err_msg += img_path;
            print_sdl_error(err_msg.data());
            throw std::runtime_error(err_msg.data());
        }

        this->width = loaded_surface->w;
        this->height = loaded_surface->h;

        // free surface
        SDL_FreeSurface(loaded_surface);
    }

    // you are responsible for this pointer!
    SDL_Surface* load_unoptimized_surface(const char* path) const {
        SDL_Surface* loaded_surface = IMG_Load( path );
        if (loaded_surface == NULL) {
            std::string err_msg = "could not load image with path: ";
            err_msg += path;
            print_sdl_img_error(err_msg.data());
            throw std::runtime_error(err_msg.data());
        }

        return loaded_surface;
    }

    // free destroys the surface
    // which might not be what you want if 
    // you just moved the texture
    void free() {
        if (this->texture != NULL) {
            SDL_DestroyTexture(this->texture);
            this->texture = NULL;
            this->width = 0;
            this->height = 0;
            this->window = NULL;
            this->renderer = NULL;
        }
    }
public:
    // cannot copy this class
    MyTexture(const MyTexture& other) = delete;
    MyTexture& operator=(const MyTexture& other) = delete;

    // move stuff
    MyTexture(MyTexture&& rhs);
    MyTexture& operator=(MyTexture&& rhs);

    ~MyTexture();

    // set color modulation
    void set_color(uint8_t red, uint8_t green, uint8_t blue);

    // alpha modulation stuff
    void enable_alpha_modulation();
    void set_blend_mode(SDL_BlendMode blending);
    void set_alpha(uint8_t alpha);

    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

