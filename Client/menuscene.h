#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "iscene.h"


class MenuScene : public IScene
{
public:
    MenuScene(sf::RenderWindow& window);

    void draw(float deltaTime) override;
    void update(float deltaTime) override;
    void handleInput(sf::Keyboard::Key keyCode) override;


};

#endif // MENUSCENE_H
