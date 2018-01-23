#ifndef ISCENE_H
#define ISCENE_H

#include "application.h"

class IScene
{
public:
    IScene(sf::RenderWindow& window);
    virtual ~IScene();

    virtual void draw(float deltaTime) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void handleInput(sf::Keyboard::Key keyCode) = 0;

    void handleEvents();

private:
    sf::RenderWindow& m_window;
    sf::Event m_event;
};

#endif // ISCENE_H
