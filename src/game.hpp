#pragma once
#include <iostream>
#include <cstddef>
#include <memory>
#include <raylib.h>
#include "utility/assets.hpp"
#include "entity_classes/sprite.hpp"
#include "entity_classes/player.hpp"
#include "entity_classes/player2.hpp"
#include "utility/data.hpp"
#include "manager_classes/world.hpp"

class Game {

    public:

        Game();
        ~Game();

        void run() { gameLoop(); };

    private:

        Color backgroundColor = {100, 100, 100, 155};

        World world = World();
        Player dipper = Player({200, 50}, world.giveTiles());
        Player2 mabel = Player2({24, 30}, world.giveTiles());

        Data data = Data(world.giveTiles(), dipper.getObject_r(), world.getWorldPos_r());

        void gameLoop();
        void updateGame();
};