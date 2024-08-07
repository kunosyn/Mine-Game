#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include <Managers/TextureManger.h>
#include <Managers/InputManager.h>
#include <Managers/TerrainManager.h>
#include <Managers/PlayerManager.h>
#include <Managers/UIManager.h>

#include <Classes/Player.h>


class Game {
public:
	Game(void);
	~Game(void);

	const bool running(void) const;

	void update(void);
	void render(void);

private:
	std::unique_ptr<sf::RenderWindow> m_window;

	InputManager m_inputManager;
	PlayerManager m_playerManager;

	TextureManager m_textureManager;
	TerrainManager m_terrainManager;
	UIManager m_uiManager;
	
	Player* m_basePlayer;


	float m_deltaTime;
	bool m_isPaused;

	sf::VideoMode m_videoMode;
	sf::Event m_event;
	sf::Vector2f m_worldSpawn;

	sf::Clock m_deltaClock;

	void debugUi(void);
};
