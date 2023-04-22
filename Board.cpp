#include "Board.hpp"


Board::Board(std::string s) {
    m_config_string = s;
    parse_string();
    solve();
}

void Board::parse_string() {
    for (size_t i=0; i<m_size; ++i) {
        if (m_config_string[i] == '.') 
            m_config_string[i] = '0';
        m_grid[i] = m_config_string[i]-'0';
    }
}

int Board::get_index(int row, int col) {
    return row*m_rows + col;
}

int Board::at(int row, int col) {
    return m_grid[get_index(row, col)];
}

void Board::place_number(int row, int col, int num) {
    /* if (!check_move(row, col, num)) return; */
    int id = get_index(row, col);
    m_grid[id] = num;
}

void Board::mark_number(int row, int col, int num) { }

bool Board::in_row(int row, int num) {
    for (int c=0; c<m_cols; ++c) {
        if (num == at(row, c) return true;
    } return false;
}

bool Board::in_col(int col, int num) {
    for (int r=0; r<m_rows; ++r) {
        if (num == at(r, col)) return true;
    } return false;
}

bool Board::in_box(int row, int col, int num) {
    int startr = row - row%3, startc = col - col%3;
    for (int r=0; r<3; ++r) {
        for (int c=0; c<3; ++c) {
            if (num == at(r + startr, c + startc, num))
                return true;
        }
    } return false; 
}

bool Board::safe_move(int row, int col, int num) {
    return !in_col(col, num) && 
           !in_row(row, num) &&
           !in_box(row, col, num);
}

bool Board::check_move(int row, int col, int num) {
    int id = get_index(row, col);
    return m_solution[id] == num;
}

// solve board TODO: at(row, col) checks the unfilled board
bool Board::is_full(int& row, int& col) {
    for (row=0; row<m_rows; ++row) {
        for (col=0; col<m_cols; ++col) {
            if (at(row, col) == 0) return false;
        }
    } return true;
}

// solve board TODO
bool Board::solve() {
    int r{}, c{};
    if (is_full(r, c)) return true;
    for (int num=1; num<10; ++num) {
        if (safe_move(r, c, num))
    }


    return true;
}

bool Board::is_solved() {
    int r{}, c{};
    if (!is_full(r, c)) return false;
    for (int i=0; i<m_size; ++i) {
        if (m_grid[i] != m_solution[i])
            return false;
    }
    return true;
}

std::vector<int> Board::get_solution() { return m_solution; };

std::vector<std::pair<int, int>> Board::get_number_positions(int num) {
    std::vector<std::pair<int, int>> positions;
    int row{}, col{};
    for (int i=0; i<m_size; ++i) { 
        if (m_grid[i] == num) {
            row = i / m_rows;
            col = i % m_cols;
            positions.push_back(std::make_pair(row, col));
        }
    }
    return positions;
}
