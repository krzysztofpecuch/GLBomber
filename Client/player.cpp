#include "player.h"

Player::Player(const sf::Texture &texture, const std::string &nickname, const sf::Vector2f &position) :
    m_strNickname(nickname),
    m_position(position)
{
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(0, m_sprite.getLocalBounds().height - TILE_SIZE);
    m_sprite.setPosition(m_position);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    target.draw(m_sprite);
}

