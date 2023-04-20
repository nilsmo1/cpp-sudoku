#include "Game.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

const sf::Color LIGHT(255, 255, 255, 120);
Game::Game() {}
void Game::gen_board() {}
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
        /* for (auto& lh : lineh) { */
        /*     lh.color = LIGHT; */
        /* } */
        /* for (auto& lv : linev) { */
        /*     lv.color = LIGHT; */
        /* } */
        win.draw(linev, 2, sf::Lines);
        win.draw(lineh, 2, sf::Lines);
    }
}
void Game::render_numbers(sf::RenderWindow& win) {}
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
