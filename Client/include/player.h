#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "common.h"

class Player : public sf::Drawable, public sf::Transformable
{
public:
    Player(const sf::Texture &texture = {}, const std::string& nickname = {}, const sf::Vector2f& position = {});

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates) const override;

private:
    std::string m_strNickname = "";
    sf::Vector2f m_position = {};

    sf::Sprite m_sprite;
};

#endif // PLAYER_H
