#include "game.hpp"

Game::Game() {

    SetExitKey(KEY_NULL);

    Utils::mapTileFrames();
    data.readData();
}

Game::~Game() {

    // data.writeData();
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

    DrawText(Utils::toString(dipper.getCoins() + mabel.getCoins()).c_str(), 100, 100, 20, GREEN);

    DrawFPS(GetScreenHeight() - 40.0f, 40);

    world.update(dipper.getCameraMovement());
    dipper.update();
    mabel.update(dipper.getCameraMovement());
}