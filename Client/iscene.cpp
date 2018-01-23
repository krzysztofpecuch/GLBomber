#include "iscene.h"

IScene::IScene(sf::RenderWindow &window) :
    m_window(window)
{

}

IScene::~IScene()
{

}

void IScene::handleEvents()
{
    while (m_window.pollEvent(m_event))
    {
        switch (m_event.type)
        {

        case sf::Event::Closed:
        {
            m_window.close();
            break;
        }

        case sf::Event::KeyPressed:
        {
            handleInput(m_event.key.code);
            break;
        }

        default:
            break;

        }
    }
}
