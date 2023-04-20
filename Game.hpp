#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Game {
    std::string m_board_string;
    const int HEIGHT = 600;
    const int WIDTH = 600;
public:
    Game();
    void gen_board();
    void render_lines(sf::RenderWindow&);
    void render_numbers(sf::RenderWindow&);
    void run();
};
