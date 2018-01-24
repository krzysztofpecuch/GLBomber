#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "iscene.h"

#include <vector>


class MenuScene : public IScene
{
public:
    MenuScene(Application& application);

    void draw(float deltaTime) override;
    void update(float deltaTime) override;
    void handleInput(sf::Keyboard::Key keyCode) override;


private:
    std::vector<sf::Text> m_options;
    sf::Sprite m_background;
    sf::Sprite m_bombPointer;

    unsigned m_currentOptionIndex = 0;
};

#endif // MENUSCENE_H
