#include <iostream>
#include "window/window.hpp"
#include "entity/entity.hpp"
#include "SDL2/SDL.h"

// how to fps (disable vsync)
// how to rotate
// how to collisions
// add rendering of lines, rects, and circles
// how to render fonts

void pac_main(){
    Window win("pacman", 600, 600);

    Entity pacman("images/pacman/pacman.png", win);

    bool done = false;
    while(!done) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                done = true;
            }
        }

        pacman.x ++;

        pacman.draw();
        win.update_screen();
    }
}
