#ifndef OPERATORS_H
#define OPERATORS_H

#include <SFML/Network.hpp>

// /forward declaration
namespace SharedData
{
struct Player;
}

sf::Packet& operator<< (sf::Packet& packet, const SharedData::Player&   data);
sf::Packet& operator>> (sf::Packet& packet, SharedData::Player&         data);

sf::Packet& operator<< (sf::Packet& packet, const std::vector<int>&     data);

//template <class T>
//sf::Packet& operator<< (sf::Packet& packet, const sf::Vector2<T>& data)
//{
//    packet << data.x << data.y;

//    return packet;
//}

//template <class T>
//sf::Packet& operator>> (sf::Packet& packet, sf::Vector2<T>& data)
//{
//    packet >> data.x >> data.y;

//    return packet;
//}

#endif // OPERATORS_H
