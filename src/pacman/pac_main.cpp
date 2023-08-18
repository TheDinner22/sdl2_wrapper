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
    unsigned int frame = 0;
    Window win("pacman", 600, 600);

    Entity pacman("images/pacman/pacman.png", win);

    bool done = false;
    while(!done) {
        frame += 1;
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                done = true;
            }
        }

        if (frame % 10 == 0) {
            pacman.x ++;
            pacman.rotate_clock_wise(90);
        }

        pacman.draw();
        win.update_screen();
    }
}
