#include "Headers/Game.h"
#include "Headers/Constants.h"

#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui-SFML_export.h>

#include <iostream>

Game::Game (void) {
	initializeWindow();

	m_playerManager = std::make_unique<PlayerManager>();

	m_playerManager->addPlayer(0);
	m_basePlayer = m_playerManager->getPlayer(0);

	m_inputManager = std::make_unique<InputManager>(m_window.get(), m_basePlayer);
	ImGui::SFML::Init(*m_window.get());

	m_terrainGenerator = std::make_unique<TerrainGenerator>(m_window.get());
	m_terrainGenerator->generateTerrain(m_basePlayer->m_position, m_basePlayer->getViewBounds());
}

Game::~Game (void) {
	ImGui::SFML::Shutdown();
}

// Public Functions
const bool Game::running (void) const {
	return m_window->isOpen();
}

void Game::update (void) {
	m_inputManager->continuousInputChecks();

	while (m_window->pollEvent(m_event)) {
		ImGui::SFML::ProcessEvent(*m_window.get(), m_event);

		if (m_event.type == sf::Event::Closed)
			m_window->close();
		else
			m_inputManager->handleInput(m_event);
	}

	m_basePlayer->applyPhysics();

	if (m_basePlayer->isMoving()) {
		std::cout << "moving" << std::endl;
		m_terrainGenerator->generateTerrain(m_basePlayer->m_position, m_basePlayer->getViewBounds());
	}
}

void Game::render (void) {
	m_window->clear(sf::Color::Color(143, 224, 242));
	m_terrainGenerator->renderTerrain();

	m_playerManager->drawPlayers(m_window.get());

	ImGui::SFML::Update(*m_window.get(), m_deltaClock.restart());
	debugUi();
	ImGui::SFML::Render(*m_window.get());

	m_window->display();
}

// Private Functions
void Game::initializeWindow (void) {
	m_videoMode.height = 600;
	m_videoMode.width = 800;

	m_window = std::make_unique<sf::RenderWindow>(
		m_videoMode,
		"MineGame",
		sf::Style::Default
	);

	m_window->setFramerateLimit(60);
}

void Game::debugUi (void) { }
