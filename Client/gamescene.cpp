#include "gamescene.h"

GameScene::GameScene(Application &application) :
    IScene(application)
{

}


void GameScene::draw(float deltaTime)
{
}

void GameScene::update(float deltaTime)
{
}

void GameScene::handleInput(sf::Keyboard::Key keyCode)
{
    switch (keyCode)
    {
        case sf::Keyboard::Escape:
    {
        m_app.popScene();
    }

    default:
        break;
    }
}
