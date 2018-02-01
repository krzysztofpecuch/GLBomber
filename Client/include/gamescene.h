#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "iscene.h"
#include "player.h"

class GameScene : public IScene
{
public:
    GameScene(Application& application);
    ~GameScene();

    void draw(float deltaTime) override;
    void update(float deltaTime) override;
    void handleInput(sf::Keyboard::Key keyCode) override;

    void setMap(const std::vector<int> &map);

    void addPlayer(int id, const Player& player);
    void updatePlayer(int id, const sf::Vector2f& position);
    void removePlayer(int id);

private:
    std::vector<Tile> m_tiles;
    std::map<int, Player> m_players;
};

#endif // GAMESCENE_H
