#pragma once

#include <string>
#include <vector>
#include <stack>
#include <utility>

class Board {
    std::string m_config_string;
public:
    Board(std::string);
    int m_rows = 9;
    int m_cols = 9;
    int m_size = m_rows*m_cols;
    int m_placed = m_size;
    bool m_done = false;
    std::vector<int> m_grid = std::vector<int>(m_size, 0);
    std::vector<int> m_solution = std::vector<int>(m_size, 0);
    void parse_string();
    int get_index(int, int);
    int at(int, int, std::vector<int>&);
    void place_number(int, int, int);
    void mark_number(int, int, int);
    bool in_row(int, int);
    bool in_col(int, int);
    bool in_box(int, int, int);
    bool safe_move(int, int, int);
    bool check_move(int, int, int);
    bool is_full(int&, int&, std::vector<int>&);
    bool solve();
    bool is_solved();
    std::vector<int> get_solution();
    std::vector<std::pair<int, int>> get_number_positions(int);
};
