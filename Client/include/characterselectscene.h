#ifndef CHARACTERSELECTSCENE_H
#define CHARACTERSELECTSCENE_H

#include "menuscene.h"

class CharacterSelectScene : public MenuScene
{
public:
    CharacterSelectScene(Application& application);

    void draw(float deltaTime) override;
    void update(float deltaTime) override;
    void handleInput(sf::Keyboard::Key keyCode) override;

protected:
    void setupOptions() override;
};

#endif // CHARACTERSELECTSCENE_H
