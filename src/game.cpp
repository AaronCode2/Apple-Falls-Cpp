#include "game.hpp"

Game::Game() {

    SetExitKey(KEY_NULL);

    // data.readData(DataMapIndex::DEV_MAP);
}

Game::~Game() {

    // data.writeData(DataMapIndex::DEV_MAP);
}


void Game::gameLoop() {

    SetTargetFPS(60);

    while(!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(backgroundColor);
        updateGame();

        EndDrawing();
    }
    CloseWindow();
}

void Game::updateGame() {

    handleFps();

    world.update(player.getCameraMovement());
    player.update();
}

void Game::handleFps() {

    if(IsKeyPressed(KEY_P)) {
        
        GlobalVar::toggleMaxFPS = !GlobalVar::toggleMaxFPS;

        if(GlobalVar::toggleMaxFPS)
            SetTargetFPS(0);
        else
            SetTargetFPS(60);
    }

    if(!IsWindowFocused() && !GlobalVar::isWindowInactive) {

        SetTargetFPS(30);
        GlobalVar::isWindowInactive = true;

    } else if(IsWindowFocused() && GlobalVar::isWindowInactive) {

        SetTargetFPS(60);
        GlobalVar::isWindowInactive = false;
    }

    DrawFPS(GetScreenHeight() - 40.0f, 40);
}