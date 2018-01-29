#ifndef CHARACTERSELECTSCENE_H
#define CHARACTERSELECTSCENE_H

#include "iscene.h"

class CharacterSelectScene : public IScene
{
public:
    CharacterSelectScene(Application& application);

    void draw(float deltaTime) override;
    void update(float deltaTime) override;
    void handleInput(sf::Keyboard::Key keyCode) override;

    void captureTextEntered(char character);

    void updateSkins(const std::vector<int>& skins);

    void updateSkinsRequest();

private:
    std::vector<sf::Text> m_options;
    sf::Text m_nicknameHolder;
    sf::Sprite m_background;

    sf::Sprite m_pointer;
    std::vector<sf::Sprite> m_skins;
    std::vector<int> m_disabledSkins;

    unsigned m_currentOptionIndex = 0;
};

#endif // CHARACTERSELECTSCENE_H
