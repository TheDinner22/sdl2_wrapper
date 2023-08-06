#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <string>

#include "texture.hpp"
#include "window/window.hpp"

MyTexture::~MyTexture() { this->free(); }

// set color modulation
void MyTexture::set_color(uint8_t red, uint8_t green, uint8_t blue){
    SDL_SetTextureColorMod(this->texture, red, green, blue);
}

// alpha modulation stuff
void MyTexture::set_blend_mode(SDL_BlendMode blending){
    SDL_SetTextureBlendMode(this->texture, blending);
}
void MyTexture::set_alpha(uint8_t alpha){
    SDL_SetTextureAlphaMod(this->texture, alpha);
}

void MyTexture::render( int x, int y, SDL_Rect* clip){}

int MyTexture::get_width(){}
int MyTexture::get_height(){}

