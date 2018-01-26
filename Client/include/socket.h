#ifndef SOCKET_H
#define SOCKET_H

#include <SFML/Network.hpp>

#include <thread>

class Application;

class Socket
{
public:
    Socket(Application& application);
    ~Socket();

    void send(sf::Packet &packet);

private:
    Application& m_app;
    sf::TcpSocket m_socket;
    std::thread* receivingThread = nullptr;
    bool m_running = true;

    void receive();
};

#endif // SOCKET_H
