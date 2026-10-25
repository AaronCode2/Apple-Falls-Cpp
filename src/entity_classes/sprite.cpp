#include "Sprite.hpp"

Sprite::Sprite(Rectangle object, ImageIndex index) {

    this->object = object;

    srcRect.width = Textures::texture[index].GetFrameSize().x;
    srcRect.height = Textures::texture[index].GetFrameSize().y;
    srcRect.y = 0;
    srcRect.x = 0;
}

void Sprite::update() {
    
    srcRect.x = srcRect.width * currentFrame;

    animate();
    draw();
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