#include "iscene.h"

IScene::IScene(Application &application) :
    m_app(application)
{

}

void IScene::handleEvents()
{
    while (m_app.window.pollEvent(m_event))
    {
        switch (m_event.type)
        {

        case sf::Event::Closed:
        {
            m_app.window.close();
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
