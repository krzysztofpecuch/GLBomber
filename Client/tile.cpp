#include "tile.h"

std::string tileTypeToStr(TileType type);
TextureType tileTypeToTexture(TileType type);

Tile::Tile() 
{ 

}

Tile::Tile(const unsigned int tileSize, const unsigned int height, sf::Texture& texture, const std::vector<Animation>& animations, 
	const TileType tileType)
{
	this->tileType = tileType;
	
	tileVariant = 0;
	regions[0] = 0;

	sprite.setOrigin(sf::Vector2f(0.0f, tileSize*(height - 1)));
	sprite.setTexture(texture);
	animationHandler.frameSize = sf::IntRect(0, 0, tileSize * 2, tileSize*height);
	
	for (auto animation : animations)
	{
		animationHandler.addAnimation(animation);
	}
	
	this->animationHandler.update(0.0f);
}

void const Tile::draw(sf::RenderWindow &window, float dt) {
	animationHandler.changeAnimation(tileVariant);

	animationHandler.update(dt);

	sprite.setTextureRect(animationHandler.bounds);

	window.draw(sprite);
}

void Tile::update() {

}

TextureType Tile::tileToTexture(TileType type)
{
	switch (type) {
	default:
		break;
	case TileType::EmptyTile:
		return TextureType::EmptyTile;
	case TileType::SoftTile:
		return TextureType::SoftTile;
	case TileType::SolidTile:
		return TextureType::SolidTile;
	}
}
