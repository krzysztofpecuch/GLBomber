#ifndef APPLICATION_H
#define APPLICATION_H

#include "textureManager.h"
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

    sf::RenderWindow window;
	TextureManager textureManager;

    void run();

    void pushScene(IScene* scene);
    void popScene();
    void changeCurrentScene(IScene* scene);
    IScene* getCurrentScene() const;

    const sf::Font& getFont(FontType type);

    void sendToServer(sf::Packet& packet);

private:
    std::stack<IScene*> m_scenes;
    std::map<FontType, sf::Font> m_fonts;
    sf::Event m_event;

    Socket m_socket;

	void loadTextures();
    void loadFonts();

    void handleEvents();
};

#endif // APPLICATION_H
