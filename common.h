#ifndef COMMON_H
#define COMMON_H

#include <SFML/Network.hpp>

#include <string>

#include "operators.h"

#define PORT 55001

#define MAP_WIDTH 13
#define MAP_HEIGHT 13

#define TILE_SIZE 62

namespace PacketType
{

enum Type
{
    UpdateSkins,
    PlayerLeftGame,
    GetMap,
    GetPlayers,
    AddPlayer,
    RemovePlayer
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

namespace SkinType
{

enum Type
{
    Skin1,
    Skin2,
    Skin3,
    Skin4
};

}

namespace SharedData
{

struct Player
{
    std::string     nickname = "";
    int             skin = 0;
//    SkinType::Type  skin = SkinType::Skin1;
    sf::Vector2f    position = {};
};

}

#endif // COMMON_H

