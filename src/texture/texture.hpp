#pragma once

// forward declarations
class Window;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdexcept>

//Texture wrapper class
class MyTexture {
public:
    // starts as initial image dimensions
    int width;
    int height;
private:
    friend class Window;

    SDL_Texture* texture;

    // info about the window and render from the generator
    SDL_Window* window;
    SDL_Renderer* renderer;

    // https://stackoverflow.com/questions/28334485/do-c-private-functions-really-need-to-be-in-the-header-file
    MyTexture(const char* img_path, SDL_Window* window, SDL_Renderer* renderer) 
    : window(window), renderer(renderer)
    {
        // TODO add color keying later
        // color key image
        // pass the surface to color key, the second are is whether or not to enable
        // color keying, and the third is the pixel we want to color key with
        // SDL_MapRGB lets us create a pixel from a color and format these values map to cyan pixels
        // SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 255, 255) );

        // load the surface
        SDL_Surface* loaded_surface = this->load_unoptimized_surface(img_path);
        if (loaded_surface == NULL) {
            std::cout << "unreachable" << std::endl;
        }

        // convert into texture
        this->texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (this->texture == NULL) {
            std::string err_msg = "unable to create texture from surface with path:";
            err_msg += img_path;
            // TODO uncomment this
            // print_sdl_error(err_msg.data());
            throw std::runtime_error(err_msg.data());
        }

        // free surface
        SDL_FreeSurface(loaded_surface);

        this->width = loaded_surface->w;
        this->height = loaded_surface->h;
    }

    // you are responsible for this pointer!
    SDL_Surface* load_unoptimized_surface(const char* path) const {
        SDL_Surface* loaded_surface = IMG_Load( path );
        if (loaded_surface == NULL) {
            std::string err_msg = "could not load image with path: ";
            err_msg += path;
            // TODO uncomment this
            // print_sdl_img_error(err_msg.data());
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
    MyTexture& operator=(MyTexture&& rhs) = delete;

    ~MyTexture();

    // set color modulation
    void set_color(uint8_t red, uint8_t green, uint8_t blue);

    // alpha modulation stuff
    void set_blend_mode(SDL_BlendMode blending);
    void set_alpha(uint8_t alpha);

    void render(int x, int y, SDL_Rect* clip = NULL) const;
};

