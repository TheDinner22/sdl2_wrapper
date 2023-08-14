#include "entity.hpp"
#include "texture/texture.hpp"
#include "window/window.hpp"

/*
class Entity {
private:
    MyTexture texture;
    int width, height;
public:
    int x, y;

};
*/
Entity::Entity(const char* img_path, const Window& win, std::optional<RBGColor> color_key_color) :
    x(0), y(0)
{
    this->texture = win.load_texture_from_file(img_path, color_key_color);

    this->width = this->texture.width;
    this->height = this->texture.height;
}

// void set_width(int width);
// void set_height(int height);

// void draw();
