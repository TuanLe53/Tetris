#include <board.hpp>

Board::Board(){
    reset();
}

void Board::draw(sf::RenderTarget &target){
    sf::RectangleShape cell(sf::Vector2f(50.f - 2.f, 50.f - 2.f));
    cell.setFillColor(sf::Color::White);

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 20; j++) {
            if (grid[i][j] != 0) {
                cell.setPosition({border_left + i * 50.f + 1.f, j * 50.f + 1.f});
                target.draw(cell);
            }
        }
    }

    for(int i = 0; i < ((width / 50) + 1); i++){
        sf::RectangleShape line({line_width, height});
        line.setPosition({border_left + (float)i*50.f, 0.f});
        target.draw(line);
    }
    for(int i = 0; i < ((height / 50) + 1); i++){
        sf::RectangleShape line({width, line_width});
        line.setPosition({border_left, (float)i*50.f});
        target.draw(line);
    }
}

void Board::reset(){
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 20; j++){
            grid[i][j] = 0;
        }
    }
}

void Board::lockBlock(const Block& block){
    sf::Vector2f pos = block.getPivotPos();

    int gridX = static_cast<int>((pos.x - border_left) / 50.f);
    int gridY = static_cast<int>(pos.y / 50.f);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (block.getCellValue(i, j) != 0) {
                int targetX = gridX + (j - 2);
                int targetY = gridY + (i - 2);

                if (targetX >= 0 && targetX < 13 && targetY >= 0 && targetY < 20) {
                    grid[targetX][targetY] = 1; 
                }
            }
        }
    }
}

bool Board::isCollision(const Block& block) {
    sf::Vector2f pos = block.getPivotPos();
    int gridX = static_cast<int>((pos.x - border_left) / 50.f);
    int gridY = static_cast<int>(pos.y / 50.f);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (block.getCellValue(i, j) != 0) {
                int targetX = gridX + (j - 2);
                int targetY = gridY + (i - 2);

                if (targetY >= 20) {
                    return true;
                }

                if (targetY >= 0 && targetX >= 0 && targetX < 13) {
                    if(grid[targetX][targetY] != 0){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::isWallCollision(const Block &block){
    sf::Vector2f pos = block.getPivotPos();
    int gridX = static_cast<int>((pos.x - border_left) / 50.f);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (block.getCellValue(i, j) != 0){
                int targetX = gridX + (j - 2);

                if (targetX < 0 || targetX >= 13) {
                    return true;
                }
            }
        }
    }

    return false;
}

int Board::clearFullLines() {
    int linesCleared = 0;
    for (int y = 19; y >= 0; y--) {
        bool isFull = true;

        for (int x = 0; x < 13; x++) {
            if (grid[x][y] == 0) {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            linesCleared++;
            for (int k = y; k > 0; k--) {
                for (int x = 0; x < 13; x++) {
                    grid[x][k] = grid[x][k - 1];
                }
            }

            for (int x = 0; x < 13; x++) {
                grid[x][0] = 0;
            }

            y++; 
        }
    }
    return linesCleared;
}