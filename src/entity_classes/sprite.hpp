#pragma once
#include <raylib.h>
#include "../utility/utils.hpp"

// The Sprite doesn't store the texture (only staticly)

class Sprite {

    public:

        Sprite(Vector2 postion, Texture2D image, Vector2 framesMap);

        void update();

        Rectangle getObject() const { return object; };

        Rectangle getSrcRect() const { return srcRect; };
        
        static Texture2D image;

    protected:
        
        Rectangle object;
        Vector2 velocity = {0, 0};
        Rectangle srcRect;

        void draw(Texture2D image);
        void animate(const int frameEnd = 6, const float frameDuration = 0.1f, const int frameStart = 0);

        int currentFrame = 0;
        float elapsedFrame = 0;
};