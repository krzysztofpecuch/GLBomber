#include "menuscene.h"

const std::vector<std::string> stringOptions {"Play", "Exit"};

MenuScene::MenuScene(Application &application) :
    IScene(application)
{
    m_background.setTexture(m_app.textureManager.getRef(TextureType::MenuBackground));

    for (unsigned i = 0; i < stringOptions.size(); ++i)
    {
        sf::Text text(stringOptions[i], m_app.getFont(FontType::Menu), 70);
        m_options.push_back(text);
    }

    m_options.front().setPosition(m_app.window.getSize().x / 2 - m_options.front().getLocalBounds().width / 2,
                                  m_app.window.getSize().y / 2 - m_options.front().getLocalBounds().height / 2 - 35);

    m_options.back().setPosition(m_app.window.getSize().x / 2 - m_options.back().getLocalBounds().width / 2,
                                  m_options.front().getGlobalBounds().top + m_options.front().getGlobalBounds().height + 10);

}


void MenuScene::draw(float deltaTime)
{
    m_app.window.draw(m_background);

    for (const auto& option : m_options)
    {
        m_app.window.draw(option);
    }
}

void MenuScene::update(float deltaTime)
{

}

void MenuScene::handleInput(sf::Keyboard::Key keyCode)
{

}
