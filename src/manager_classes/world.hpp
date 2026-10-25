#pragma once
#include <raylib.h>
#include <vector>
#include "../entity_classes/tile.hpp"
#include <math.h>

// Bored, Bored, Boredom.

class World {

    public:

        World();

        void update(const Vector2 cameraMovement);

        std::vector<Tile> &giveTiles();

        Vector2 &getWorldPos_r() { return worldPos; };
        Vector2 getWorldPos() { return worldPos; };

        void setpickedTile(TileType newPickedTile) { pickedTile = newPickedTile; };

    private:

        void dev_tilePlacer();

        void updateTiles(const Vector2 cameraMovement);

        std::vector<Tile> tiles;

        const Vector2 tileSize = {

            (float) Tile::image[0].width / IMAGE_TILE_MAX_FRAMES.x,
            (float) Tile::image[0].height / IMAGE_TILE_MAX_FRAMES.y
        };

        Rectangle tilePlacerRect;
        TileType pickedTile = TileType::SINGLE_FULL;
        
        bool enableTilePlacer = false;

        Vector2 worldPos = {0, 0};
        Vector2 tempWorldVec = {0, 0};
};