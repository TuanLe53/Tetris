#pragma once

#include <SFML/Graphics.hpp>
#include <constants.hpp>

class Block{
private:
    Tetris::BlockType type;
    sf::Vector2f pivotPos = {700.f, -100.f};
    int block[5][5] = {0};
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Block(Tetris::BlockType type);
    void spawn(Tetris::BlockType type);
    void draw(sf::RenderTarget &target);
    void setPivotPos(sf::Vector2f pos);

    void rotate();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    sf::Vector2f getPivotPos() const;
    int getCellValue(int i, int j) const;
    Tetris::BlockType getType() const;
};