#include "Utils.hpp"

Input getInputDipper() {

    return {

        (IsKeyDown(KEY_A)),
        (IsKeyDown(KEY_D)),
        (IsKeyPressed(KEY_W))
    };
}

Input getInputMabel() {

    return {

        (IsKeyDown(KEY_LEFT)),
        (IsKeyDown(KEY_RIGHT)),
        (IsKeyPressed(KEY_UP))
    };
}

int Utils::selectedtileTypeIndex = 0;
Color const Utils::testColor = {255, 0, 0, 100};
float Utils::deltaTimeIt = 0.0f;
bool Utils::hackerMode = false;

std::map<TileType, Vector2> Utils::tileFrameMap;

void Utils::mapTileFrames(){

    Utils::tileFrameMap[TileType::LEFT_UP_FULL_CORNER] = {0, 0};
    Utils::tileFrameMap[TileType::MIDLLE_UPPER_FULL_CORNER] = {1, 0};
    Utils::tileFrameMap[TileType::RIGHT_UP_FULL_CORNER] = {2, 0};
    Utils::tileFrameMap[TileType::LEFT_FULL_MIDDLE_SIDE] = {0, 1};
    Utils::tileFrameMap[TileType::FULL_HOLLOW_MIDDLE] = {1, 1};
    Utils::tileFrameMap[TileType::RIGHT_FULL_SIDE] = {2, 1};
    Utils::tileFrameMap[TileType::LEFT_DOWN_FULL_CORNER] = {0, 2};
    Utils::tileFrameMap[TileType::DOWN_FULL_SIDE] = {1, 2};
    Utils::tileFrameMap[TileType::RIGHT_DOWN_FULL_CORNER] = {2, 2};

    Utils::tileFrameMap[TileType::SINGLE_FULL] = {0, 3};
    Utils::tileFrameMap[TileType::SINGLE_CORNER_LEFT] = {1, 3};
    Utils::tileFrameMap[TileType::SINGLE_MIDDLE] = {2, 3};
    Utils::tileFrameMap[TileType::SINGLE_CORNER_RIGHT] = {3, 3};

    Utils::tileFrameMap[TileType::PLATFORM_LEFT] = {6, 0}; 
    Utils::tileFrameMap[TileType::PLATFORM_MIDDLE] = {7, 0};
    Utils::tileFrameMap[TileType::PLATFORM_RIGHT] = {8, 0};

    Utils::tileFrameMap[TileType::SINGLE_PLATFORM] = {8, 3};
    Utils::tileFrameMap[TileType::SINGLE_LEFT_PLATFORM] = {8, 5};
    Utils::tileFrameMap[TileType::SINGLE_RIGHT_PLATFORM] = {8, 4};

    Utils::tileFrameMap[TileType::WATER_PLAT_1] = {9, 0};
    Utils::tileFrameMap[TileType::WATER_PLAT_2] = {9, 1};
    Utils::tileFrameMap[TileType::WATER_PLAT_3] = {9, 2};
    Utils::tileFrameMap[TileType::WATER_PLAT_4] = {9, 3};
    Utils::tileFrameMap[TileType::WATER_PLAT_5] = {9, 4};
    Utils::tileFrameMap[TileType::WATER_PLAT_6] = {9, 5};

    Utils::tileFrameMap[TileType::SIGN_FORWARD] = {0, 0};
    Utils::tileFrameMap[TileType::SIGN_BACKWARD] = {1, 0};
    Utils::tileFrameMap[TileType::SIGN_UP_FORWARD] = {2, 0};
    Utils::tileFrameMap[TileType::SIGN_UP_BACKWARD] = {3, 0};
    Utils::tileFrameMap[TileType::SIGN_DOWN_FORWARD] = {4, 0};
    Utils::tileFrameMap[TileType::SIGN_DOWN_BACKWARD] = {5, 0};
    Utils::tileFrameMap[TileType::SIGN_X] = {6, 0};
    Utils::tileFrameMap[TileType::SIGN_EXCLAMATORY] = {7, 0};

    Utils::tileFrameMap[TileType::TREE_SMALL] = {0, 0};
    Utils::tileFrameMap[TileType::TREE_MED] = {1, 0};
    Utils::tileFrameMap[TileType::TREE_LARGE] = {2, 0};

    Utils::tileFrameMap[TileType::WILLOW_TREE_SMALL] = {0, 0};
    Utils::tileFrameMap[TileType::WILLOW_TREE_MED] = {1, 0};
    Utils::tileFrameMap[TileType::WILLOW_TREE_LARGE] = {2, 0};

    Utils::tileFrameMap[TileType::GRASS_1] = {0, 0};
    Utils::tileFrameMap[TileType::GRASS_2] = {1, 0};
    Utils::tileFrameMap[TileType::GRASS_3] = {2, 0};
    Utils::tileFrameMap[TileType::GRASS_4] = {3, 0};
    Utils::tileFrameMap[TileType::GRASS_5] = {4, 0};
    Utils::tileFrameMap[TileType::GRASS_6] = {5, 0};
    Utils::tileFrameMap[TileType::GRASS_7] = {6, 0};
    Utils::tileFrameMap[TileType::GRASS_8] = {7, 0};
    Utils::tileFrameMap[TileType::GRASS_9] = {8, 0};
    Utils::tileFrameMap[TileType::GRASS_10] = {9, 0};

    Utils::tileFrameMap[TileType::FLAG_GREEN] = {0, 0};
    Utils::tileFrameMap[TileType::FLAG_END_BLUE] = {0, 1};
    Utils::tileFrameMap[TileType::FLAG_END_RED] = {0, 2};
    Utils::tileFrameMap[TileType::COIN] = {0, 0};
}

