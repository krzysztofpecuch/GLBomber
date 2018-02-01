#include "socket.h"
#include "common.h"
#include "application.h"
#include "characterselectscene.h"
#include "gamescene.h"
#include "player.h"

#include <iostream>

Socket::Socket(Application &application) : m_app(application)
{

}

Socket::~Socket()
{
    m_running = false;
    delete receivingThread;
}

void Socket::send(sf::Packet &packet)
{
    if (m_socket.send(packet) != sf::Socket::Done)
    {
        std::cout << "Cannot send message to server!" << std::endl;
    }
}

void Socket::connect()
{
    std::thread connectingThread([this]()
    {
        if (m_socket.connect(sf::IpAddress::getLocalAddress(), PORT) != sf::Socket::Done)
        {
            std::cout << "Cannot connect to server!" << std::endl;
        }

    });

    connectingThread.detach();

    receivingThread = new std::thread(&Socket::receive, this);
    receivingThread->detach();
}

void Socket::disconnect()
{
    m_socket.disconnect();
}

void Socket::receive()
{
    while (m_running)
    {
        sf::Packet packet;
        sf::Socket::Status status = m_socket.receive(packet);

        if (status != sf::Socket::Done)
            continue;

        int type;
        packet >> type;

        std::cout << "New message type: " << type << std::endl;

        switch (type)
        {

        case PacketType::UpdateSkins:
        {
            std::cout << "UpdateSkins:" << std::endl;
            std::vector<int> skins;

            int size;
            packet >> size;
            std::cout << "Size: " << size << std::endl;

            for (int i = 0; i < size; ++i)
            {
                int data;
                packet >> data;
                std::cout << "Data: " << data << std::endl;

                skins.push_back(data);
            }

            std::cout << std::endl;


            CharacterSelectScene* scene = dynamic_cast<CharacterSelectScene*>(m_app.getCurrentScene());
            if (!scene)
                break;

            scene->updateSkins(skins);

            break;
        }

        case PacketType::GetMap:
        {
            std::vector<int> map;

            for (int i = 0; i < MAP_HEIGHT * MAP_WIDTH; ++i)
            {
                int tile;
                packet >> tile;

                map.push_back(tile);
            }

            GameScene* scene = dynamic_cast<GameScene*>(m_app.getCurrentScene());
            if (!scene)
                break;

            scene->setMap(map);

            break;
        }

        case PacketType::PlayerData:
        {
            int id;
            SharedData::Player playerInfo;

            packet >> id >> playerInfo;

            GameScene* scene = dynamic_cast<GameScene*>(m_app.getCurrentScene());
            if (!scene)
                break;

            std::map<int, TextureType> skinToTexture
            {
                { SkinType::Skin1, TextureType::Player1 },
                { SkinType::Skin2, TextureType::Player1 },
                { SkinType::Skin3, TextureType::Player1 },
                { SkinType::Skin4, TextureType::Player1 },
            };

            Player player(m_app.textureManager.getRef(skinToTexture[playerInfo.skin]), playerInfo.nickname, playerInfo.position);

            scene->addPlayer(id, player);

            break;
        }

        default:
            break;
        }
    }
}
