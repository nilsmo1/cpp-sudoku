#include "Game.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

Game::Game() {}
void Game::gen_board() {}
void Game::render_lines(sf::RenderWindow& win) {
    float small_step = 64.5f;
    float big_step = 193.5f;
    for (size_t i=0; i<10; ++i) {
        sf::Vertex lineh[] =
        {
            sf::Vertex(sf::Vector2f(10.f , 10.f + i*small_step)),
            sf::Vertex(sf::Vector2f(WIDTH-10.f, 10.f + i*small_step)),
        };
        sf::Vertex linev[] =
        {
            sf::Vertex(sf::Vector2f(10.f + i*small_step, 10.f)),
            sf::Vertex(sf::Vector2f(10.f + i*small_step, HEIGHT-10.f)),
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
        for (auto& lh : lineh) {
            lh.color = sf::Color::Red;
        }
        for (auto& lv : linev) {
            lv.color = sf::Color::Red;
        }
        win.draw(linev, 2, sf::Lines);
        win.draw(lineh, 2, sf::Lines);
    }
}
void Game::run() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sudoku");

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) 
            break;

        window.clear(sf::Color::Black);
        render_lines(window);
        window.display();
    }
    window.close();

    return;
}
