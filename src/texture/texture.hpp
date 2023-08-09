#pragma once

// forward declarations
class Window;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

//Texture wrapper class
class MyTexture {
private:
    friend class Window;

    SDL_Texture* texture;

    //initial image dimensions
    int width;
    int height;

    // info about the window and render from the generator
    SDL_Window* window;
    SDL_Surface* window_surface; // TODO remove this member (we dont need it)
    SDL_Renderer* renderer;

    // https://stackoverflow.com/questions/28334485/do-c-private-functions-really-need-to-be-in-the-header-file
    MyTexture(const char* img_path, SDL_Surface* loaded_surface, SDL_Window* window, SDL_Surface* window_surface, SDL_Renderer* renderer) 
    : window(window), window_surface(window_surface), renderer(renderer)
    {
        // TODO add color keying later
        // color key image
        // pass the surface to color key, the second are is whether or not to enable
        // color keying, and the third is the pixel we want to color key with
        // SDL_MapRGB lets us create a pixel from a color and format these values map to cyan pixels
        // SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 255, 255) );

        // now that we have enabled color keying for the surface
        // we convert it into a texture
        this->texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (this->texture == NULL) {
            std::string err_msg = "unable to create texture from surface with path:";
            err_msg += img_path;
            // TODO uncomment this
            // print_sdl_error(err_msg.data());
            throw std::runtime_error(err_msg.data());
        }

        this->width = loaded_surface->w;
        this->height = loaded_surface->h;
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
            this->window_surface = NULL;
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

    int get_width();
    int get_height();
};

