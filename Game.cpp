#include "Game.hpp"
#include "Board.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

Game::Game() {}

void Game::swap_color() {
    dark_mode = !dark_mode;
    init_colors();
}

void Game::gen_board() {}

void Game::init_colors() {
    HIGHLIGHT = sf::Color(255, 255,  0, 150);
    MARKING   = sf::Color(0, 255, 100 , 150);
    if (dark_mode) {
        LINE_THIN  = sf::Color(255, 255, 255, 120);
        LINE_THICK = sf::Color::White;
        BACKGROUND = sf::Color::Black;
        NUMBER     = LINE_THICK;
        return;
    }
    LINE_THIN  = sf::Color(50, 50, 0, 50);
    LINE_THICK = sf::Color::Black;
    BACKGROUND = sf::Color::White;
    NUMBER     = LINE_THICK;
}

void Game::starting_menu() {
    // TODO
}
 
void Game::init_highlight() {
    float size = 63.5f;
    hl_rect.setSize(sf::Vector2f(size, size));
    hl_rect.setFillColor(HIGHLIGHT);
}

void Game::highlight_selected() {
    hl_rect.setPosition(10.5f + m_cellx*64.5f, 10.5f + m_celly*64.5f);
}

void Game::show_markings(Board& board, int row, int col) {
    for (bool b : board.m_markings[board.get_index(row, col)]) {
            std::cout << b << " ";
    } std::cout << '\n';
}

void Game::render_markings(sf::RenderWindow& win, sf::Font& font, Board& board) {
    for (int row=0; row<9; ++row) {
        for (int col=0; col<9; ++col) {
            if (board.m_grid[board.get_index(row, col)] != 0) continue;
            std::vector<bool> ms = board.m_markings[board.get_index(row, col)];
            for (int m=0; m<board.m_rows; ++m) {
                bool b = ms[m];
                if (b) {
                    sf::Text num(std::to_string(m+1), font, 20);
                    num.setFillColor(NUMBER);
                    num.setPosition(
                            13.f + col * 64.5f + (m % 3) * 20.f,
                            10.f + row * 64.5f + ((float)m / 3) * 20.f
                    );
                    win.draw(num);
                }
            }
        }
    }
}

void Game::render_terminal_board(Board& board, std::vector<int> grid) {
    for (int row=0; row<board.m_rows; ++row) {
        if (row%3 == 0)
            std::cout << "-------------------------" << '\n';
        for (int col=0; col<board.m_cols; ++col) {
            if (col % 3 == 0) std::cout << "| ";
            if (board.at(row, col, grid) == 0)
                std::cout << "  ";
            else std::cout << board.at(row, col, grid) << " ";
        } std::cout << "|\n";
    } std::cout << "-------------------------" << "\n\n";
}

void Game::render_lines(sf::RenderWindow& win) {
    float small_step = 64.5f;
    float big_step = 193.5f;
    for (size_t i=0; i<10; ++i) {
        sf::Vertex thin_lineh[] =
        {
            sf::Vertex(sf::Vector2f(      10.f, 10.f + i*small_step), LINE_THIN),
            sf::Vertex(sf::Vector2f(WIDTH-10.f, 10.f + i*small_step), LINE_THIN),
        };
        sf::Vertex thin_linev[] =
        {
            sf::Vertex(sf::Vector2f(10.f + i*small_step,        10.5f), LINE_THIN),
            sf::Vertex(sf::Vector2f(10.f + i*small_step, HEIGHT-8.5f), LINE_THIN)
        };
        win.draw(thin_linev, 2, sf::Lines);
        win.draw(thin_lineh, 2, sf::Lines);
    }

    for (size_t i=0; i<4; ++i) {
        sf::Vertex lineh[] =
        {
            sf::Vertex(sf::Vector2f(      10.f, 10.f + i*big_step), LINE_THICK),
            sf::Vertex(sf::Vector2f(WIDTH-10.f, 10.f + i*big_step), LINE_THICK)
        };
        sf::Vertex linev[] =
        {
            sf::Vertex(sf::Vector2f(10.f + i*big_step,        10.5f), LINE_THICK),
            sf::Vertex(sf::Vector2f(10.f + i*big_step, HEIGHT-8.5f), LINE_THICK)
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
            num.setFillColor(NUMBER);
            num.setPosition(23.f+col*64.5f, 12.f+row*64.5f);
            win.draw(num);
        }
    }
}

void Game::select_cell(sf::RenderWindow& win) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(win);
    float div = 64.5f;
    m_cellx = (int)((mouse_pos.x-10) / div);
    m_celly = (int)((mouse_pos.y-10) / div); 
}

void Game::unselect_cell() { m_cellx = -1; m_celly = -1; }

void Game::swap_mode() {
    m_mode = !m_mode;
    if (m_mode) hl_rect.setFillColor(HIGHLIGHT);
    else hl_rect.setFillColor(MARKING);
}

void Game::run() {
    Board board("2...965.1.694.........5...7.4.8.27.......5...856.49...6.8........1......79....2.6");
    render_terminal_board(board, board.m_grid);
    render_terminal_board(board, board.m_solution);
    init_colors();
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sudoku");
    window.setFramerateLimit(20);
    sf::Font font;
    font.loadFromFile("nk57-monospace-se-lt.ttf");
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
                        if (m_mode) {
                            if (m_cellx >= 0 && m_cellx < 9 && m_celly >= 0 && m_celly < 9)
                                board.place_number(m_celly, m_cellx, d);
                        } else {
                            if (m_cellx >= 0 && m_cellx < 9 && m_celly >= 0 && m_celly < 9)
                                board.mark_number(m_celly, m_cellx, d);
                        }

                    } else if (event.key.code == sf::Keyboard::E) {
                        swap_mode();
                    } else if (event.key.code == sf::Keyboard::D) {
                        unselect_cell();
                    } else if (event.key.code == sf::Keyboard::S) {
                        board.m_grid = board.m_solution;
                        solved = true;
                    } else if (event.key.code == sf::Keyboard::C) {
                        swap_color();

                    } else if (event.key.code == sf::Keyboard::Left) {
                        if (m_cellx > 0 && m_celly >= 0) m_cellx--;

                    } else if (event.key.code == sf::Keyboard::Right) {
                        if (m_cellx >= 0 && m_cellx < board.m_cols-1 && m_celly >= 0) m_cellx++;

                    } else if (event.key.code == sf::Keyboard::Up) {
                        if (m_cellx >= 0 && m_celly > 0) m_celly--;

                    } else if (event.key.code == sf::Keyboard::Down) {
                        if (m_cellx >= 0 && m_celly < board.m_rows-1 && m_celly >= 0) m_celly++;
                    } break;
		default: break;
            }

        }
        window.clear(BACKGROUND);
        if (solved || board.m_done)
            window.clear(sf::Color(0, 175, 0));
        render_lines(window);
        if (m_cellx >= 0 && m_celly >= 0) {
            highlight_selected();
            window.draw(hl_rect);
        }
        render_numbers(window, font, board);
        render_markings(window, font, board);
        window.display();
    }
    window.close();
}
