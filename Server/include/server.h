#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>

#include <thread>
#include <vector>
#include <map>

#include "gamedata.h"

class Server
{
public:
    Server();
    ~Server();

    void run();

private:
    sf::TcpListener m_listener;
    bool m_listen = true;
    int m_idToGrant = 0;

    GameData m_gameData;

    std::map<int, sf::TcpSocket*> m_clients;
    std::map<int, std::thread*> m_clientsThreads;

    void receiveData(int clientID, sf::TcpSocket* client);

    void generateMap();

    sf::Vector2f tileToPixelPosition(const sf::Vector2i& position)
    {
        return sf::Vector2f(position * TILE_SIZE);
    }
};

#endif // SERVER_H
