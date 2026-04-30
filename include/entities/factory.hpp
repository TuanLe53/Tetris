#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <constants.hpp>

using namespace std;

class Factory{
private:
    vector<Tetris::BlockType> bag;
    mt19937 rng;
public:
    Factory();
    void refilBag();
    Tetris::BlockType nextBlockType();
};