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
    for (const auto& value : data)
    {
        packet << value;
    }

    return packet;
}

sf::Packet& operator>> (sf::Packet& packet, std::vector<int>& data)
{
    const char* stuff = static_cast<const char*>(packet.getData());

    for (unsigned i = 0; i < packet.getDataSize(); ++i)
    {
        std::cout << i + 1 << ": " << static_cast<int>(stuff[i]) << std::endl;
    }

    return packet;
}
