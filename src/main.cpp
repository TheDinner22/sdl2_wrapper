#include "window/window.hpp"
#include "texture/texture.hpp"

#include <iostream>

// add color keying
// add better rendering (x, y, w, h)
// you can move textures?
// events?
// maybe a class that has a texture which is 
// aware of "where it is" or something
// move the error stuff to another file

int main() {
    const int SCREEN_WIDTH = 650;
    const int SCREEN_HEIGHT = 650;

    Window win("test window", SCREEN_WIDTH, SCREEN_HEIGHT);

    MyTexture t = win.load_texture_from_file("images/wed.png");

    t.render(0, 0);

    win.update_screen();

    // just to make the program not insta die
    int a;
    std::cin >> a;
}
