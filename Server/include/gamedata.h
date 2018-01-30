#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <vector>
#include <map>
#include <string>

#include "common.h"

struct GameData
{
    std::map<int, SharedData::Player> players;
    std::vector<int> disabledSkins;
    int map[MAP_WIDTH][MAP_HEIGHT] = { {TileType::EmptyTile} };
};

#endif // GAMEDATA_H
