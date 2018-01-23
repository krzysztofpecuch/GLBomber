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

    sf::RenderWindow window;
	TextureManager textureManager;
	sf::Sprite background;

    void run();

    void pushScene(IScene* scene);
    void popScene();
    void changeCurrentScene(IScene* scene);
    IScene* getCurrentScene() const;

private:

    std::stack<IScene*> m_scenes;


	void loadTextures();
};

#endif // APPLICATION_H
