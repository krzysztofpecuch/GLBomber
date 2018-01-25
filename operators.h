#ifndef OPERATORS_H
#define OPERATORS_H

#include <SFML/Network.hpp>

struct PlayerInitialData;

sf::Packet& operator<< (sf::Packet& packet, const PlayerInitialData& data);

sf::Packet& operator>> (sf::Packet& packet, PlayerInitialData& data);

#endif // OPERATORS_H
