#include "Game.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

const sf::Color LIGHT(255, 255, 255, 120);

Game::Game() {}

void Game::gen_board() {}

void Game::render_terminal_board(Board& board) {
    for (int row=0; row<board.m_rows; ++row) {
        for (int col=0; col<board.m_cols; ++col) {
            std::cout << board.at(row,col) << " ";
        } std::cout << '\n';
    }
}

void Game::render_lines(sf::RenderWindow& win) {
    float small_step = 64.5f;
    float big_step = 193.5f;
    for (size_t i=0; i<10; ++i) {
        sf::Vertex lineh[] =
        {
            sf::Vertex(sf::Vector2f(10.f , 10.f + i*small_step), LIGHT),
            sf::Vertex(sf::Vector2f(WIDTH-10.f, 10.f + i*small_step), LIGHT),
        };
        sf::Vertex linev[] =
        {
            sf::Vertex(sf::Vector2f(10.f + i*small_step, 10.f), LIGHT),
            sf::Vertex(sf::Vector2f(10.f + i*small_step, HEIGHT-10.f), LIGHT),
        };
        win.draw(linev, 2, sf::Lines);
        win.draw(lineh, 2, sf::Lines);
    }

    for (size_t i=0; i<4; ++i) {
        sf::Vertex lineh[] =
        {
            sf::Vertex(sf::Vector2f(10.f , 10.f + i*big_step)),
            sf::Vertex(sf::Vector2f(WIDTH-10.f, 10.f + i*big_step)),
        };
        sf::Vertex linev[] =
        {
            sf::Vertex(sf::Vector2f(10.f + i*big_step, 10.f)),
            sf::Vertex(sf::Vector2f(10.f + i*big_step, HEIGHT-10.f)),
        };
        win.draw(linev, 2, sf::Lines);
        win.draw(lineh, 2, sf::Lines);
    }
}

void Game::render_numbers(sf::RenderWindow& win, sf::Font& font, Board& board) {
    for (int row=0; row<9; ++row) {
        for (int col=0; col<9; ++col) {
            int val = board.at(row, col);
            if (val == 0) continue;
            sf::Text num(std::to_string(val),font,50);
            num.setFillColor(sf::Color::White);
            num.setOutlineColor(sf::Color::White);
            num.setPosition(30.f+col*64.5f, 10.f+row*64.5f);
            win.draw(num);
        }
    }
}

void Game::select_cell(sf::RenderWindow& win) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(win);
    float div = 64.5f;
    m_cellx = (int)((mouse_pos.x-10) / div);
    m_celly = (int)((mouse_pos.y-10) / div);
    /* std::cout << m_cellx << " " << m_celly << '\n'; */
}

void Game::unselect_cell() {
    m_cellx = -1;
    m_celly = -1;
    /* std::cout << m_celly << " " << m_cellx << '\n'; */
}

void Game::select_mode() {}

void Game::run() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sudoku");
    sf::Font font;
    font.loadFromFile("Ezme.ttf");
    Board board("47..5...29.2...1....6..247.3.4..1...................5....4.7.3...7.....66.1..92..");
    bool quit = false;
    render_terminal_board(board);
    while (window.isOpen() && !quit)
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseButtonPressed:
                    select_cell(window);
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Q) {
                        quit = true;
                    } else if (event.key.code > sf::Keyboard::Num0 &&
                               event.key.code <= sf::Keyboard::Num9) {
                        int d{};
                        std::cout << (d = event.key.code - sf::Keyboard::Num0) << '\n';
                        if (m_cellx >= 0 && m_cellx < 9 && m_celly >= 0 && m_celly < 9)
                            board.place_number(m_celly, m_cellx, d);

                    } else if (event.key.code == sf::Keyboard::D) {
                        unselect_cell();
                    }
                    break;

            }
            if (quit) break;
        }
        window.clear(sf::Color::Black);
        render_lines(window);
        render_numbers(window, font, board);
        window.display();
    }
    window.close();
}
