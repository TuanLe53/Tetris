#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <entities/block.hpp>
#include <entities/factory.hpp>
#include <board.hpp>

const int WIDTH = 1550;
const int HEIGHT = 1000;

const float fastSpeed = 0.05f;
float currentSpeed;
float timer = 0;
int linesCleared = 0;
int level = 1;
std::vector<float> gravityTable = {0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.2f, 0.15f, 0.1f};

void updateSpeed(){
    level = linesCleared / 10;
    if(level < 1){
        level = 1;
    }

    if(level < gravityTable.size()){
        currentSpeed = gravityTable[level];
    }else{
        currentSpeed = gravityTable.back();
    }
}

int calculateScore(int linesCleared, int currentLevel){
    int baseScore = 0;

    switch(linesCleared){
        case 1:
            baseScore = 100;
            break;
        case 2:
            baseScore = 300;
            break;
        case 3:
            baseScore = 500;
            break;
        case 4:
            baseScore = 1200;
            break;
    }

    return baseScore * currentLevel;
}

int score = 0;
Board board = Board();
Factory factory = Factory();
Block currentBlock = Block(factory.nextBlockType());
Tetris::BlockType nextType = factory.nextBlockType();
Block nextBlock = Block(nextType);

std::optional<Tetris::BlockType> heldType;
Block heldBlock(Tetris::BlockType::I);
bool canHold = true;

int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Tetris!");
    sf::Clock clock;
    
    float boxSize = 400.f;

    sf::Vector2f previewBoxPos(1150.f, 600.f);
    sf::Vector2f previewBoxCenter(previewBoxPos.x + boxSize / 2.f, previewBoxPos.y + boxSize / 2.f);
    sf::Texture previewBoxTexture("assets/graphics/UI/next.png");
    sf::Sprite previewBoxSprite(previewBoxTexture);
    previewBoxSprite.setPosition(previewBoxPos);
    previewBoxSprite.setScale({boxSize/192.f, boxSize/192.f});
    
    nextBlock.setPivotPos(previewBoxCenter);

    sf::Vector2f holdBoxPos(0.f, 600.f);
    sf::Vector2f holdBoxCenter(holdBoxPos.x + boxSize / 2.f,holdBoxPos.y + boxSize / 2.f);
    sf::Texture holdBoxTexture("assets/graphics/UI/hold.png");
    sf::Sprite holdBoxSprite(holdBoxTexture);
    holdBoxSprite.setPosition(holdBoxPos);
    holdBoxSprite.setScale({boxSize/192.f, boxSize/192.f});


    sf::Font font("assets/fonts/m6x11.ttf");
    sf::Text text(font);
    text.setCharacterSize(50);
    text.setPosition({1200, 100});

    updateSpeed();

    while (window.isOpen())
    {
        float time = clock.restart().asSeconds();
        timer += time;

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){
                window.close();
                std::printf("Your score: %d", score);
            }

            if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->code == sf::Keyboard::Key::Left) {
                    currentBlock.moveLeft();
                    if (board.isWallCollision(currentBlock)) {
                        currentBlock.moveRight();
                    }
                }
                if (keyPressed->code == sf::Keyboard::Key::Right) {
                    currentBlock.moveRight();
                    if (board.isWallCollision(currentBlock)) {
                        currentBlock.moveLeft();
                    }
                }
                if(keyPressed->code == sf::Keyboard::Key::X){
                    currentBlock.rotate();
                }
                if(keyPressed->code == sf::Keyboard::Key::C){
                    if(canHold){
                        Tetris::BlockType currentType = currentBlock.getType();
    
                        if(!heldType.has_value()){
                            heldType = currentType;
                            currentBlock.spawn(nextType);
    
                            nextType = factory.nextBlockType();
                            nextBlock.spawn(nextType);
                            nextBlock.setPivotPos(previewBoxCenter);
                        }else{
                            Tetris::BlockType temp = *heldType;
                            heldType = currentType;
                            currentBlock.spawn(temp);
                        }
    
                        heldBlock.spawn(*heldType);
                        heldBlock.setPivotPos(holdBoxCenter);
    
                        canHold = false;
                        timer = 0;
                    }
                }
            }
        }

        window.clear();

        text.setString("Score: " + std::to_string(score));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            currentSpeed = fastSpeed;
        } else {
            updateSpeed();
        }

        if(timer > currentSpeed){
            currentBlock.moveDown();

            if (board.isCollision(currentBlock)) {
                currentBlock.moveUp();
                board.lockBlock(currentBlock);

                canHold = true;

                currentBlock.spawn(nextType);

                nextType = factory.nextBlockType();
                nextBlock.spawn(nextType);
                nextBlock.setPivotPos(previewBoxCenter);

                int lines = board.clearFullLines();
                score += calculateScore(lines, level);
                linesCleared += lines;
            }

            timer = 0;
        }

        board.draw(window);

        window.draw(previewBoxSprite);
        window.draw(holdBoxSprite);
        window.draw(text);
        if (heldType.has_value()) {
            heldBlock.draw(window);
        }

        currentBlock.draw(window);
        nextBlock.draw(window);

        window.display();
    }
}