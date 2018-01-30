#include "characterselectscene.h"
#include "gamescene.h"

const std::vector<std::string> stringOptions {"Enter nickname", "Choose skin"};

CharacterSelectScene::CharacterSelectScene(Application &application) :
    IScene(application),
    m_nicknameHolder("", m_app.getFont(FontType::Menu), 25)
{
    m_background.setTexture(m_app.textureManager.getRef(TextureType::MenuBackground));
    m_pointer.setTexture(m_app.textureManager.getRef(TextureType::TrianglePointer));

    for (unsigned i = 0; i < stringOptions.size(); ++i)
    {
        sf::Text text(stringOptions[i], m_app.getFont(FontType::Menu), 30);
        m_options.push_back(text);
    }

    m_options.front().setPosition(m_app.window.getSize().x / 2 - m_options.front().getLocalBounds().width / 2, 300);
    m_options.back().setPosition(m_app.window.getSize().x / 2 - m_options.back().getLocalBounds().width / 2, 400);

    m_nicknameHolder.setString("Player");
    m_nicknameHolder.setFillColor(sf::Color(227, 162, 6));
    m_nicknameHolder.setPosition(m_app.window.getSize().x / 2 - m_nicknameHolder.getGlobalBounds().width / 2,
                                 m_options.front().getPosition().y + m_options.front().getGlobalBounds().height + 30);

    const std::vector<TextureType> skinTypes {TextureType::Skin1, TextureType::Skin2, TextureType::Skin3, TextureType::Skin4};

    for (unsigned i = 0; i < skinTypes.size(); ++i)
    {
        sf::Sprite skinSprite(m_app.textureManager.getRef(skinTypes[i]));
        m_skins.push_back(skinSprite);
    }

    m_skins.front().setPosition(220, 427);

    for (unsigned i = 1; i < m_skins.size(); ++i)
    {
        m_skins[i].setPosition(m_skins[i-1].getGlobalBounds().left + m_skins[i-1].getGlobalBounds().width + 35, m_skins[i-1].getPosition().y);
    }

    m_pointer.setScale(0.7f, 0.7f);
    m_pointer.setPosition(m_skins.front().getPosition().x + m_skins.front().getGlobalBounds().width / 2 - m_pointer.getGlobalBounds().width / 2,
                          m_skins.front().getPosition().y + 10);
}


void CharacterSelectScene::draw(float deltaTime)
{
    m_app.window.draw(m_background);

    for (const auto& option : m_options)
    {
        m_app.window.draw(option);
    }

    m_app.window.draw(m_nicknameHolder);

    m_app.window.draw(m_pointer);

    for (const auto& skin : m_skins)
    {
        m_app.window.draw(skin);
    }
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

    case sf::Keyboard::Left:
    {
        if (m_currentOptionIndex == 0)
            return;

        if (m_disabledSkins.size() == 0)
        {
            m_currentOptionIndex--;
            break;
        }

        for (int i = m_currentOptionIndex - 1; i >= 0; --i)
        {
            bool found = false;

            if (std::find(m_disabledSkins.begin(), m_disabledSkins.end(), i) == m_disabledSkins.end())
            {
                m_currentOptionIndex = i;
                found = true;
                break;
            }

            if (found)
                break;
        }

        break;
    }

    case sf::Keyboard::Right:
    {
        if (m_currentOptionIndex == m_skins.size() - 1)
            return;

        if (m_disabledSkins.size() == 0)
        {
            m_currentOptionIndex++;
            break;
        }

        for (unsigned i = m_currentOptionIndex + 1; i < m_skins.size(); ++i)
        {
            bool found = false;

            if (std::find(m_disabledSkins.begin(), m_disabledSkins.end(), i) == m_disabledSkins.end())
            {
                m_currentOptionIndex = i;
                found = true;
                break;
            }

            if (found)
                break;
        }

        break;
    }

    case sf::Keyboard::Return:
    {
        sf::Packet packet;

        SharedData::Player data;
        data.nickname = m_nicknameHolder.getString().toAnsiString();
        data.skin = m_currentOptionIndex;

        packet << PacketType::PlayerInitialData << data;

        m_app.sendToServer(packet);

        m_app.changeCurrentScene(new GameScene(m_app));

        return;
    }

    default:
        break;

    }

    m_pointer.setPosition(m_skins[m_currentOptionIndex].getPosition().x + m_skins[m_currentOptionIndex].getGlobalBounds().width / 2 - m_pointer.getGlobalBounds().width / 2,
                          m_skins[m_currentOptionIndex].getPosition().y + 10);
}

void CharacterSelectScene::captureTextEntered(char character)
{
    std::string currentText = m_nicknameHolder.getString().toAnsiString();

    if (static_cast<int>(character) == 8) // backspace
    {
        if (currentText.size() < 1)
            return;

        currentText = currentText.substr(0, currentText.size() - 1);
    }
    else if (static_cast<int>(character) < 32) // control character
        return;

    else
    {
        if (m_nicknameHolder.getGlobalBounds().width > 350)
            return;

        currentText.append({character});
    }


    m_nicknameHolder.setString(currentText);
    m_nicknameHolder.setPosition(m_app.window.getSize().x / 2 - m_nicknameHolder.getGlobalBounds().width / 2, m_nicknameHolder.getPosition().y);
}

void CharacterSelectScene::updateSkins(const std::vector<int> &skins)
{
    m_disabledSkins = skins;
    std::sort(m_disabledSkins.begin(), m_disabledSkins.end());

    if (std::find(m_disabledSkins.begin(), m_disabledSkins.end(), m_currentOptionIndex) != m_disabledSkins.end())
    {
        for (unsigned i = 0; i < m_skins.size(); ++i)
        {
            bool found = false;

            if (std::find(m_disabledSkins.begin(), m_disabledSkins.end(), i) == m_disabledSkins.end())
            {
                m_currentOptionIndex = i;
                found = true;
                m_pointer.setPosition(m_skins[m_currentOptionIndex].getPosition().x + m_skins[m_currentOptionIndex].getGlobalBounds().width / 2 - m_pointer.getGlobalBounds().width / 2,
                                      m_skins[m_currentOptionIndex].getPosition().y + 10);
                break;
            }

            if (found)
                break;
        }
    }


    for (unsigned i = 0; i < m_skins.size(); ++i)
    {
        if (std::find(m_disabledSkins.begin(), m_disabledSkins.end(), i) != m_disabledSkins.end())
            m_skins[i].setTexture(m_app.textureManager.getRef(TextureType::SkinGray));

        else
            m_skins[i].setTexture(m_app.textureManager.getRef(TextureType::Skin1));
    }


}

void CharacterSelectScene::updateSkinsRequest()
{
    sf::Packet packet;
    packet << PacketType::UpdateSkins;
    m_app.sendToServer(packet);
}
