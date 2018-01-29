#include "menuscene.h"
#include "characterselectscene.h"
#include "gamescene.h"

const std::vector<std::string> stringOptions {"Play", "Exit"};

MenuScene::MenuScene(Application &application) :
    IScene(application)
{
    m_background.setTexture(m_app.textureManager.getRef(TextureType::MenuBackground));
    m_bombPointer.setTexture(m_app.textureManager.getRef(TextureType::BombPointer));

    for (unsigned i = 0; i < stringOptions.size(); ++i)
    {
        sf::Text text(stringOptions[i], m_app.getFont(FontType::Menu), 70);
        m_options.push_back(text);
    }

    m_options.front().setPosition(m_app.window.getSize().x / 2 - m_options.front().getLocalBounds().width / 2,
                                  m_app.window.getSize().y / 2 - m_options.front().getLocalBounds().height / 2 - 35);

    m_options.back().setPosition(m_app.window.getSize().x / 2 - m_options.back().getLocalBounds().width / 2,
                                 m_options.front().getGlobalBounds().top + m_options.front().getGlobalBounds().height + 10);

    m_bombPointer.setPosition(m_options.front().getGlobalBounds().left - m_bombPointer.getLocalBounds().width - 10,
                              m_options.front().getGlobalBounds().top + m_options.front().getGlobalBounds().height / 2 - m_bombPointer.getLocalBounds().height / 2);
}


void MenuScene::draw(float deltaTime)
{
    m_app.window.draw(m_background);

    for (const auto& option : m_options)
    {
        m_app.window.draw(option);
    }

    m_app.window.draw(m_bombPointer);
}

void MenuScene::update(float deltaTime)
{

}

void MenuScene::handleInput(sf::Keyboard::Key keyCode)
{
    switch (keyCode)
    {

    case sf::Keyboard::Escape:
        m_app.window.close();

    case sf::Keyboard::Up:
    {

        if (m_currentOptionIndex == 0)
            m_currentOptionIndex = m_options.size() - 1;

        else
            m_currentOptionIndex--;
        break;
    }

    case sf::Keyboard::Down:
    {
        if (m_currentOptionIndex == m_options.size() - 1)
            m_currentOptionIndex = 0;

        else
            m_currentOptionIndex++;
        break;
    }

    case sf::Keyboard::Return:
    {
        switch (m_currentOptionIndex)
        {
        case 0:
        {
            m_app.pushScene(new CharacterSelectScene(m_app));

            CharacterSelectScene* scene = dynamic_cast<CharacterSelectScene*>(m_app.getCurrentScene());
            if (!scene)
                break;

            scene->updateSkinsRequest();
        }
        break;

        case 1:
            m_app.window.close();
            break;

        default:
            break;
        }
    }

    default:
        break;
    }

    m_bombPointer.setPosition(m_options[m_currentOptionIndex].getGlobalBounds().left - m_bombPointer.getLocalBounds().width - 10,
                              m_options[m_currentOptionIndex].getGlobalBounds().top + m_options[m_currentOptionIndex].getGlobalBounds().height / 2
                              - m_bombPointer.getLocalBounds().height / 2);
}
