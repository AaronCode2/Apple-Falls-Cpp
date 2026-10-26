#pragma once
#include <raylib.h>
#include "sprite.hpp"
#include <math.h>
#include "../utility/utils.hpp"

class Tile : public Sprite {

    public:

        Tile(Vector2 position, TileType type);

        void update();
        void move(const Vector2 newVelocity);

        void setFlagCaptured(TileType newType);

        bool isColliable() const { return colliable; };

        Rectangle getHitBox() const { return hitBox; };

        TileType getType() const { return type; };

        static Texture2D image[NUM_OF_TILE_IMAGES];

    private:

        void draw();
        void updateHitBox();

        void configureTile();
        void configureHitBoxAdj();
        void configureSrcAdj();

        void animateTile();

        bool colliable = true;

        TileType type;
        Rectangle hitBox;
        Rectangle hitBoxAdj = {0, 0, 0, 0};
};