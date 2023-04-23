#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include <utility>

class Game {
    std::string m_board_string;
    const int HEIGHT = 600;
    const int WIDTH = 600;
    bool m_mode = true;
    sf::RectangleShape hl_rect;
    bool dark_mode = true;
    sf::Color LINE_THIN, LINE_THICK, HIGHLIGHT, BACKGROUND, NUMBER, MARKING;
public:
    int m_cellx = -1;
    int m_celly = -1;
    Game();
    void swap_color();
    void gen_board();
    void init_colors();
    void starting_menu();
    void init_highlight();
    void highlight_selected();
    void show_markings(Board&, int, int);
    void render_markings(sf::RenderWindow&, sf::Font&, Board&);
    void render_terminal_board(Board&, std::vector<int>);
    void render_lines(sf::RenderWindow&);
    void render_numbers(sf::RenderWindow&, sf::Font&, Board&);
    void select_cell(sf::RenderWindow&);
    void unselect_cell();
    void swap_mode();
    void run();
};
