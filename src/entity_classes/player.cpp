#include "player.hpp"

Texture2D Player::image;

Player::Player(Vector2 position, std::vector<Tile> &tiles):
    Sprite(position, Player::image, IMAGE_PLAYER_MAX_FRAMES), tiles(tiles)     
{

    object.width = srcRect.width;
    object.height = srcRect.height;
}

void Player::update() {
    
    addressInput();
    applyGravity();
    move();

    draw();
}

void Player::draw() {
    
    handleAnimation();

    DrawTextureRec(
        Player::image,
        srcRect, 
        {std::floorf(object.x), std::floorf(object.y)},
        WHITE
    );

}

void Player::move() {

    updateCamera();

    object.x += velocity.x * GetFrameTime();
    collisionX();
    moveCameraX();

    object.y += velocity.y  * GetFrameTime();
    collisionY();
    moveCameraY();
}

void Player::handleAnimation() {

    // My python is against me

    if(velocity.x == 0) {

        if(state != PlayerAnimState::IDLE) {

            state = PlayerAnimState::IDLE;
            currentFrame = 0;
            srcRect.y = 0;
        }
        
        handleDirection();
        animate(PLAYER_IDLE_MAX_FRAMES, PLAYER_IDLE_FRAME_DURATION);
        handleFraming();
    } else {        

        if(state != PlayerAnimState::WALK) {

            state = PlayerAnimState::WALK;
            currentFrame = 0;
            srcRect.y = srcRect.height;
        }

        handleDirection();
        handleFraming();
        animate(PLAYER_WALK_MAX_FRAMES, PLAYER_WALK_FRAME_DURATION);
    }
}

void Player::handleFraming() {

    if(direction == Dir::RIGHT)
        srcRect.x = srcRect.width * currentFrame;
    else
        srcRect.x = srcRect.width * (IMAGE_PLAYER_MAX_FRAMES.x - currentFrame);
}

void Player::addressInput() {

    cameraMovement = {0, 0};
    velocity.x = 0;

    if(getInputDipper().goingLeft)
        velocity.x = -PLAYER_SPEED;
    if(getInputDipper().goingRight)
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

    if(getInputDipper().isJumping && isOnGround)
        velocity.y = PLAYER_JUMP_SPEED;
}

void Player::handleDirection() {

    if(velocity.x < 0 && direction == Dir::RIGHT) {

        direction = Dir::LEFT;
        srcRect.width = -srcRect.width;
    } else if(velocity.x > 0 && direction == Dir::LEFT) {

        direction = Dir::RIGHT;
        srcRect.width = abs(srcRect.width);
    }
}

void Player::applyGravity() {

    if(object.y + object.height <= GetScreenHeight() - 100)
        velocity.y += GRAVITY * GetFrameTime();
    else
        velocity.y = 0;
}

void Player::updateHitBox() {

    hitBox = {

        object.x + PLAYER_HITBOX_ADJ.x,
        object.y + PLAYER_HITBOX_ADJ.y,
        object.width + PLAYER_HITBOX_ADJ.width,
        object.height + PLAYER_HITBOX_ADJ.height,   
    };

    // Utils::debugRect(hitBox);
}

void Player::collisionX() {

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

void Player::collisionY() {

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

void Player::moveCameraX() {  

    updateHitBox();

    if(hitBox.x + hitBox.width >= cameraBox.x + cameraBox.width && velocity.x >= 0) {

        cameraMovement.x = -velocity.x;

        const float offset = hitBox.x - object.x + hitBox.width; 
        object.x = cameraBox.x + cameraBox.width - offset;
    }

    if(hitBox.x <= cameraBox.x && velocity.x <= 0) {

        cameraMovement.x = -velocity.x;

        const float offset = hitBox.x - object.x;
        object.x = cameraBox.x - offset;
    }

    updateHitBox();
}

void Player::moveCameraY() {

    updateHitBox();

    if(hitBox.y + hitBox.height >= cameraBox.y + cameraBox.height && velocity.y >= 0) {

        cameraMovement.y = -velocity.y;
        
        const float offset = hitBox.y - object.y + hitBox.height; 
        object.y = cameraBox.y + cameraBox.height - offset;
    }

    if(hitBox.y <= cameraBox.y && velocity.y <= 0) {

        cameraMovement.y = -velocity.y;
        
        const float offset = hitBox.y - object.y;
        object.y = cameraBox.y - offset;
    }

    updateHitBox();
}

// coding is the only happiness I get nower days :(

void Player::updateCamera() {

    cameraBox = {

        CAMERA_BOX_ADJ.x,
        CAMERA_BOX_ADJ.y,
        GetScreenWidth() - CAMERA_BOX_ADJ.width,
        GetScreenHeight() - CAMERA_BOX_ADJ.height,
    };

    // Utils::debugRect(cameraBox);
}