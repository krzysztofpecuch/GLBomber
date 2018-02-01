#include "server.h"
#include "common.h"

#include <iostream>
#include <ctime>

const sf::Vector2i initialPlayersTilePositions[] = { {1, 1}, {11, 1}, {1, 11}, {11, 11} };


Server::Server()
{
    srand(time(nullptr));
}

Server::~Server()
{
    m_listen = false;

    for (auto& client : m_clients)
    {
        delete client.second;
    }

    for (auto& thread : m_clientsThreads)
    {
        delete thread.second;
    }
}

void Server::run()
{
    std::cout << "Server has IP: " << sf::IpAddress::getLocalAddress() << std::endl;

    generateMap();

    m_listener.listen(PORT);

    while (m_listen)
    {
        sf::TcpSocket* client = new sf::TcpSocket;

        if (m_listener.accept(*client) == sf::Socket::Done)
        {

            m_clients[m_idToGrant] = client;
            m_clientsThreads[m_idToGrant] = new std::thread(&Server::receiveData, this, m_idToGrant, client);
            m_clientsThreads[m_idToGrant]->detach();
            std::cout << "New client with id " << m_idToGrant << " connected to server!" << std::endl;
            m_idToGrant++;
        }
        else
            delete client;
    }
}

void Server::receiveData(int clientID, sf::TcpSocket *client)
{
    sf::Socket::Status status;

    while (m_listen)
    {
        sf::Packet packet;
        status = client->receive(packet);

        if (status == sf::Socket::Done)
        {
            std::cout << "Message received!" << std::endl;

            int type;

            packet >> type;

            switch (type)
            {

            case PacketType::UpdateSkins:
            {
                packet.clear();
                packet << PacketType::UpdateSkins << m_gameData.disabledSkins;

                client->send(packet);

                break;
            }

            case PacketType::PlayerData:
            {
                SharedData::Player player;
                packet >> player;
                player.position = tileToPixelPosition(initialPlayersTilePositions[clientID]);
                m_gameData.players[clientID] = player;
                m_gameData.disabledSkins.push_back(player.skin);

                packet.clear();
                packet << PacketType::PlayerData << clientID << player;

                for (const auto& client : m_clients)
                {
                    client.second->send(packet);
                }

                packet.clear();
                packet << PacketType::UpdateSkins << m_gameData.disabledSkins;

                for (const auto& client : m_clients)
                {
                    client.second->send(packet);
                }

                break;
            }

            case PacketType::PlayerLeftGame:
            {
                std::cout << "Player has left the game" << std::endl;
                packet.clear();

                if (m_gameData.disabledSkins.size() > 0)
                {
                    m_gameData.disabledSkins.erase([this](int id) -> std::vector<int>::iterator
                    {
                        for (auto it = m_gameData.disabledSkins.begin(); it != m_gameData.disabledSkins.end(); ++it)
                            if (*it == m_gameData.players[id].skin)
                                return it;

                        return m_gameData.disabledSkins.end();
                    }(clientID));
                }

                m_gameData.players.erase(m_gameData.players.find(clientID));

                sf::Packet packet;
                packet << PacketType::UpdateSkins << m_gameData.disabledSkins;

                for (const auto& client : m_clients)
                    client.second->send(packet);

                break;
            }

            case PacketType::GetMap:
            {
                packet.clear();
                packet << PacketType::GetMap;

                for (int row = 0; row < MAP_HEIGHT; ++row)
                {
                    for (int col = 0; col < MAP_WIDTH; ++col)
                    {
                        packet << m_gameData.map[row][col];
                    }
                }

                client->send(packet);

                break;
            }

            default:
                break;
            }
        }
        else if (status == sf::Socket::Disconnected)
        {
            std::cout << "Client disconnected from server." << std::endl;

            if (m_gameData.disabledSkins.size() > 0)
            {
                m_gameData.disabledSkins.erase([this](int id) -> std::vector<int>::iterator
                {
                    for (auto it = m_gameData.disabledSkins.begin(); it != m_gameData.disabledSkins.end(); ++it)
                        if (*it == m_gameData.players[id].skin)
                            return it;

                    return m_gameData.disabledSkins.end();
                }(clientID));
            }

            auto playerIndex = m_gameData.players.find(clientID);

            if (playerIndex != m_gameData.players.end())
                m_gameData.players.erase(playerIndex);

            delete m_clients[clientID];
            m_clients.erase(m_clients.find(clientID));

            delete m_clientsThreads[clientID];
            m_clientsThreads.erase(m_clientsThreads.find(clientID));

            sf::Packet packet;
            packet << PacketType::UpdateSkins << m_gameData.disabledSkins;

            for (const auto& client : m_clients)
                client.second->send(packet);

            m_idToGrant--;

            return;
        }

    }
}

void Server::generateMap()
{
    std::vector<sf::Vector2i> emptyTiles;

    for (int row = 0; row < MAP_HEIGHT; ++row)
    {
        for (int col = 0; col < MAP_WIDTH; ++col)
        {
            // fill borders with solid blocks
            if (row == 0 || row == MAP_HEIGHT - 1 || col == 0 || col == MAP_WIDTH - 1)
            {
                m_gameData.map[row][col] = TileType::SolidTile;
                continue;
            }

            // set solid blocks inside map
            if (row % 2 == 0 && col % 2 == 0)
            {
                m_gameData.map[row][col] = TileType::SolidTile;
                continue;
            }

            // now find positions, where soft blocks can be generated

            // skip tiles in players initial position neihgbourhood
            if (row == 1 || row == MAP_HEIGHT - 2)
            {
                if (col == 1 || col == 2 || col == MAP_WIDTH - 2 || col == MAP_WIDTH - 3)
                    continue;
            }

            if (row == 2 || row == MAP_HEIGHT - 3)
            {
                if (col == 1 || col == MAP_WIDTH - 2)
                    continue;
            }

            emptyTiles.push_back(sf::Vector2i(col, row));
        }
    }

    const int tilesToGenerate = 60;

    for (int i = 0; i < tilesToGenerate; ++i)
    {
        int index = rand() % (emptyTiles.size() - 1);
        sf::Vector2i pos = emptyTiles[index];

        m_gameData.map[pos.y][pos.x] = TileType::SoftTile;

        emptyTiles.erase(std::find(emptyTiles.begin(), emptyTiles.end(), pos));
    }


    std::cout << "Map:" << std::endl << std::endl;

    for (int row = 0; row < MAP_HEIGHT; ++row)
    {
        for (int col = 0; col < MAP_WIDTH; ++col)
        {
            std::cout << m_gameData.map[row][col];
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}
