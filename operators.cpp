#include "operators.h"
#include "common.h"

#include <iostream>

sf::Packet& operator<< (sf::Packet& packet, const SharedData::Player& data)
{
    return packet << data.nickname << data.skin;
}

sf::Packet& operator>> (sf::Packet& packet, SharedData::Player& data)
{
    return packet >> data.nickname >> data.skin;
}

sf::Packet& operator<< (sf::Packet& packet, const std::vector<int>& data)
{
    packet << data.size();

    for (const auto& value : data)
    {
        packet << value;
    }

    return packet;
}
