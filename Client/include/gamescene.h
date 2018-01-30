#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "iscene.h"

class GameScene : public IScene
{
public:
    GameScene(Application& application);
    ~GameScene();

    void draw(float deltaTime) override;
    void update(float deltaTime) override;
    void handleInput(sf::Keyboard::Key keyCode) override;

private:
	std::vector<Tile> tiles;

};

#endif // GAMESCENE_H
