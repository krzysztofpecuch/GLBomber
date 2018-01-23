#ifndef APPLICATION_H
#define APPLICATION_H

#include "textureManager.h"

#include <SFML/Graphics.hpp>

#include <stack>
#include <map>

enum class FontType
{
    Menu
};

class IScene;

class Application
{
public:
    Application();

    sf::RenderWindow window;
	TextureManager textureManager;

    void run();

    void pushScene(IScene* scene);
    void popScene();
    void changeCurrentScene(IScene* scene);
    IScene* getCurrentScene() const;

    const sf::Font& getFont(FontType type);

private:
    std::stack<IScene*> m_scenes;
    std::map<FontType, sf::Font> m_fonts;

	void loadTextures();
    void loadFonts();
};

#endif // APPLICATION_H
