#include <SDL2/SDL.h>

#include "entity.hpp"
#include "texture/texture.hpp"
#include "window/window.hpp"

Entity::Entity(const char* img_path, const Window& win, std::optional<RBGColor> color_key_color) : 
    texture(win.load_texture_from_file(img_path, color_key_color)),
    angle(0.0),
    x(0),
    y(0)
{}

void Entity::set_width(int width){
    this->texture.width = width;
}
void Entity::set_height(int height){
    this->texture.height = height;
}

void Entity::rotate_clock_wise(double angle){
    this->angle += angle;
}

void Entity::rotate_counter_clock_wise(double angle){
    this->angle -= angle;
}

void Entity::draw() const {
    this->texture.render(this->x, this->y, NULL, this->angle);
}

SDL_Point Entity::center() const {
    const int x = this->x + this->texture.width / 2;
    const int y = this->y + this->texture.height / 2;
    auto center = SDL_Point();
    center.x = x;
    center.y = y;
    return center;
}

