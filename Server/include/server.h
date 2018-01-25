#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>

#include <thread>
#include <vector>
#include <map>

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

    std::map<int, sf::TcpSocket*> m_clients;
    std::map<int, std::thread*> m_clientsThreads;

    void manageConnections();
    void receiveData(int clientID, sf::TcpSocket* client);
};

#endif // SERVER_H
