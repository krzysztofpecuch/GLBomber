#include "tile.h"

Tile::Tile() 
{

}

Tile::Tile(const unsigned int height, TextureManager& textureManager, const std::vector<Animation>& animations, 
	TileType type)
{
	//TODO pozniej byc moze private
	tileType = type;
	m_textureManager = &textureManager;

	m_tileVariant = 0;
	
	sprite.setOrigin(sf::Vector2f(0.0f, tileSize*(height - 1)));
	sprite.setTexture(textureManager.getRef(tileToTexture(tileType)));

	animationHandler.frameSize = sf::IntRect(0, 0, tileSize, tileSize*height);
	
	for (auto animation : animations)
	{
		animationHandler.addAnimation(animation);
	}
	
	this->animationHandler.update(0.0f);
}

void Tile::setTileVariant(int tileVariant)
{
	m_tileVariant = tileVariant;
}

void Tile::draw(sf::RenderWindow &window, float dt)
{
	animationHandler.changeAnimation(m_tileVariant);
	animationHandler.update(dt);

	sprite.setTextureRect(animationHandler.bounds);

	window.draw(sprite);

	if (animationHandler.animationEnded()) 
	{
		if (tileType == TileType::SoftTile) 
		{
            tileType = TileType::EmptyTile;
			sprite.setTexture(m_textureManager->getRef(tileToTexture(tileType)));
			animationHandler.addAnimation(Animation(0, 0, 1.f));
		}
	}
}

void Tile::update() {

}

TextureType Tile::tileToTexture(TileType type)
{
    switch (type)
    {
	default:
        return TextureType::Error;
	case TileType::EmptyTile:
		return TextureType::EmptyTile;
	case TileType::SoftTile:
		return TextureType::SoftTile;
	case TileType::SolidTile:
		return TextureType::SolidTile;
	}
}
