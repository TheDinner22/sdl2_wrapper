#include "entity.hpp"
#include "texture/texture.hpp"
#include "window/window.hpp"

/*
class Entity {
private:
    MyTexture texture;
public:
    int x, y;

};
*/
Entity::Entity(const char* img_path, const Window& win, std::optional<RBGColor> color_key_color) : 
    texture(win.load_texture_from_file(img_path, color_key_color)),
    x(0),
    y(0)
{}

void Entity::set_width(int width){
    this->texture.width = width;
}
void Entity::set_height(int height){
    this->texture.height = height;
}

void Entity::draw(){
    this->texture.render(this->x, this->y);
}
