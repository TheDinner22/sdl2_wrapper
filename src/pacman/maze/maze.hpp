#pragma once

#include "pacman/entity/entity.hpp"
#include <array>
#include <iostream>
#include <optional>
#include <vector>

// i want to return a row, col pair to identify an
// index in a 2d array and refuse to use a pair or tuple
// Ex: array[i][j]
// i = row and j = col
class Index2 {
public:
    int i, j;
};

class ContainsResult {
public:
    // ContainsResult(bool x_and_y_match) : x_match(x_and_y_match), y_match(x_and_y_match) {}

    bool x_match = false;
    bool y_match = false;

    bool contained() const { return x_match == true && y_match == true; }
};

enum CellState {
    EMPTY,
    WALL,
    PELLET,
    POWER_PELLET,
};

class Cell {
private:
    double x, y;
    int width, height;
public:
    CellState state = EMPTY;

    friend std::ostream &operator<<(std::ostream &os, Cell const &cell);

    Cell(int x = 0.0, int y = 0.0, int width = 0, int height = 0);

    const double& get_x() const { return this->x; }
    const double& get_y() const { return this->y; }

    template<int number_of_rows, int number_of_cols>
    static std::array<std::array<Cell, number_of_cols>, number_of_rows> make_cells(
        int maze_width,
        int maze_height)
    {
        const double cell_width = (double)maze_width / (double)number_of_cols;
        const double cell_height = (double)maze_height / (double)number_of_rows;
        std::array<std::array<Cell, number_of_cols>, number_of_rows> cells;

        for (int row_i = 0; row_i < number_of_rows; row_i++) {
            const double y_pos = cell_height * double(row_i);
            for (int col_i = 0; col_i < number_of_rows; col_i++) {
                const double x_pos = cell_width * double(col_i);
                cells[row_i][col_i] = Cell(x_pos, y_pos, cell_width, cell_height);
            }
        }

        return cells;
    }

    template<int number_of_rows, int number_of_cols>
    static void print(const std::array<std::array<Cell, number_of_cols>, number_of_rows>& cells) {
        for (std::array<Cell, number_of_cols> row : cells) {
            for (Cell x : row) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
        }
    }

    ContainsResult contains(const Entity& other) const;
};

enum Move {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Maze {
private:
    const int maze_width = 600;
    const int maze_height = 600;

    static const int side_length = 30;
    // cells[row][col]
    std::array<std::array<Cell, side_length>, side_length> cells;

    std::vector<Entity> ghosts;

    Entity player;
    Move player_move;
    

    // ()'s group & and layout becuase this is a ref to slice not slice of ref's
    void update_cellstates_from_layout(const int (&layout) [side_length * side_length]) {
        for (int row_i = 0; row_i < this->side_length; row_i++) {
            for (int col_i = 0; col_i < this->side_length; col_i++) {
                const int new_state = layout[col_i + (row_i * this->side_length)];
                this->cells[row_i][col_i].state = (CellState)new_state;
            }
        }
    }

public:
    // TODO way to setup maze?
    Maze(Entity&& player, std::vector<Entity>&& ghosts);

    void draw() const;

    void tick();

    // gets the row and col of the cell the player 
    // is on
    std::optional<Index2> players_cell() const; // TODO

    void handle_key_press(const SDL_Keycode& sym);
};

