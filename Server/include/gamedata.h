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
};

#endif // GAMEDATA_H
