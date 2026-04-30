#pragma once

#include <SFML/Graphics.hpp>
#include <constants.hpp>

class Block{
private:
    Tetris::BlockType type;
    sf::Vector2f pivotPos = {300.f, -150.f};
    int block[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    sf::RectangleShape square{{50.f, 50.f}};
public:
    Block(Tetris::BlockType type);
    void spawn(Tetris::BlockType type);
    void draw(sf::RenderTarget &target);

    void rotate();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    sf::Vector2f getPivotPos() const;
    int getCellValue(int i, int j) const;
};