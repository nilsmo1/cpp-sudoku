#include "Board.hpp"


Board::Board(std::string s) {
    m_config_string = s;
    parse_string();
    solve();
}

void Board::parse_string() {
    for (int i=0; i<m_size; ++i) {
        char c = m_config_string[i];
        if (c == '.') { c = '0'; m_placed--; }
        m_grid[i]     = c-'0';
        m_solution[i] = c-'0';
    }
}

int Board::get_index(int row, int col) {
    return row*m_rows + col;
}

int Board::at(int row, int col, std::vector<int>& grid) {
    return grid[get_index(row, col)];
}

void Board::place_number(int row, int col, int num) {
    if (!check_move(row, col, num)) return;
    int id = get_index(row, col);
    m_grid[id] = num;
    m_placed++;
    if (m_placed == m_size) m_done = true;
}

void Board::mark_number(int row, int col, int num) { }

bool Board::in_row(int row, int num) {
    for (int c=0; c<m_cols; ++c) {
        if (num == at(row, c, m_solution)) return true;
    } return false;
}

bool Board::in_col(int col, int num) {
    for (int r=0; r<m_rows; ++r) {
        if (num == at(r, col, m_solution)) return true;
    } return false;
}

bool Board::in_box(int row, int col, int num) {
    int startr = row - row%3, startc = col - col%3;
    for (int r=0; r<3; ++r) {
        for (int c=0; c<3; ++c) {
            if (num == at(r + startr, c + startc, m_solution))
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

bool Board::is_full(int& row, int& col, std::vector<int>& grid) {
    for (row=0; row<m_rows; ++row) {
        for (col=0; col<m_cols; ++col) {
            if (at(row, col, grid) == 0) return false;
        }
    } return true;
}

bool Board::solve() {
    int r{}, c{};
    if (is_full(r, c, m_solution)) return true;
    for (int num=1; num<10; ++num) {
        if (safe_move(r, c, num)) {
            m_solution[get_index(r, c)] = num;
            if (solve()) return true;
            m_solution[get_index(r, c)] = 0;
        }
    } return false;
}

bool Board::is_solved() {
    int r{}, c{};
    if (!is_full(r, c, m_grid)) return false;
    for (int i=0; i<m_size; ++i) {
        if (m_grid[i] != m_solution[i])
            return false;
    } return true;
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
    } return positions;
}
