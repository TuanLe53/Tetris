#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <entities/block.hpp>
#include <entities/factory.hpp>
#include <board.hpp>

const float fastSpeed = 0.05f;
float currentSpeed;
float timer = 0;
int linesCleared = 0;
int level = 0;
std::vector<float> gravityTable = {0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.2f, 0.15f, 0.1f};

void updateSpeed(){
    level = linesCleared / 10;
    if(level < gravityTable.size()){
        currentSpeed = gravityTable[level];
    }else{
        currentSpeed = gravityTable.back();
    }
}

int score = 0;
Board board = Board();
Factory factory = Factory();
Block currentBlock = Block(factory.nextBlockType());
Tetris::BlockType nextType = factory.nextBlockType();
Block nextBlock = Block(nextType);

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML works!");
    sf::Clock clock;
    
    nextBlock.setPivotPos({700, 700});

    sf::RectangleShape line({350.f, 500.f});
    line.setPosition({650.f, 500.f});

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
            }
        }

        window.clear();

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

                currentBlock.spawn(nextType);

                nextType = factory.nextBlockType();
                nextBlock.spawn(nextType);
                nextBlock.setPivotPos({700, 700});

                int lines = board.clearFullLines();
                score += 50*lines;
                linesCleared += lines;
            }

            timer = 0;
        }

        board.draw(window);
        window.draw(line);
        currentBlock.draw(window);
        nextBlock.draw(window);

        window.display();
    }
}