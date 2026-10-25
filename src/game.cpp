#include "game.hpp"

Game::Game() {

    SetExitKey(KEY_NULL);

    Utils::mapTileFrames();
    data.readData();
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

    DrawFPS(GetScreenHeight() - 40.0f, 40);

    world.update(player.getCameraMovement());
    player.update();
}