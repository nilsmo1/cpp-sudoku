#pragma once

#include <string>
#include <vector>
#include <stack>
#include <utility>

class Board {
    int m_rows = 9;
    int m_cols = 9;
    int m_size = m_rows*m_cols;
    std::string m_config_string;
    std::vector<int> m_grid = std::vector<int>(m_size, 0);
    std::vector<int> m_solution = std::vector<int>(m_size, 0);
public:
    Board(std::string);
    void parse_string();
    int get_index(int, int);
    void place_number(int, int, int);
    void mark_number(int, int, int);
    bool in_row(int, int);
    bool in_col(int, int);
    bool in_box(int, int);
    bool check_move(int, int, int);
    bool is_full();
    bool solve();
    bool is_solved();
    std::vector<int> get_solution();
    std::vector<std::pair<int, int>> get_number_positions(int);
};
