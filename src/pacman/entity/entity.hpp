#pragma once

#include "texture/texture.hpp"

// its just a textrue paired with an x, y coordinate pair
class Entity {
private:
    MyTexture texture;
public:
    int x, y;

    Entity(const char* filename, const Window& win, std::optional<RBGColor> color_key_color = std::nullopt);

    void set_width(int width);
    void set_height(int height);

    void draw();
};
