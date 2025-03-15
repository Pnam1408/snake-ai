#pragma once
#include <SFML/Graphics.hpp>

namespace cf {
    unsigned int const WindowWidth = 800;
    unsigned int const WindowHeight = 600;

    float const BoardWidth = 400.f;
    float const BoardHeight = 400.f;

    // Khong duoc nho hon 5
    // Neu ca hang va cot deu le se ko co chu trinh hamiltonian
    unsigned int const NumRows = 6;
    unsigned int const NumCols = 6;

    float const RowHeight = BoardHeight/NumRows;
    float const ColWidth = BoardWidth/NumCols;

    const sf::Color snakeBodyColor = sf::Color::Cyan;
    const sf::Color snakeHeadColor = sf::Color::Blue;
    const sf::Color foodColor = sf::Color::Green;
    const sf::Color gridColor = sf::Color::Red;
}