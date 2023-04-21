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

bool Board::in_row(int row, int num) { return false; }

bool Board::in_col(int col, int num) { return false; }

bool Board::in_box(int corner, int num) { return false; }

bool Board::check_move(int row, int col, int num) {
    int id = get_index(row, col);
    return m_solution[id] == num;
}

bool Board::is_full() {
    for (int d : m_grid) { if (d == 0) return false; }
    return true;
}

bool Board::solve() {
    


    return true;
}

bool Board::is_solved() {
    if (!is_full()) return false;
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
