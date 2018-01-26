#include "application.h"
#include "iscene.h"
#include "menuscene.h"
#include "characterselectscene.h"
#include "texturemanager.h"

Application::Application() :
    window(sf::VideoMode(800, 800), "GL Bomber", sf::Style::Close),
    m_socket(*this)
{
    window.setFramerateLimit(60);

    loadTextures();
	loadTiles();
    loadFonts();
	

    pushScene(new MenuScene(*this));
}

Application::~Application()
{
    while (!m_scenes.empty())
        popScene();
}

void Application::loadTextures()
{
	textureManager.loadTexture(TextureType::Background, "media/background.png");
	textureManager.loadTexture(TextureType::SolidTile, "media/solidTile.png");
	//textureManager.loadTexture(TextureType::SoftTile, "media/softTile.png");
	textureManager.loadTexture(TextureType::EmptyTile, "media/emptyTile.png");
	textureManager.loadTexture(TextureType::MenuBackground, "media/menu_background.png");
	textureManager.loadTexture(TextureType::BombPointer, "media/bomb_pointer.png");
	textureManager.loadTexture(TextureType::TrianglePointer, "media/triangle_pointer.png");
	textureManager.loadTexture(TextureType::Skin1, "media/skin1.png");
	textureManager.loadTexture(TextureType::Skin2, "media/skin1.png");
	textureManager.loadTexture(TextureType::Skin3, "media/skin1.png");
	textureManager.loadTexture(TextureType::Skin4, "media/skin1.png");
	textureManager.loadTexture(TextureType::SoftTile, "media/softTile2.png");
	textureManager.loadTexture(TextureType::SkinGray, "media/skin_gray.png");
}

void Application::loadTiles()
{
	//tileAtlas["test"] = Tile(tileSize, 1, textureManager.getRef(TextureType::EmptyTile), { Animation(0, 0, 1.f) }, TileType::EmptyTile);
	tileAtlas[TileType::SoftTile] = Tile(1, textureManager, { Animation(0, 4, 0.5f), Animation(0, 4, 0.5f), Animation(0, 4, 0.5f) }, TileType::SoftTile);
	tileAtlas[TileType::EmptyTile] = Tile(1, textureManager, { Animation(0, 0, 1.f) }, TileType::EmptyTile);
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

void Application::sendToServer(sf::Packet &packet)
{
    m_socket.send(packet);
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

        case sf::Event::TextEntered:
        {
            CharacterSelectScene* scene = dynamic_cast<CharacterSelectScene*>(getCurrentScene());
            if (!scene)
                break;

            scene->captureTextEntered(m_event.text.unicode);
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
