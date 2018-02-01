#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "common.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <map>
#include <string>

enum class TextureType
{
    Background,
    SolidTile,
    SoftTile,
    EmptyTile,
	TestTile,
    MenuBackground,
    BombPointer,
    TrianglePointer,
    Skin1,
    Skin2,
    Skin3,
    Skin4,
    SkinGray,
    Player1,
    Error
};

class TextureManager
{
public:
	TextureManager();

    const std::map<int, TextureType> skinToTexture
    {
        { SkinType::Skin1, TextureType::Player1 },
        { SkinType::Skin2, TextureType::Player1 },
        { SkinType::Skin3, TextureType::Player1 },
        { SkinType::Skin4, TextureType::Player1 },
    };

	void loadTexture(const TextureType &type, const std::string &filename);
	sf::Texture& getRef(const TextureType &type);

private:
	std::map<TextureType, sf::Texture> textures;
};

#endif // !TEXTUREMANAGER_HPP
