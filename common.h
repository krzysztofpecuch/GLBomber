#ifndef COMMON_H
#define COMMON_H

#include <SFML/Network.hpp>

#include <string>

#include "operators.h"

#define PORT 55001

#define MAP_WIDTH 13
#define MAP_HEIGHT 13

namespace PacketType
{

enum Type
{
    PlayerInitialData,
    UpdateSkins,
    PlayerLeftGame,
    GetMap
};

}

namespace TileType
{

enum Type
{
    EmptyTile,
    SoftTile,
    SolidTile
};

}


namespace SharedData
{

struct Player
{
    std::string nickname;
    int skin;
};

}


#endif // COMMON_H