std::string Utils::toString(int num) {


#if defined(__GNUC__) || defined(__clang__)

    return std::to_string(num);

#else

    return to_string(num);

#endif

}

int Utils::getRightTileImage(const TileType type) {


    // Since the images are separate, we need to figure out which image to give.

    const int typeIndex = (int) type;

    if(typeIndex > 24 && typeIndex < 33) 
        return (int) ImageTileType::SIGN;
    if(typeIndex > 32 && typeIndex < 36)
        return (int) ImageTileType::TREE;
    if(typeIndex > 35 && typeIndex < 39)
        return (int) ImageTileType::WILLOW_TREE;
    if(typeIndex > 38 && typeIndex < 49)
        return (int) ImageTileType::GRASS;
            
    if(typeIndex <= 24)
        return (int) ImageTileType::TILE;

    if(typeIndex > 48 && typeIndex < 52)
        return (int) ImageTileType::BANNER;
        // self.collidable = False
        // self.maxAnimationFrames = 4
        // self.elapsedFrame = 0.0
        // self.frameduration = 0.3
        // self.animationFrame = 0

        
        // self.srcRect = pygame.Rect(
        //     utils.imagesWidth[5] * utils.tileTypeCords[self.type][0],
        //     utils.imagesHeight[5] * utils.tileTypeCords[self.type][1],
        //     utils.imagesWidth[5], utils.imagesHeight[5]
        // )
    if(typeIndex == 52)
        return (int) ImageTileType::COIN;
        // self.collidable = True
        // self.maxAnimationFrames = 4
        // self.elapsedFrame = 0.0
        // self.frameduration = 0.15
        // self.animationFrame = 0
        
        
        // self.srcRect = pygame.Rect(
        //     utils.imagesWidth[6] * utils.tileTypeCords[self.type][0],
        //     utils.imagesHeight[6] * utils.tileTypeCords[self.type][1],
        //     utils.imagesWidth[6], utils.imagesHeight[6]
        // )

}

Vector2 Utils::getRightTileMaxFrames(const TileType type) {

    // It random Values, can't be bothered to map it

    const int typeIndex = (int) type;

    if(typeIndex > 24 && typeIndex < 33) 
        return {8.0f, 1.0f};
    if(typeIndex > 32 && typeIndex < 36)
        return {3.0f, 1.0f};
    if(typeIndex > 35 && typeIndex < 39)
        return {3.0f, 1.0f};
    if(typeIndex > 38 && typeIndex < 49)
        return {10.0f, 1.0f};
            
    if(typeIndex <= 24)
        return {10.0f, 6.0f};

    if(typeIndex > 48 && typeIndex < 52)
        return {4.0f, 3.0f};
        // self.collidable = False
        // self.maxAnimationFrames = 4
        // self.elapsedFrame = 0.0
        // self.frameduration = 0.3
        // self.animationFrame = 0

        
        // self.srcRect = pygame.Rect(
        //     utils.imagesWidth[5] * utils.tileTypeCords[self.type][0],
        //     utils.imagesHeight[5] * utils.tileTypeCords[self.type][1],
        //     utils.imagesWidth[5], utils.imagesHeight[5]
        // )
    if(typeIndex == 52)
        return {4.0f, 1.0f};
}

Font Utils::font;
int Utils::fontSize;

