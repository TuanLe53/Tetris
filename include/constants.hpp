#pragma once

#include <map>
#include <array>

namespace Tetris {
    enum class BlockType { O, I, L, N, T };

    using Matrix5x5 = std::array<std::array<int, 5>, 5>;

    static inline std::map<BlockType, Matrix5x5> SHAPES = {
        {
            BlockType::O,
            {{
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 2, 1, 0},
                {0, 0, 1, 1, 0},
                {0, 0, 0, 0, 0}
            }}
        },
        {
            BlockType::I,
            {{
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 2, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}
            }}
        },
        {
            BlockType::L,
            {{
                {0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 2, 0, 0},
                {0, 0, 1, 1, 0},
                {0, 0, 0, 0, 0}
            }}
        },
        {
            BlockType::N,
            {{
                {0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0},
                {0, 0, 2, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}
            }}
        },
        {
            BlockType::T,
            {{
                {0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 1, 2, 1, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}
            }}
        },
        
    };
}