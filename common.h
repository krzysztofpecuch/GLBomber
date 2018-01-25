#ifndef COMMON_H
#define COMMON_H

#include <SFML/Network.hpp>

#include <string>

#include "operators.h"

#define PORT 55001

namespace PacketType
{
    enum Type
    {
        PlayerInitialData,
        SkinChoosed
    };

}

enum class TileType
{
    SolidTile,
    SoftTile,
    EmptyTile
};

struct PlayerInitialData
{
    std::string nickname;
    int skin;
};

#endif // COMMON_H

