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
    Tile(const unsigned int tileSize, const unsigned int height, sf::Texture& texture, const std::vector<Animation>& animations,
        const TileType tileType);

	AnimationHandler animationHandler;
	sf::Sprite sprite;
	TileType tileType;

	/* Tile variant, allowing for different looking versions of the
	* same tile */
	int tileVariant;

	/* Region IDs of the tile, tiles in the same region are connected.
	* First is for transport */
	unsigned int regions[1];


    void draw(sf::RenderWindow &window, float dt);
	void update();
	TextureType tileToTexture(TileType type);
};


#endif // !TILE_H
