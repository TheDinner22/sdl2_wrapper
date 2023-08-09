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

// move constructor
MyTexture::MyTexture(MyTexture&& rhs) :
    texture(rhs.texture),
    width(rhs.width),
    height(rhs.height),
    window(rhs.window),
    window_surface(rhs.window_surface),
    renderer(rhs.renderer)
{
    rhs.texture = NULL;
    rhs.width = 0;
    rhs.height = 0;
    rhs.window = NULL;
    rhs.window_surface = NULL;
    rhs.renderer = NULL;
}

// i have no clue how to implement this and 
// am operating on pure guesswork
// the cpp reference is more confusing than the 
// enigma codes
// TODO implement this and test the move constructor
MyTexture& MyTexture::operator=(MyTexture&& rhs) {
    this->free();

    this->texture = rhs.texture;
    this->width = rhs.width;
    this->height = rhs.height;
    this->window = rhs.window;
    this->window_surface = rhs.window_surface;
    this->renderer = rhs.renderer;

    rhs.texture = NULL;
    rhs.width = 0;
    rhs.height = 0;
    rhs.window = NULL;
    rhs.window_surface = NULL;
    rhs.renderer = NULL;

    return *this;
}

