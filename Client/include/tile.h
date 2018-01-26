#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "animationhandler.h"
#include "texturemanager.h"

class Tile
{
public:
	Tile();
    Tile(const unsigned int height, TextureManager& textureManager, const std::vector<Animation>& animations, TileType type);

	AnimationHandler animationHandler;
	sf::Sprite sprite;
	TileType tileType;

	void setTileVariant(int tileVariant);
	void draw(sf::RenderWindow &window, float dt);
	void update();
	TextureType tileToTexture(TileType type);


private:
	int m_tileVariant;
	TextureManager *m_textureManager;
};


#endif // !TILE_H
