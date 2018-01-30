#include "gamescene.h"
#include "menuscene.h"

GameScene::GameScene(Application &application) :
	IScene(application)
{
//    sf::Packet packet;
//    packet << PacketType::GetMap;
//    m_app.sendToServer(packet);

//    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++)
//	{
//        if (i < MAP_WIDTH)
//            tiles.push_back(m_app.tileAtlas.at(TileType::SolidTile));

//        else if (i % MAP_HEIGHT == 0 || i % MAP_HEIGHT == MAP_HEIGHT - 1)
//            tiles.push_back(m_app.tileAtlas.at(TileType::SolidTile));

//        else if (i > MAP_WIDTH * (MAP_HEIGHT-1))
//            tiles.push_back(m_app.tileAtlas.at(TileType::SolidTile));

//		else
//			tiles.push_back(m_app.tileAtlas.at(TileType::EmptyTile));
//    }
}

GameScene::~GameScene()
{
    sf::Packet packet;
    packet << PacketType::PlayerLeftGame;
    m_app.sendToServer(packet);
}

void GameScene::draw(float deltaTime)
{
    if (tiles.empty())
        return;

    for (int y = 0; y < MAP_HEIGHT; y++)
	{
        for (int x = 0; x < MAP_WIDTH; x++)
		{
			sf::Vector2f pos;
            pos.x = x * tileSize;
            pos.y = y * tileSize;

            tiles[y * MAP_WIDTH + x].sprite.setPosition(pos);
            tiles[y * MAP_WIDTH + x].draw(m_app.window, deltaTime);
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

void GameScene::setMap(const std::vector<int> &map)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            tiles.push_back(m_app.tileAtlas.at(static_cast<TileType::Type>(map[y * MAP_WIDTH + x])));
        }
    }
}
