#include "assets.hpp"

std::map<ImageTileType, std::string> Assets::_tileImagePaths;

void Assets::loadTextures() {

    Player::image = LoadTexture(IMAGE_PLAYER_PATH);

    _mapImagePaths();

    // Uses CPU upscaling

    Image images[NUM_OF_TILE_IMAGES];

    for(int i = 0; i < NUM_OF_TILE_IMAGES; i++) {

        images[i] = LoadImage(_tileImagePaths[(ImageTileType) i].c_str());

        ImageResize(
            &images[i], 
            images[i].width * 2, 
            images[i].height * 2
        );

        
        Tile::image[i] = LoadTextureFromImage(images[i]);
    }
}

void Assets::_mapImagePaths() {

    _tileImagePaths[ImageTileType::TILE] = "../assets/tiles/tileset.png";
    _tileImagePaths[ImageTileType::SIGN] = "../assets/tiles/sign.png";
    _tileImagePaths[ImageTileType::TREE] = "../assets/tiles/trees.png";
    _tileImagePaths[ImageTileType::WILLOW_TREE] = "../assets/tiles/willow_trees.png";
    _tileImagePaths[ImageTileType::GRASS] = "../assets/tiles/grass.png";
    _tileImagePaths[ImageTileType::FLAG] = "../assets/tiles/flag.png";
    _tileImagePaths[ImageTileType::COIN] = "../assets/tiles/coin.png";
}