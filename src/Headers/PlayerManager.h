#pragma once

#include "Player.h"

#include <memory>
#include <unordered_map>


class PlayerManager {
public:
	PlayerManager(void);

	void createPlayer(void);
	void addPlayer(int id);
	void removePlayer(int id);
	void drawPlayers(sf::RenderWindow* renderWindow);

	Player* getPlayer(int id);
private:
	std::unordered_map<int, std::unique_ptr<Player>> m_players;
};

