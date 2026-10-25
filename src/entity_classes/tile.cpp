#include "tile.hpp"

Texture2D Tile::image[NUM_OF_TILE_IMAGES];

Tile::Tile(Vector2 position, TileType type): 
    Sprite(
        position, 
        Tile::image[Utils::getRightTileImage(type)],
        Utils::getRightTileMaxFrames(type)
    )
{

    this->type = type;

    configureTile();
}

void Tile::update() {

    draw();
    updateHitBox();
}

void Tile::move(const Vector2 newVelocity) {

    velocity = newVelocity;

    object.x += velocity.x * GetFrameTime();
    object.y += velocity.y * GetFrameTime();

    velocity = {0, 0};
}

void Tile::draw() {

    DrawTextureRec(
        Tile::image[Utils::getRightTileImage(type)],
        srcRect, {std::floorf(object.x), std::floorf(object.y)},
        WHITE
    );
}

void Tile::updateHitBox() {

    hitBox = {
        object.x + hitBoxAdj.x,
        object.y + hitBoxAdj.y,
        object.width + hitBoxAdj.width,
        object.height + hitBoxAdj.height,
    };

    // Utils::debugRect(hitBox);
}

void Tile::configureTile() {

    switch((ImageTileType) Utils::getRightTileImage(type)) {

        case ImageTileType::COIN:
        case ImageTileType::WILLOW_TREE:
        case ImageTileType::TREE:
        case ImageTileType::FLAG:
        case ImageTileType::SIGN:
        case ImageTileType::GRASS:
            colliable = false;
            break;
    }

    configureHitBoxAdj();

    srcRect.x = srcRect.width * Utils::tileFrameMap[type].x;
    srcRect.y = srcRect.height * Utils::tileFrameMap[type].y;

    configureSrcAdj();
}

void Tile::configureHitBoxAdj() {

    switch(type) {

        case TileType::SINGLE_PLATFORM:  
        case TileType::PLATFORM_LEFT: 
        case TileType::PLATFORM_MIDDLE: 
        case TileType::PLATFORM_RIGHT:
            hitBoxAdj = {0, 0, 0, -40};
            break;

        case TileType::SINGLE_LEFT_PLATFORM:
            hitBoxAdj = {0, 0, -32, -40};
            break;

        case TileType::SINGLE_RIGHT_PLATFORM:
            hitBoxAdj = {32, 0, -32, -40};
            break;

        case TileType::WATER_PLAT_1:
        case TileType::WATER_PLAT_2:
        case TileType::WATER_PLAT_3:
        case TileType::WATER_PLAT_4:
        case TileType::WATER_PLAT_5:
            hitBoxAdj = {0, 40, 0, -40};
            break;

        case TileType::WATER_PLAT_6:
            hitBoxAdj = {14, 0, -26, 0};
            break;

        case TileType::FULL_HOLLOW_MIDDLE:
            colliable = false;
            break;
    }
}

void Tile::configureSrcAdj() {

    // Due to raylib using ints, not floats, we have to do this :(

    switch(type) {

        case TileType::PLATFORM_RIGHT:
            srcRect.width -= 1;
            srcRect.height -= 1;
            break;

        case TileType::PLATFORM_LEFT:
            srcRect.x += 1;
            srcRect.height -= 1;
            break;

        case TileType::PLATFORM_MIDDLE:
            srcRect.height -= 1;
            break;
    }
}
