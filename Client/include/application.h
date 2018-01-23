#ifndef APPLICATION_H
#define APPLICATION_H

#include "textureManager.h"
#include <SFML/Graphics.hpp>
#include <stack>


class IScene;

class Application
{
public:
    Application();

	TextureManager textureManager;
	sf::Sprite background;

    void run();

private:
    sf::RenderWindow m_window;

    std::stack<IScene*> m_scenes;

    void pushScene(IScene* scene);
    void popScene();
    void changeCurrentScene(IScene* scene);
    IScene* getCurrentScene() const;

	void loadTextures();
};

#endif // APPLICATION_H
