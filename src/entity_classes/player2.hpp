#pragma once
#include "sprite.hpp"
#include "../utility/utils.hpp"
#include "tile.hpp"
#include <raylib.h>
#include <vector>
#include <math.h>

class Player2 : public Sprite {


    public:

        Player2(Vector2 position, std::vector<Tile> &tiles);

        void update(Vector2 cameraMovement);

        int getCoins() const { return coins; };

        Vector2 getVelocity() const { return velocity; };

        Rectangle &getObject_r() { return object; };
        Rectangle getObject() { return object; };

        static Texture2D image;

    private:

        Vector2 velocity = {0, 0};

        void draw();
        void move();
        void handleAnimation();
        void handleFraming();
        void addressInput();
        void handleDirection();

        void resetPosition();

        void applyGravity();
        void updateHitBox();
        
        void collisionX();
        void collisionY();

        void moveCameraX();
        void moveCameraY();
        void updateCamera();

        Dir direction = Dir::RIGHT;
        PlayerAnimState state = PlayerAnimState::IDLE;

        std::vector<Tile> &tiles;

        Rectangle cameraBox;
        Rectangle hitBox;
        
        int coins = 0;
        bool capturedFlag = false;
};