#include "socket.h"
#include "common.h"
#include "application.h"
#include "characterselectscene.h"

#include <iostream>

Socket::Socket(Application &application) : m_app(application)
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

void Socket::receive()
{
    while (m_running)
    {
        sf::Packet packet;
        m_socket.receive(packet);

        int type;
        packet >> type;

        std::cout << "Message type: " << type << std::endl;

        switch (type)
        {

        case PacketType::SkinChoosed:
        {
            int skin;
            packet >> skin;

            CharacterSelectScene* scene = dynamic_cast<CharacterSelectScene*>(m_app.getCurrentScene());
            if (!scene)
                break;

            scene->setSkinDisabled(skin);

            break;
        }
        case PacketType::DisabledSkinsRequest:
        {
            std::vector<int> disabledSkins;

            packet >> disabledSkins;

            break;
        }

        default:
            break;
        }
    }
}
