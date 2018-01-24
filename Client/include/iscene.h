#ifndef ISCENE_H
#define ISCENE_H

#include "application.h"

class IScene
{
public:
    IScene(Application& application);
    virtual ~IScene() = default;

    virtual void draw(float deltaTime) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void handleInput(sf::Keyboard::Key keyCode) = 0;

protected:
    Application& m_app;

};

#endif // ISCENE_H
