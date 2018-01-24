#include "characterselectscene.h"

const std::vector<std::string> stringOptions {"Play", "Exit"};

CharacterSelectScene::CharacterSelectScene(Application &application) :
    MenuScene(application)
{

}


void CharacterSelectScene::draw(float deltaTime)
{
    m_app.window.draw(m_background);
}

void CharacterSelectScene::update(float deltaTime)
{
}

void CharacterSelectScene::handleInput(sf::Keyboard::Key keyCode)
{
    switch (keyCode)
    {

    case sf::Keyboard::Escape:
    {
        m_app.popScene();
        break;
    }

    default:
        break;

    }
}

void CharacterSelectScene::setupOptions()
{

}
