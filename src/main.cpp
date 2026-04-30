#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <entities/block.hpp>
#include <entities/factory.hpp>
#include <board.hpp>

const float defaultSpeed = 0.7f;
const float fastSpeed = 0.05f;
float currentSpeed = defaultSpeed;

int score = 0;
Board board = Board();
Factory factory = Factory();
Block block = Block(factory.nextBlockType());

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "SFML works!");
    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

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
            currentSpeed = defaultSpeed;
        }

        if(clock.getElapsedTime().asSeconds() >= currentSpeed){
            block.moveDown();

            if (board.isCollision(block)) {
                block.moveUp();
                board.lockBlock(block);
                Tetris::BlockType nextType = factory.nextBlockType();

                int lines = board.clearFullLines();
                score += 50*lines;

                block.spawn(nextType);
            }

            clock.restart();
        }

        board.draw(window);
        block.draw(window);

        window.display();
    }
}