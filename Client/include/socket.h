#ifndef SOCKET_H
#define SOCKET_H

#include <SFML/Network.hpp>

#include <thread>


class Socket
{
public:
    Socket();
    ~Socket();

//    void connect();
    void send(sf::Packet &packet);

private:
    sf::TcpSocket m_socket;
    std::thread* receivingThread = nullptr;
    bool m_running = true;

    void receive();
};

#endif // SOCKET_H
