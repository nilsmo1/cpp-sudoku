#include "Game.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

const sf::Color LIGHT(255, 255, 255, 120);

Game::Game() {}

void Game::gen_board() {}

void Game::init_highlight() {
    float size = 63.5f;
    hl_rect.setSize(sf::Vector2f(size, size));
    hl_rect.setFillColor(sf::Color(255, 255, 0, 100));
}

void Game::highlight_selected() {
    hl_rect.setPosition(10.5f + m_cellx*64.5f, 10.5f + m_celly*64.5f);
}

void Game::render_terminal_board(Board& board) {
    std::cout << "Board:" << '\n';
    for (int row=0; row<board.m_rows; ++row) {
        for (int col=0; col<board.m_cols; ++col) {
            std::cout << board.at(row,col,board.m_grid) << " ";
        } std::cout << '\n';
    }
    std::cout << "\nSolution:\n";
    for (int row=0; row<board.m_rows; ++row) {
        for (int col=0; col<board.m_cols; ++col) {
            std::cout << board.at(row,col,board.m_solution) << " ";
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
            int val = board.at(row, col, board.m_grid);
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
    Board board("2...965.1.694.........5...7.4.8.27.......5...856.49...6.8........1......79....2.6");
    render_terminal_board(board);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sudoku");
    sf::Font font;
    font.loadFromFile("Ezme.ttf");
    init_highlight();
    bool quit = false, solved = false;
    while (window.isOpen() && !quit)
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    quit = true;
                    break;
                case sf::Event::MouseButtonPressed:
                    select_cell(window);
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Q) {
                        quit = true;
                    } else if (event.key.code > sf::Keyboard::Num0 &&
                               event.key.code <= sf::Keyboard::Num9) {
                        int d = event.key.code - sf::Keyboard::Num0;
                        if (m_cellx >= 0 && m_cellx < 9 && m_celly >= 0 && m_celly < 9)
                            board.place_number(m_celly, m_cellx, d);

                    } else if (event.key.code == sf::Keyboard::D) {
                        unselect_cell();
                    } else if (event.key.code == sf::Keyboard::S) {
                        board.m_grid = board.m_solution;
                        solved = true;
                    } else if (event.key.code == sf::Keyboard::Left) {
                        if (m_cellx > 0 && m_celly >= 0)
                            m_cellx--;
                    } else if (event.key.code == sf::Keyboard::Right) {
                        if (m_cellx >= 0 && m_cellx < board.m_cols-1 && m_celly >= 0)
                            m_cellx++;
                    } else if (event.key.code == sf::Keyboard::Up) {
                        if (m_cellx >= 0 && m_celly > 0)
                            m_celly--;
                    } else if (event.key.code == sf::Keyboard::Down) {
                        if (m_cellx >= 0 && m_celly < board.m_rows-1 && m_celly >= 0)
                            m_celly++;
                    } break;
            }
        }
        window.clear(sf::Color::Black);
        if (solved || board.m_done)
            window.clear(sf::Color(0, 100, 0));
        render_lines(window);
        if (m_cellx >= 0 && m_celly >= 0) {
            highlight_selected();
            window.draw(hl_rect);
        }
        render_numbers(window, font, board);
        window.display();
    }
    window.close();
}
