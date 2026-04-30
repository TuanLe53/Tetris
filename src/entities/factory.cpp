#include <entities/factory.hpp>

Factory::Factory(){
    random_device rd;
    this->rng = mt19937(rd());
    refilBag();
}

void Factory::refilBag(){
    bag = {
        Tetris::BlockType::O, 
        Tetris::BlockType::I, 
        Tetris::BlockType::L,
        Tetris::BlockType::N, 
        Tetris::BlockType::T
    };
    std::shuffle(bag.begin(), bag.end(), rng);
}

Tetris::BlockType Factory::nextBlockType(){
    if (bag.empty()) {
        this->refilBag();
    }
        
    Tetris::BlockType nextType = bag.back();
    bag.pop_back();
    return nextType;
}