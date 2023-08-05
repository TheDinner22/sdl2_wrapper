#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window/window.hpp"


namespace Wrapper {
    
//Texture wrapper class
class MyTexture {
private:
    friend class Window;

    //The actual hardware texture
    SDL_Texture* texture;

    //initial image dimensions
    int width;
    int height;

    // info about the window and render from the generator
    SDL_Window* window;
    SDL_Surface* window_surface;
    SDL_Renderer* renderer;

    // huge TODO impl this here and then make the window class a generator for this class or do something with this
    // https://stackoverflow.com/questions/28334485/do-c-private-functions-really-need-to-be-in-the-header-file
    MyTexture(const char* img_path, SDL_Window* window, SDL_Surface* window_surface, SDL_Renderer* renderer);

    void free() {
        if (this->texture != NULL) {
            SDL_DestroyTexture(this->texture);
            this->texture = NULL;
            this->width = 0;
            this->height = 0;
        }
    }
public:
    // cannot make or copy this class
    MyTexture() = delete;
    MyTexture(const MyTexture& other) = delete;
    MyTexture& operator=(const MyTexture& other) = delete;

    ~MyTexture();

    bool load_from_file( const char* path );

    // set color modulation
    void set_color(uint8_t red, uint8_t green, uint8_t blue);

    // alpha modulation stuff
    void set_blend_mode(SDL_BlendMode blending);
    void set_alpha(uint8_t alpha);

    void render( int x, int y, SDL_Rect* clip = NULL );

    int get_width();
    int get_height();
};

}
