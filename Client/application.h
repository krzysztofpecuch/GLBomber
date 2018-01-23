#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>
#include <stack>

class IScene;

class Application
{
public:
    Application();

    void run();

private:
    sf::RenderWindow m_window;

    std::stack<IScene*> m_scenes;

    void pushScene(IScene* scene);
    void popScene();
    void changeCurrentScene(IScene* scene);
    IScene* getCurrentScene() const;
};

#endif // APPLICATION_H
