#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "window/window.hpp"


namespace Wrapper {
    
//Texture wrapper class
class MyTexture {
private:
    //The actual hardware texture
    SDL_Texture* texture;

    //initial image dimensions
    int width;
    int height;

    void free() {
        if (this->texture != NULL) {
            SDL_DestroyTexture(this->texture);
            this->texture = NULL;
            this->width = 0;
            this->height = 0;
        }
    }
public:
    MyTexture(const MyTexture& other) = delete;
    MyTexture& operator=(const MyTexture& other) = delete;

    //Initializes variables
    MyTexture(const char* img_path, const Window& window);

    //Deallocates memory
    ~MyTexture();

    //Loads image at specified path
    bool load_from_file( const char* path );

    // set color modulation
    void set_color(uint8_t red, uint8_t green, uint8_t blue);

    // alpha modulation stuff
    void set_blend_mode(SDL_BlendMode blending);
    void set_alpha(uint8_t alpha);

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL );

    //Gets image dimensions
    int get_width();
    int get_height();
};

}
