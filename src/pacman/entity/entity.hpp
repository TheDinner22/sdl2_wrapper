#pragma once

#include <SDL2/SDL.h>
#include <utility>
#include "texture/texture.hpp"

// its just a textrue paired with an x, y coordinate pair
class Entity {
private:
    MyTexture texture;
    double angle;
public:
    int x, y;

    Entity(const char* filename, const Window& win, std::optional<RBGColor> color_key_color = std::nullopt);

    void set_width(int width);
    void set_height(int height);

    void rotate_clock_wise(double angle);
    void rotate_counter_clock_wise(double angle);

    SDL_Point center() const;

    void draw() const;
};
