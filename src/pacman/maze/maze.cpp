enum CellState {
    PELLET,
    POWER_PELLET,
    WALL,
    EMPTY
};

enum Move {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Maze {
private:
    // cells[row][col]
    CellState cells[30][30];
public:
    bool can_make_move_at_cell(int cell_row, int cell_col, Move move) const {

    }
};
