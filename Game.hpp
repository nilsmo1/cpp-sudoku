#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <utility>

class Game {
    std::string m_board_string;
    const int HEIGHT = 600;
    const int WIDTH = 600;
    int mode = 0; // place, marking or mark 
public:
    int m_cellx = -1;
    int m_celly = -1;
    Game();
    void gen_board();
    void render_terminal_board(Board&);
    void render_lines(sf::RenderWindow&);
    void render_numbers(sf::RenderWindow&, sf::Font&, Board&);
    void select_cell(sf::RenderWindow&);
    void unselect_cell();
    void select_mode();
    void run();
};
