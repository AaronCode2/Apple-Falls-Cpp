#pragma once
#include <raylib.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include <math.h>
#include <map>
#include <string>
#include "../entity_classes/tile.hpp"
#include "../utility/utils.hpp"

// Using thirdparty lib called json for data, README: [https://github.com/nlohmann/json]

using Json = nlohmann::json;

class Data {

    public:

        Data(std::vector<Tile> &tiles, Rectangle &playerObject, Vector2 &worldPos);

        void writeData();
        void readData();

    private:

        Json data;

        std::vector<Tile> &tiles;
        Rectangle &playerObject;
        Vector2 &worldPos;
};