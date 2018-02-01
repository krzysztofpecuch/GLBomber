#include "gamescene.h"
#include "menuscene.h"

GameScene::GameScene(Application &application) :
    IScene(application)
{
    sf::Packet packet;
    packet << PacketType::GetMap;
    m_app.sendToServer(packet);

    packet.clear();
    packet << PacketType::GetPlayers;
    m_app.sendToServer(packet);

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
    if (m_tiles.empty())
        return;

    for (auto& tile : m_tiles)
    {
        tile.draw(m_app.window, deltaTime);
    }

    for (auto& player : m_players)
    {
        m_app.window.draw(player.second);
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

        break;
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
            m_tiles.push_back(m_app.tileAtlas.at(static_cast<TileType::Type>(map[y * MAP_WIDTH + x])));

            sf::Vector2f pos;
            pos.x = x * TILE_SIZE;
            pos.y = y * TILE_SIZE;

            m_tiles[y * MAP_WIDTH + x].sprite.setPosition(pos);
        }
    }
}

void GameScene::addPlayer(int id, const Player &player)
{
    m_players.insert(std::pair<int, Player>(id, player));
}

void GameScene::updatePlayer(int id, const sf::Vector2f &position)
{

}
