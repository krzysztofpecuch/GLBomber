#include "application.h"
#include "iscene.h"
#include "menuscene.h"
#include "texturemanager.h"

Application::Application() :
    window(sf::VideoMode(800, 800), "GL Bomber", sf::Style::Close)
{
    window.setFramerateLimit(60);

    loadTextures();
    loadFonts();

    pushScene(new MenuScene(*this));
}

Application::~Application()
{
    while (!m_scenes.empty())
        popScene();
}

void Application::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        if (getCurrentScene() == nullptr)
            continue;

        handleEvents();

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
//    m_scenes.top() = nullptr;
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

const sf::Font &Application::getFont(FontType type)
{
    return m_fonts[type];
}

void Application::loadTextures()
{
	textureManager.loadTexture(TextureType::Background, "media/background.png");
	textureManager.loadTexture(TextureType::SolidTile, "media/solidTile.png");
	textureManager.loadTexture(TextureType::SoftTile, "media/softTile.png");
	textureManager.loadTexture(TextureType::EmptyTile, "media/emptyTile.png");
    textureManager.loadTexture(TextureType::MenuBackground, "media/menu_background.png");
    textureManager.loadTexture(TextureType::BombPointer, "media/bombpointer.png");
}

void Application::loadFonts()
{
    sf::Font font;
    font.loadFromFile("fonts/main.ttf");
    m_fonts[FontType::Menu] = font;
}

void Application::handleEvents()
{
    while (window.pollEvent(m_event))
    {
        switch (m_event.type)
        {

        case sf::Event::Closed:
        {
            window.close();
            break;
        }

        case sf::Event::KeyPressed:
        {
            getCurrentScene()->handleInput(m_event.key.code);
            break;
        }

        default:
            break;

        }
    }
}
