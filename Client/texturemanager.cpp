#include "texturemanager.h"

TextureManager::TextureManager()
{

}

void TextureManager::loadTexture(const TextureType & type, const std::string & filename)
{
	std::cout << "Loading " + filename << std::endl;

	sf::Texture texture;
	texture.loadFromFile(filename);
	this->textures[type] = texture;
}

sf::Texture & TextureManager::getRef(const TextureType & texture)
{
	return this->textures.at(texture);
}

