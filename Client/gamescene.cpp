#include "gamescene.h"
#include "menuscene.h"

GameScene::GameScene(Application &application) :
	IScene(application)
{
	m_background.setTexture(m_app.textureManager.getRef(TextureType::MenuBackground));
	width = 11;
	height = 11;
	for (int i = 0; i < width * height; i++)
	{
		if (i < width)
			tiles.push_back(m_app.tileAtlas.at(TileType::SoftTile));
		else if (i%height == 0 || i%height == height-1)
			tiles.push_back(m_app.tileAtlas.at(TileType::SoftTile));
		else if (i > width * (height-1))
			tiles.push_back(m_app.tileAtlas.at(TileType::SoftTile));
		else
			tiles.push_back(m_app.tileAtlas.at(TileType::EmptyTile));
    }
}

GameScene::~GameScene()
{
    m_app.disconnectFromServer();
}


void GameScene::draw(float deltaTime)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			sf::Vector2f pos;
			pos.x = x * 64;
			pos.y = y * 64;
			tiles[y*width + x].sprite.setPosition(pos);
			
			tiles[y*width + x].draw(m_app.window, deltaTime);
		}
	}
}

void GameScene::update(float deltaTime)
{
	
}

void GameScene::handleInput(sf::Keyboard::Key keyCode)
{
    switch (keyCode)
    {
        case sf::Keyboard::Escape:
    {
        m_app.popScene();
    }

    default:
        break;
    }
}
