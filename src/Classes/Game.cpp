#include "../Headers/Classes/Game.h"
#include "../Headers/Constants.h"

#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui-SFML_export.h>

#include <iostream>
#include <thread>

Game::Game (void)
	: m_isPaused(false), m_event(),

	m_window(std::make_unique<sf::RenderWindow>(
		sf::VideoMode::getDesktopMode(),
		"Mine Game",
		sf::Style::Fullscreen
	)),

	m_playerManager(m_deltaTime),
	m_terrainManager(m_window.get()),
	m_inputManager(m_window.get(), m_basePlayer, m_isPaused),
	m_uiManager()
{
	m_window->setFramerateLimit(60);
	m_deltaTime = m_deltaClock.restart().asSeconds();


	m_playerManager.addPlayer(0);
	m_basePlayer = m_playerManager.getPlayer(0);
	
	ImGui::SFML::Init(*m_window.get());

	m_terrainManager.generateTerrain(
		m_basePlayer->m_position, 
		m_basePlayer->getViewBounds()
	);
}

Game::~Game (void) {
	ImGui::SFML::Shutdown();
}

// Public Functions
const bool Game::running (void) const {
	return m_window->isOpen();
}

void Game::update (void) {
	if (m_isPaused) return;

	while (m_window->pollEvent(m_event)) {
		ImGui::SFML::ProcessEvent(*m_window.get(), m_event);

		if (m_event.type == sf::Event::Closed)
			m_window->close();
		else
			m_inputManager.handleInput(m_event);
	}

	m_inputManager.update();
	m_basePlayer->applyPhysics();

	if (m_basePlayer->eligibleForGeneration()) {
		m_terrainManager.generateTerrain(
			m_basePlayer->m_position,
			m_basePlayer->getViewBounds()
		);
	}

	m_deltaTime = m_deltaClock.restart().asSeconds();
}

void Game::render (void) {
	m_window->clear(sf::Color::Color(171, 200, 245));
	m_window->setView(m_basePlayer->m_view);

	m_terrainManager.renderTerrain(m_basePlayer->getViewBounds());
	m_playerManager.drawPlayers(m_window.get());
	m_uiManager.drawUI(m_window.get());

	m_window->display();
}


void Game::debugUi (void) { }
