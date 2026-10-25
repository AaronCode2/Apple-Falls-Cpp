#include "game.hpp"

// I'm doing this all in the main.cpp, to not write more and get more complicated

int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1440, 730, "Apple Falls");
    Image favicon = LoadImage("../assets/icon/favicon.png");

    // Sometimes it doesn't work don't know why?
    SetWindowIcon(favicon); 
    
    SetWindowState(FLAG_WINDOW_MAXIMIZED);
    
    SetTargetFPS(60);
    InitAudioDevice();
    
    UnloadImage(favicon);

    Assets::loadTextures();

    Game game;
    game.run();
}