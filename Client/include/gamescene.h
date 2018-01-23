#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "iscene.h"

class GameScene : public IScene
{
public:
    GameScene(sf::RenderWindow& window);

    void draw(float deltaTime) override;
    void update(float deltaTime) override;
    void handleInput(sf::Keyboard::Key keyCode) override;
};

#endif // GAMESCENE_H
