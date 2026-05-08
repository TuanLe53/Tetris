#include <entities/block.hpp>

Block::Block(Tetris::BlockType type) : sprite(texture) {
    this->type = type;

    std::string path = Tetris::TEXTURE_PATHS.at(type);
    if (this->texture.loadFromFile(path)) {
        this->sprite.setTexture(this->texture, true);
        float scale = 50.f / 32.f;
        this->sprite.setScale({scale, scale});
    }else{
        std::printf("Error: Could not load texture!\n");
    }

    auto& shapeData = Tetris::SHAPES.at(type);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            this->block[i][j] = shapeData[i][j];
        }
    }
}

void Block::draw(sf::RenderTarget &target){
    float cellSize = 50.f;

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(block[i][j]){
                float relativeX = (j - 2) * cellSize;
                float relativeY = (i - 2) * cellSize;

                sprite.setPosition({pivotPos.x + relativeX, pivotPos.y + relativeY});
                target.draw(sprite);
            }
        }
    }
}

void Block::rotate(){
    if(type == Tetris::BlockType::O){
        return;
    }

    int temp[5][5];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            temp[j][4 - i] = block[i][j];
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            block[i][j] = temp[i][j];
        }
    }
}

void Block::moveUp(){
    pivotPos.y -= 50.f;
}

void Block::moveDown(){
    pivotPos.y += 50.f;
};

void Block::moveLeft(){
    pivotPos.x -= 50.f;
};

void Block::moveRight(){
    pivotPos.x += 50.f;
};

void Block::setPivotPos(sf::Vector2f pos){
    pivotPos = pos;
}

sf::Vector2f Block::getPivotPos() const{
    return pivotPos;
}

int Block::getCellValue(int i, int j) const{
    return block[i][j];
}

void Block::spawn(Tetris::BlockType type){
    this->type = type;
    this->pivotPos = {700.f, -100.f};

    std::string path = Tetris::TEXTURE_PATHS.at(type);
    if (this->texture.loadFromFile(path)) {
        this->sprite.setTexture(this->texture, true);
    }

    auto& shapeData = Tetris::SHAPES.at(type);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            this->block[i][j] = shapeData[i][j];
        }
    }
}