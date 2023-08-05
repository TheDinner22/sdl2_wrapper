#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.hpp"

namespace Wrapper {

MyTexture::MyTexture() {}

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
