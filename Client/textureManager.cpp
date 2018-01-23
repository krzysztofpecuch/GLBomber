#include "textureManager.h"

//enumclass dodasifgdaojigfdofdgklsdajgfdlk

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::loadTexture(const TextureType & type, const std::string & filename)
{
	sf::Texture texture;
	texture.loadFromFile(filename);
	this->textures[type] = texture;
}

sf::Texture & TextureManager::getRef(const TextureType & texture)
{
	return this->textures.at(texture);
}

