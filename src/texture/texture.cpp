#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <iostream>
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

void MyTexture::enable_alpha_modulation(){
    this->set_blend_mode(SDL_BLENDMODE_BLEND);
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

// move constructor
MyTexture::MyTexture(MyTexture&& rhs) :
    width(rhs.width),
    height(rhs.height),
    texture(rhs.texture),
    window(rhs.window),
    renderer(rhs.renderer)
{
    rhs.texture = NULL;
    rhs.width = 0;
    rhs.height = 0;
    rhs.window = NULL;
    rhs.renderer = NULL;
}

// i have no clue how to implement this and 
// am operating on pure guesswork
// the cpp reference is more confusing than the 
// enigma codes
/*
MyTexture& MyTexture::operator=(MyTexture&& rhs) {
    this->free();

    this->texture = rhs.texture;
    this->width = rhs.width;
    this->height = rhs.height;
    this->window = rhs.window;
    this->renderer = rhs.renderer;

    rhs.texture = NULL;
    rhs.width = 0;
    rhs.height = 0;
    rhs.window = NULL;
    rhs.renderer = NULL;

    return *this;
}
*/

