#include "application.h"
#include "iscene.h"
#include "menuscene.h"
#include "texturemanager.h"

Application::Application() :
    window(sf::VideoMode(800, 800), "GL Bomber", sf::Style::Close)
{
    window.setFramerateLimit(60);

    pushScene(new MenuScene(*this));
}

void Application::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        if (getCurrentScene() == nullptr)
            continue;

        getCurrentScene()->handleEvents();
        getCurrentScene()->update(deltaTime);

        window.clear();
        getCurrentScene()->draw(deltaTime);
        window.display();

    }
}

void Application::pushScene(IScene *scene)
{
    m_scenes.push(scene);
}

void Application::popScene()
{
    delete m_scenes.top();
    m_scenes.pop();
}

void Application::changeCurrentScene(IScene *scene)
{
    if (!m_scenes.empty())
        popScene();

    pushScene(scene);
}

IScene *Application::getCurrentScene() const
{
    if (m_scenes.empty())
        return nullptr;

    return m_scenes.top();
}

void Application::loadTextures()
{
	textureManager.loadTexture(TextureType::Background, "media/background.png");
}
