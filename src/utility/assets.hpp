#pragma once
#include "../entity_classes/player.hpp"
#include "../entity_classes/player2.hpp"
#include "../entity_classes/tile.hpp"

namespace Assets {

    
    void loadTextures();

    void _mapImagePaths();

    extern std::map<ImageTileType, std::string> _tileImagePaths;
}