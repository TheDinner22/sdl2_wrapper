#include "window/window.hpp"
#include "texture/texture.hpp"

#include <iostream>

// add better rendering (x, y, w, h)
// you can move textures?
// events?
// maybe a class that has a texture which is 
// aware of "where it is" or something
// move the error stuff to another file

void alpha_mod_test(const Window& win){
    MyTexture t = win.load_texture_from_file("images/wed.png");
    t.enable_alpha_modulation();

    uint8_t a = 255;
    while(true){
        t.set_alpha(a);

        t.render(0, 0);
        a--;

        if (a == 0) {break;}

        win.update_screen();
    }
}

void color_key_test (const Window& win) {
    RBGColor color = {0, 255, 255};
    MyTexture bg = win.load_texture_from_file("images/background.png");
    MyTexture man = win.load_texture_from_file("images/foo.png", color);

    bg.render(0, 0);
    man.render(200, 200);

    win.update_screen();
    
    // just to make the program not insta die
    int b;
    std::cin >> b;
}

void bg_color_test (const Window& win) {
    RBGColor bg_color = {0, 255, 255};
    MyTexture bg = win.load_texture_from_file("images/background.png");

    // here because we set bg color after render
    win.update_screen(bg_color);
    bg.render(0, 0);
    win.update_screen(bg_color);

    
    // just to make the program not insta die
    int b;
    std::cin >> b;
}

int main() {
    const int SCREEN_WIDTH = 650;
    const int SCREEN_HEIGHT = 650;

    Window win("test window", SCREEN_WIDTH, SCREEN_HEIGHT);
    alpha_mod_test(win);

    color_key_test(win);

    bg_color_test(win);
}
