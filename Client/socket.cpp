#include "socket.h"

#include <iostream>

Socket::Socket()
{
    std::thread connectingThread([this]()
    {
        if (m_socket.connect(sf::IpAddress::getLocalAddress(), 55001) != sf::Socket::Done)
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

        std::string message;

        packet >> message;

//        std::cout << message << std::endl;
    }
}
