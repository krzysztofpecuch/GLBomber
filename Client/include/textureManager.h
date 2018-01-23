#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "common.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void loadTexture(const TextureType &type, const std::string &filename);
	sf::Texture& getRef(const TextureType &type);

private:
	std::map<TextureType, sf::Texture> textures;
};

#endif // !TEXTUREMANAGER_HPP