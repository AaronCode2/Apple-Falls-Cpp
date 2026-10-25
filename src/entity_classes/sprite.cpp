#include "Sprite.hpp"

Texture2D Sprite::image;

Sprite::Sprite(Vector2 position, Texture2D image, Vector2 framesMap) {

    this->object.x = position.x;
    this->object.y = position.y;
    this->object.width = (float) image.width / framesMap.x;
    this->object.height = (float) image.height / framesMap.y;

    srcRect = {
        0, 0,
        (float) image.width / framesMap.x,
        (float) image.height / framesMap.y,
    };
}

void Sprite::update() {
    
    srcRect.x = srcRect.width * currentFrame;

    animate();
    draw(Sprite::image);
}

void Sprite::draw(Texture2D image) {

    DrawTexturePro(
        image,
        srcRect, object,
        {0, 0}, 0, WHITE
    );
}

void Sprite::animate(const int frameEnd, const float frameDuration, int frameStart) {

    elapsedFrame += GetFrameTime();

    if(elapsedFrame >= frameDuration) {
        
        elapsedFrame = 0.0f;

        if(currentFrame < frameEnd - 1) currentFrame++;
        else currentFrame = frameStart;
    }
}