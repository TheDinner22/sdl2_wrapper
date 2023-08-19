#include "pacman/entity/entity.hpp"
#include <iostream>
#include <vector>

enum CellState {
    EMPTY,
    WALL,
    PELLET,
    POWER_PELLET,
};

enum Move {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Maze {
private:
    static const int side_length = 30;
    // cells[row][col]
    CellState cells[side_length][side_length];

    std::vector<Entity> ghosts;
    Entity player;

    // ()'s group & and layout becuase this is a ref to slice not slice of ref's
    void load_layout_into_cells(const int (&layout) [side_length * side_length]) {
        int col = 0;
        int row = 0;
        for (int cell_val : layout) {
            if(!(col < side_length)) {
                col = 0;
                row++;
            }

            this->cells[row][col] = (CellState)cell_val;

            col++;
        }
    }

public:
    // TODO way to setup maze?
    Maze(Entity&& player, std::vector<Entity>&& ghosts) :
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
};

