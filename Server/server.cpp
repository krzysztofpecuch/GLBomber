#include "server.h"
#include "common.h"

#include <iostream>

Server::Server()
{
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

    m_listener.listen(PORT);

    while (m_listen)
    {
        sf::TcpSocket* client = new sf::TcpSocket;

        if (m_listener.accept(*client) == sf::Socket::Done)
        {
            std::cout << "New client connected to server!" << std::endl;

            m_clients[m_idToGrant] = client;
            m_clientsThreads[m_idToGrant] = new std::thread(&Server::receiveData, this, m_idToGrant, client);
            m_clientsThreads[m_idToGrant]->detach();
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

            case PacketType::PlayerInitialData:
            {
                SharedData::Player data;
                packet >> data;
                packet.clear();

                m_gameData.players[clientID] = data;
                m_gameData.disabledSkins.push_back(data.skin);

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
