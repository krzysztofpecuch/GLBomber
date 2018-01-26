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

            case PacketType::PlayerInitialData:
            {
                SharedData::Player data;

                packet >> data;

                // process data

                packet.clear();

                packet << PacketType::SkinChoosed << data.skin;

                for (const auto& client : m_clients)
                {
                    client.second->send(packet);
                }

                m_gameData.disabledSkins.push_back(data.skin);

                break;
            }

            case PacketType::DisabledSkinsRequest:
            {
                packet.clear();

                packet << PacketType::DisabledSkinsRequest << m_gameData.disabledSkins;

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

            delete m_clients[clientID];
            m_clients.erase(m_clients.find(clientID));

            delete m_clientsThreads[clientID];
            m_clientsThreads.erase(m_clientsThreads.find(clientID));

            m_idToGrant--;

            return;
        }

    }
}
