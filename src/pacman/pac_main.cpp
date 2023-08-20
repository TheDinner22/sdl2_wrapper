#include <iostream>
#include <vector>
#include "window/window.hpp"
#include "entity/entity.hpp"
#include "pacman/maze/maze.hpp"
#include "SDL2/SDL.h"

// how to fps (disable vsync)
// how to rotate
// how to collisions
// add rendering of lines, rects, and circles
// how to render fonts

void pac_main(){
    Window win("pacman", 600, 600);

    Entity maze_pacman("images/pacman/pacman.png", win);
    std::vector<Entity> ghosts;
    Maze test_maze(std::move(maze_pacman), std::move(ghosts));

    bool done = false;
    while(!done) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                done = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                test_maze.handle_key_press(e.key.keysym.sym);
            }
        }

        test_maze.tick();

        test_maze.draw();
        win.update_screen();
    }
}
