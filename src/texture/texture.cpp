#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "texture.hpp"
#include "window/window.hpp"

namespace Wrapper {

MyTexture::MyTexture(const char* img_path, const Window& window) {
    SDL_Surface* loaded_surface = window.load_surface(img_path);
    if (loaded_surface == NULL) {
        return false;
    }

    // color key image
    // pass the surface to color key, the second are is whether or not to enable
    // color keying, and the third is the pixel we want to color key with
    // SDL_MapRGB lets us create a pixel from a color and format these values map to cyan pixels
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 255, 255) );

    // now that we have enabled color keying for the surface
    // we convert it into a texture
    loaded_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (loaded_texture == NULL) {
        std::string err_msg = "unable to create texture from surface with path:";
        err_msg += img_path;
        print_sdl_error(err_msg.data());
        return false;
    }

    this->width = loaded_surface->w;
    this->height = loaded_surface->h;

    SDL_FreeSurface(loaded_surface);

    this->texture = loaded_texture;
    return true;
}

MyTexture::~MyTexture() {}

bool MyTexture::load_from_file( const char* path ){}

// set color modulation
void MyTexture::set_color(uint8_t red, uint8_t green, uint8_t blue){}

// alpha modulation stuff
void MyTexture::set_blend_mode(SDL_BlendMode blending){}
void MyTexture::set_alpha(uint8_t alpha){}

void MyTexture::render( int x, int y, SDL_Rect* clip){}

int MyTexture::get_width(){}
int MyTexture::get_height(){}

}
