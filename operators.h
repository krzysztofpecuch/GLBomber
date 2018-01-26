#ifndef OPERATORS_H
#define OPERATORS_H

#include <SFML/Network.hpp>

namespace SharedData
{
struct Player;
}

sf::Packet& operator<< (sf::Packet& packet, const SharedData::Player& data);
sf::Packet& operator>> (sf::Packet& packet, SharedData::Player& data);

sf::Packet& operator<< (sf::Packet& packet, const std::vector<int>& data);
sf::Packet& operator>> (sf::Packet& packet, std::vector<int>& data);

#endif // OPERATORS_H
