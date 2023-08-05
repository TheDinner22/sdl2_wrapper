#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window/window.hpp"

namespace Wrapper {

class Renderer {
private:
    SDL_Renderer* renderer = NULL;
public:
    Renderer(const Window& window);
    ~Renderer();
};

}
