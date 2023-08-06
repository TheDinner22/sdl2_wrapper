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

void MyTexture::render( int x, int y, SDL_Rect* clip) const {
    SDL_Rect render_quad = {x, y, this->width, this->height};

    // TODO make it so i can render to entire screen if i want
    // just me but i prefer the image fit the screen
    // this code is not part of tutorial
    // render_quad.w = SCREEN_WIDTH;
    // render_quad.h = SCREEN_HEIGHT;

    // if there is a clip apply it
    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    // render to screen
    SDL_RenderCopy(renderer, this->texture, clip, &render_quad);
}

int MyTexture::get_width(){ return this->width; }
int MyTexture::get_height(){ return this->height; }

