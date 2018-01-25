#include "operators.h"

#include "common.h"

sf::Packet& operator<< (sf::Packet& packet, const PlayerInitialData& data)
{
    return packet << data.nickname << data.skin;
}

sf::Packet& operator>> (sf::Packet& packet, PlayerInitialData& data)
{
    return packet >> data.nickname >> data.skin;
}
