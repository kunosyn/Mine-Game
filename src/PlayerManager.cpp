#include "Headers/PlayerManager.h"
#include <random>

PlayerManager::PlayerManager (void) {

}

void PlayerManager::createPlayer (void) {
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());

	std::uniform_int_distribution<int> distributed(1, 10000000);
	int id = distributed(generator);

	addPlayer(id);
}

void PlayerManager::addPlayer (int id) {
	std::unique_ptr<Player> player = std::make_unique<Player>(id);
	m_players[id] = std::move(player);
}

void PlayerManager::removePlayer(int id) {
	m_players.erase(id);
}

Player* PlayerManager::getPlayer (int id) {
	auto it = m_players.find(id);

	if (it != m_players.end()) {
		return it->second.get();
	}

	return nullptr;
}


void PlayerManager::drawPlayers (sf::RenderWindow* render_window) {
	for (auto it = m_players.begin(); it != m_players.end(); ++it) {
		it->second->draw(render_window);
	}
}
