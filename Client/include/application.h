#ifndef APPLICATION_H
#define APPLICATION_H

#include "texturemanager.h"
#include "animationhandler.h"
#include "tile.h"
#include "socket.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <stack>
#include <map>

enum class FontType
{
    Menu
};

class IScene;

class Application
{
public:
    Application();
    ~Application();

    sf::RenderWindow                window;
    TextureManager                  textureManager;
    std::map<TileType::Type, Tile>  tileAtlas;

    void run();

    const sf::Font& getFont(FontType type);

    void    pushScene(IScene* scene);
    void    popScene();
    void    changeCurrentScene(IScene* scene);
    IScene* getCurrentScene() const;



    void sendToServer(sf::Packet& packet);
    void connectToServer();
    void disconnectFromServer();

private:
    std::stack<IScene*>             m_scenes;
    std::map<FontType, sf::Font>    m_fonts;
    sf::Event                       m_event;
    Socket                          m_socket;

	void loadTextures();
	void loadTiles();
    void loadFonts();

    void handleEvents();
};

#endif // APPLICATION_H
