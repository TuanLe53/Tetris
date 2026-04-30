#pragma once

#include <SFML/Graphics.hpp>
#include <entities/block.hpp>

class Board{
private:
    int grid[13][20];
    float width = 650.f;
    float height = 1000.f;
    float line_width = 1.f;
public:
    Board();
    void draw(sf::RenderTarget &target);
    void reset();
    void lockBlock(const Block& block);
    bool isCollision(const Block& block);
    bool isWallCollision(const Block& block);
    int clearFullLines();
};