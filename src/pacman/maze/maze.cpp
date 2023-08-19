#include "maze.hpp"

// TODO way to setup maze?
Maze::Maze(Entity&& player, std::vector<Entity>&& ghosts) :
ghosts(std::move(ghosts)), player(std::move(player))
{
    const int layout[side_length * side_length] = {/*TODO*/};
    load_layout_into_cells(layout);

    for (int row = 0; row < side_length; row++){
        for (int col = 0; col < side_length; col++){
            std::cout << this->cells[row][col];
        }
        std::cout << std::endl;
    }

    // position player and ghosts 
    // TODOS:
    // how to render them
    // how to determine positions
    // move mechanics and collisions
}

