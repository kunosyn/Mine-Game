#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Headers/InputManager.h"
#include "Headers/TerrainGenerator.h"
#include "Headers/PlayerManager.h"
#include "Headers/Player.h"


class Game {
public:
	Game(void);
	~Game(void);

	const bool running(void) const;

	void update(void);
	void render(void);

private:
	std::unique_ptr<sf::RenderWindow> m_window;
	std::unique_ptr<InputManager> m_inputManager;
	std::unique_ptr<TerrainGenerator> m_terrainGenerator;
	std::unique_ptr<PlayerManager> m_playerManager;


	sf::VideoMode m_videoMode;
	sf::Event m_event;
	sf::Vector2f m_worldSpawn;

	Player* m_basePlayer;
	void initializeWindow(void);
	void debugUi(void);

	sf::Clock m_deltaClock;
	float m_debugTerrainFrequency, m_debugTerrainHeight, m_debugTerrainMultiplier;
};
