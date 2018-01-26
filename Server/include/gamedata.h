#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <vector>
#include <string>

#include "common.h"

struct GameData
{
    std::vector<int> disabledSkins;
    std::vector<SharedData::Player> players;
};

#endif // GAMEDATA_H
