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
Block block = Block(factory.nextBlockType());

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML works!");
    sf::Clock clock;
    
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
                    block.moveLeft();
                    if (board.isWallCollision(block)) {
                        block.moveRight();
                    }
                }
                if (keyPressed->code == sf::Keyboard::Key::Right) {
                    block.moveRight();
                    if (board.isWallCollision(block)) {
                        block.moveLeft();
                    }
                }
                if(keyPressed->code == sf::Keyboard::Key::X){
                    block.rotate();
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
            block.moveDown();

            if (board.isCollision(block)) {
                block.moveUp();
                board.lockBlock(block);
                Tetris::BlockType nextType = factory.nextBlockType();

                int lines = board.clearFullLines();
                score += 50*lines;
                linesCleared += lines;

                block.spawn(nextType);
            }

            timer -= currentSpeed;
        }

        board.draw(window);
        block.draw(window);

        window.display();
    }
}