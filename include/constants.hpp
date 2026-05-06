#pragma once

#include <map>
#include <array>

namespace Tetris {
    enum class BlockType { O, I, L, J, S, Z, T };

    using Matrix5x5 = std::array<std::array<int, 5>, 5>;

    static inline std::map<BlockType, std::string> TEXTURE_PATHS = {
        {BlockType::O, "assets/graphics/block/yellow_block.png"},
        {BlockType::I, "assets/graphics/block/cyan_block.png"},
        {BlockType::L, "assets/graphics/block/pink_block.png"},
        {BlockType::J, "assets/graphics/block/blue_block.png"},
        {BlockType::S, "assets/graphics/block/green_block.png"},
        {BlockType::Z, "assets/graphics/block/red_block.png"},
        {BlockType::T, "assets/graphics/block/purple_block.png"}
    };

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
            BlockType::J,
            {{
                {0, 0, 0, 0, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 2, 0, 0},
                {0, 1, 1, 0, 0},
                {0, 0, 0, 0, 0}
            }}
        },
        {
            BlockType::Z,
            {{
                {0, 0, 0, 0, 0},
                {0, 0, 0, 1, 0},
                {0, 0, 2, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}
            }}
        },
        {
            BlockType::S,
            {{
                {0, 0, 0, 0, 0},
                {0, 1, 0, 0, 0},
                {0, 1, 2, 0, 0},
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