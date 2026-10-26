#include "player2.hpp"

Texture2D Player2::image;

Player2::Player2(Vector2 position, std::vector<Tile> &tiles):
    Sprite(position, Player2::image, IMAGE_PLAYER2_MAX_FRAMES), tiles(tiles)     
{

    object.width = srcRect.width;
    object.height = srcRect.height;
}

void Player2::update(Vector2 cameraMovement) {
    
    addressInput();

    if(cameraMovement != (Vector2) {0, 0}) {

        object.x += cameraMovement.x * GetFrameTime();
        object.y += cameraMovement.y * GetFrameTime();
    }

    applyGravity();
    move();

    draw();
}

void Player2::draw() {
    
    handleAnimation();

    DrawTextureRec(
        Player2::image,
        srcRect, 
        {std::floorf(object.x), std::floorf(object.y)},
        WHITE
    );

}

void Player2::move() {

    object.x += velocity.x * GetFrameTime();
    collisionX();

    object.y += velocity.y  * GetFrameTime();
    collisionY();
}

void Player2::handleAnimation() {

    // My python is against me

    if(velocity.x == 0) {

        if(state != PlayerAnimState::IDLE) {

            state = PlayerAnimState::IDLE;
            currentFrame = 0;
            srcRect.y = 0;
        }
        
        handleDirection();
        animate(PLAYER2_IDLE_MAX_FRAMES, PLAYER2_IDLE_FRAME_DURATION);
        handleFraming();
    } else {        

        if(state != PlayerAnimState::WALK) {

            state = PlayerAnimState::WALK;
            currentFrame = 0;
            srcRect.y = srcRect.height;
        }

        handleDirection();
        handleFraming();
        animate(PLAYER2_WALK_MAX_FRAMES, PLAYER2_WALK_FRAME_DURATION);
    }
}

void Player2::handleFraming() {

    if(direction == Dir::RIGHT)
        srcRect.x = srcRect.width * currentFrame;
    else
        srcRect.x = srcRect.width * (IMAGE_PLAYER2_MAX_FRAMES.x - currentFrame);
}

void Player2::addressInput() {
    velocity.x = 0;

    if(getInputMabel().goingLeft)
        velocity.x = -PLAYER_SPEED;
    if(getInputMabel().goingRight)
        velocity.x = PLAYER_SPEED;

    bool isOnGround = false;

    for(auto &tile : tiles) {

        if(not CheckCollisionRecs(object, tile.getHitBox()) or !tile.isColliable())
            continue;
        else {

            isOnGround = true;
            break;
        }
    }

    if(getInputMabel().isJumping && isOnGround)
        velocity.y = PLAYER_JUMP_SPEED;
}

void Player2::handleDirection() {

    if(velocity.x < 0 && direction == Dir::RIGHT) {

        direction = Dir::LEFT;
        srcRect.width = -srcRect.width;
    } else if(velocity.x > 0 && direction == Dir::LEFT) {

        direction = Dir::RIGHT;
        srcRect.width = abs(srcRect.width);
    }
}

void Player2::resetPosition() {

    object.x = MABEL_RESET_POSITION.x;
    object.y = MABEL_RESET_POSITION.y;
}

void Player2::applyGravity() {

    if(!CheckCollisionRecs(hitBox, Utils::getScreenRect()))
        resetPosition();

    if(object.y + object.height <= GetScreenHeight() - 100)
        velocity.y += GRAVITY * GetFrameTime();
    else
        velocity.y = 0;

    print(velocity.y);
}

void Player2::updateHitBox() {

    hitBox = {

        object.x + PLAYER2_HITBOX_ADJ.x,
        object.y + PLAYER2_HITBOX_ADJ.y,
        object.width + PLAYER2_HITBOX_ADJ.width,
        object.height + PLAYER2_HITBOX_ADJ.height,   
    };

    // Utils::debugRect(hitBox);
}

void Player2::collisionX() {

    updateHitBox();

    for(auto it = tiles.begin(); it != tiles.end(); it++) {



        if(!it->isColliable())
            continue;



        if(CheckCollisionRecs(hitBox, it->getHitBox())) {

            if(it->getType() == TileType::FLAG_GREEN && capturedFlag == false) {

                it->setFlagCaptured(TileType::FLAG_END_BLUE);
                continue;
            }

            if(it->getType() == TileType::COIN) {

                coins++;

                it = tiles.erase(it);
                continue;
            }

            if(velocity.x > 0) {
                
                const float offset = hitBox.x - object.x + hitBox.width;
                
                object.x = it->getHitBox().x - offset - COL_ADJUST;
            }
            
            if(velocity.x < 0) {
                
                const float offset = hitBox.x - object.x;
                
                object.x = it->getHitBox().x + it->getHitBox().width - offset + COL_ADJUST;
            }

            velocity.x = 0;
        }
    }
}

void Player2::collisionY() {

    updateHitBox();

    for(auto it = tiles.begin(); it != tiles.end(); it++) {

        if(!it->isColliable())
            continue;

        if(CheckCollisionRecs(hitBox, it->getHitBox())) {

            if(it->getType() == TileType::FLAG_GREEN && capturedFlag == false) {

                it->setFlagCaptured(TileType::FLAG_END_BLUE);
                continue;
            }

            if(it->getType() == TileType::COIN) {

                coins++;
                it = tiles.erase(it);
                continue;
            }

            if(velocity.y > 0) {
                
                velocity.y = 0;
                
                const float offset = hitBox.y - object.y + hitBox.height;
                
                object.y = it->getHitBox().y - offset - COL_ADJUST;
            }

            if(velocity.y < 0) {

                velocity.y = 0;

                const float offset = hitBox.y - object.y;

                object.y = it->getHitBox().y + it->getHitBox().height - offset + COL_ADJUST;
            }
        }
    }
}

// coding is the only happiness I get nower days :(