#pragma once
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <map>

#define print(x) std::cout << x << '\n'
#define EMPTY_RECT (Rectangle) {0, 0, 0, 0}
#define WH_EMPTY_RECT (Rectangle) {0, 0, TILE_SIZE, TILE_SIZE}

#define SAVY_YELLOW (Color) {255, 209, 157, 255}
#define MOUSE_BROWN (Color) {163, 90, 66, 255}
#define SAVY_BROWN (Color) {215, 147, 106, 255}
#define DARK_BROWN (Color) {181, 108, 78, 255}

#define FONT_SIZE 30
#define FONT_SPACING 1
#define SLOT_SIZE 120

#define STACK_SIZE 255

// 200 Tiles -> World Size

#define WORLD_SIZE 200

// Some C++ operator magic

inline Vector2 operator<<=(Vector2 &v1, const Vector2 &v2) {

    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

inline Vector2 operator*(Vector2 vec, const float numf) {

    vec.x *= numf;
    vec.y *= numf;
    return vec;
}

inline Vector2 operator*(Vector2 vec1, Vector2 vec2) {

    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    return vec1;
}

inline Vector2 operator+(Vector2 vec1, Vector2 vec2) {

    vec1.x += vec2.x;
    vec1.y += vec2.y;
    return vec1;
}

inline Vector2 operator>>=(Vector2 &v1, const Vector2 &v2) {

    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

// I wanna do something else than coding, It really is a concern. 

inline bool operator!=(const Vector2 &v1, const Vector2 &v2) {

    return (v1.x != v2.x || v1.y != v2.y);
}

inline bool operator==(const Vector2 &v1, const Vector2 &v2) {

    return (v1.x == v2.x && v1.y == v2.y);
}

inline Rectangle operator<<=(Rectangle &v1, const Vector2 &v2) {

    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

struct Input {

    bool goingLeft;
    bool goingRight;
    bool isJumping;
};

Input getInput();

enum class Dir {

    LEFT = 0,
    RIGHT
};

enum class PlayerAnimState {

    IDLE = 0,
    WALK
};

enum class ImageTileType {

    TILE = 0,
    SIGN = 1,
    TREE = 2,
    WILLOW_TREE = 3,
    GRASS = 4,
    FLAG = 5,
    COIN = 6
};

enum class TileType {

    LEFT_UP_FULL_CORNER = 0,
    MIDLLE_UPPER_FULL_CORNER = 1,
    RIGHT_UP_FULL_CORNER = 2,
    LEFT_FULL_MIDDLE_SIDE = 3,
    FULL_HOLLOW_MIDDLE = 4,
    RIGHT_FULL_SIDE = 5,
    LEFT_DOWN_FULL_CORNER = 6,
    DOWN_FULL_SIDE = 7,
    RIGHT_DOWN_FULL_CORNER = 8,

    SINGLE_FULL = 9,
    SINGLE_CORNER_LEFT = 10,
    SINGLE_MIDDLE = 11,
    SINGLE_CORNER_RIGHT = 12,

    PLATFORM_LEFT = 13,
    PLATFORM_MIDDLE = 14,
    PLATFORM_RIGHT = 15,

    SINGLE_PLATFORM = 16,
    SINGLE_LEFT_PLATFORM = 17,
    SINGLE_RIGHT_PLATFORM = 18,

    WATER_PLAT_1 = 19,
    WATER_PLAT_2 = 20,
    WATER_PLAT_3 = 21,
    WATER_PLAT_4 = 22,
    WATER_PLAT_5 = 23,
    WATER_PLAT_6 = 24,

    SIGN_FORWARD = 25,
    SIGN_BACKWARD = 26,
    SIGN_UP_FORWARD = 27,
    SIGN_UP_BACKWARD = 28,
    SIGN_DOWN_FORWARD = 29,
    SIGN_DOWN_BACKWARD = 30,
    SIGN_X = 31,
    SIGN_EXCLAMATORY = 32,

    TREE_SMALL = 33,
    TREE_MED = 34,
    TREE_LARGE = 35,

    WILLOW_TREE_SMALL = 36,
    WILLOW_TREE_MED = 37,
    WILLOW_TREE_LARGE = 38,

    GRASS_1 = 39,
    GRASS_2 = 40,
    GRASS_3 = 41,
    GRASS_4 = 42,
    GRASS_5 = 43,
    GRASS_6 = 44,
    GRASS_7 = 45,
    GRASS_8 = 46,
    GRASS_9 = 47,
    GRASS_10 = 48,

    FLAG_GREEN = 49,
    FLAG_END_BLUE = 50,
    FLAG_END_RED = 51,
    COIN = 52,
};

namespace Utils {

    extern float deltaTimeIt;
    extern Color const testColor;
    Rectangle getScreenRect();
    Vector2 getScreenSizeV();

    std::string formatZeros(int num, int width);
    extern int fontSize;

    bool isSameXY(const Rectangle aObject, const Rectangle bObject);
    bool isSameXY(const Vector2 aObject, const Vector2 bObject);
    bool isSameXY(const Vector2 aObject, const Vector2 bObject, const Vector2 bObject2);
    
    void collisionActionX(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity, bool resetVelocity = true);
    void collisionActionY(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity, bool resetVelocity = true);
    
    void debugRect(Rectangle object);

    void exitApp(const std::string errorInfo);

    extern Font font;

    // Did this for emphasis

    extern Rectangle THE_DEBUG_RECT;
    extern Vector2 THE_DEBUG_VECTOR;
    extern int selectedtileTypeIndex;

    extern bool hackerMode;

    extern std::map<TileType, Vector2> tileFrameMap;

    void mapTileFrames();

    int getRightTileImage(const TileType type);

    Vector2 getRightTileMaxFrames(const TileType type);
} 

namespace Mouse {

    bool isHovering(const Rectangle object);
    bool isClickedL(const Rectangle object);
    bool isClickedR(const Rectangle object);

    bool isClickedOnceR(const Rectangle object);
    bool isClickedOnceL(const Rectangle object);
}

// constants

#define IMAGE_PLAYER_PATH "../assets/player/dipper.png"
#define IMAGE_PLAYER_MAX_FRAMES (Vector2) {7, 2}

#define IMAGE_TILE_MAX_FRAMES (Vector2) {10, 6}

#define PLAYER_IDLE_FRAME_DURATION 0.1f
#define PLAYER_IDLE_MAX_FRAMES 7

#define PLAYER_WALK_FRAME_DURATION 0.09f
#define PLAYER_WALK_MAX_FRAMES 6

#define PLAYER_SPEED 500
#define PLAYER_JUMP_SPEED -1000
#define GRAVITY 1800

#define TILE_WALL_HITBOX_ADJ (Rectangle) {0, 188, 0, -190}
#define PLAYER_HITBOX_ADJ (Rectangle) {5, 12, -16, -15}
#define COL_ADJUST 0.1f
#define CAMERA_BOX_ADJ (Rectangle) {170, 268, 400, 400}

#define NUM_OF_TILE_IMAGES 7 

#define DATA_PATH "../data/dat.json"
#define JSON_INDENT 4