#pragma once

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
    Move player_move;
    

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
    Maze(Entity&& player, std::vector<Entity>&& ghosts);

    void draw() const;

    void tick();

    void handle_key_press(const SDL_Keycode& sym);
};

class Cell {
private:
    CellState state = EMPTY;
    int x, y, width, height;
    Cell() : x(0), y(0), width(0), height(0) { }
public:
    static std::vector<Cell> make_cells(
        int number_of_rows,
        int number_of_cols,
        int maze_width,
        int maze_height)
    {
        const double cell_width = (double)maze_width / (double)number_of_cols;
        const double cell_height = (double)maze_height / (double)number_of_rows;
        const int number_of_cells = number_of_cols * number_of_rows;
        std::vector<Cell> cells;
        cells.reserve(number_of_cells);

        // fill vectore with cells
        // u probly need a double for loop or something
        // rememb u r mapping the pixels on the screen to cells

        return cells;
    }

    bool contains(const Entity& other) const;
};

