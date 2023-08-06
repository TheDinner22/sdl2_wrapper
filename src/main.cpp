#include "window/window.hpp"
#include "texture/texture.hpp"

#include <iostream>

int main() {
    const int SCREEN_WIDTH = 650;
    const int SCREEN_HEIGHT = 650;

    Window win("test window", SCREEN_WIDTH, SCREEN_HEIGHT);

    MyTexture t = win.load_texture_from_file("images/wed.png");

    // t.render(SCREEN_WIDTH, SCREEN_HEIGHT);

    // just to make the program not insta die
    int a;
    std::cin >> a;
}