void Utils::exitApp(const std::string errorInfo) {

    CloseWindow();
    std::cerr << "\033[31m" << errorInfo << '\n';

    std::ofstream file("errors.log");

    file << errorInfo;

    file.close();

#if DEBUG_ENABLED

    __debugbreak;

    std::cout << "Press ENTER to exit the Application as a Error has occured [PLAYER]: ";
    std::cin.get();

    exit(EXIT_FAILURE);
#endif
} 

bool Utils::isSameXY(const Rectangle aObject, const Rectangle bObject) {

    return (
        aObject.x == bObject.x &&
        aObject.y == bObject.y
    );
}

bool Utils::isSameXY(const Vector2 aObject, const Vector2 bObject) {

    return (
        aObject.x == bObject.x &&
        aObject.y == bObject.y
    );
}

bool Utils::isSameXY(const Vector2 aObject, const Vector2 bObject, const Vector2 bObject2) {

    return (
        (
            aObject.x == bObject.x &&
            aObject.y == bObject.y
        ) 
        ||
        (
            aObject.x == bObject2.x &&
            aObject.y == bObject2.y
        )
    );
}

// These funcs are not used LOL, don't use them, I burrowed code thinking I will use these.

void Utils::collisionActionX(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity, bool resetVelocity) {

    // Double-check Collision #BUG-FIX

    if(!CheckCollisionRecs(ahitBox, bHitBox)) 
        return;
            
#if DEBUG_ENABLED

    DrawText("COLLISON X!!!", 400, 400, 30, RED);

#endif
    if(aVelocity.x > 0) {
                
        const float offset = ahitBox.x - aObject.x + ahitBox.width + 0.01;

        aObject.x = bHitBox.x - offset;
    }
        
    if(aVelocity.x < 0) {
                
        const float offset = ahitBox.x - aObject.x - 0.01;

        aObject.x = bHitBox.x + bHitBox.width - offset;
    }

    if(resetVelocity) aVelocity.x = 0;
}

void Utils::collisionActionY(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity, bool resetVelocity) {

    // Double-check Collision #BUG-FIX

    if(!CheckCollisionRecs(ahitBox, bHitBox)) 
        return;

#if DEBUG_ENABLED

    DrawText("COLLISON Y!!!", 400, 400, 30, RED);

#endif

    if(aVelocity.y > 0) {
                
        const float offset = ahitBox.y - aObject.y + ahitBox.height;

        aObject.y = bHitBox.y - offset;
    }
        
    if(aVelocity.y < 0) {
                
        const float offset = ahitBox.y - aObject.y;

        aObject.y = bHitBox.y + bHitBox.height - offset;
    }

    if(resetVelocity) aVelocity.y = 0;
}

Rectangle Utils::getScreenRect() {

    return {0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()};
}

Vector2 Utils::getScreenSizeV() {

    return {(float) GetScreenWidth(), (float) GetScreenHeight()};
}

Rectangle Utils::THE_DEBUG_RECT = {0, 0, 0, 0};
Vector2 Utils::THE_DEBUG_VECTOR = {0, 0};

void Utils::debugRect(Rectangle object) {

    DrawRectangleRec(object, {255, 0, 0, 100});
}

bool Mouse::isHovering(const Rectangle object) {

    return CheckCollisionPointRec(GetMousePosition(), object);
}

bool Mouse::isClickedL(const Rectangle object) {

    return (CheckCollisionPointRec(GetMousePosition(), object) && IsMouseButtonDown(MOUSE_BUTTON_LEFT));
}

bool Mouse::isClickedR(const Rectangle object) {

    return (CheckCollisionPointRec(GetMousePosition(), object) && IsMouseButtonDown(MOUSE_BUTTON_RIGHT));
}

bool Mouse::isClickedOnceL(const Rectangle object) {


    return (CheckCollisionPointRec(GetMousePosition(), object) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

bool Mouse::isClickedOnceR(const Rectangle object) {


    return (CheckCollisionPointRec(GetMousePosition(), object) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT));
}

std::string Utils::formatZeros(int num, int width) {

    // This func can fail when overflow happens, don't know if it works in release?

    std::string numText;
    int leadingZero;

    try {

        numText = std::to_string(num);
        leadingZero = width - numText.length();
    } catch(const std::exception& e) {

#if DEBUG_ENABLED

        std::cerr << e.what() << '\n';
#endif

        Utils::exitApp(
            "Overflow Money, The variable `NumText` value (Integar): " + numText + " To fix simply go to"
            " the Data/Money.txt and edit this to become a number below 4 digits"
        );
    }
    
    if(num >= 0)
        numText = 'x' + std::string(leadingZero, '0') + numText;
    else numText = "x" + numText;

    return numText;
}
