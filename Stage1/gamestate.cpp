#include "GameState.h"
#include "level.h";
#include"player.h"
#include <thread>
#include <chrono>
#include"Menu.h"

GameState::GameState()
{
}

void GameState::init()
{
	if (m_in_menu) {
		m_menu = new Menu();
		m_menu->init();
	}
	else {
		m_current_level = new Level();
		m_current_level->init();

		m_player = new Player("ninja");
		m_player->init();
	}

	graphics::preloadBitmaps(getAssetDir());
}


void GameState::draw()
{
	if (m_in_menu) {
		m_menu->draw();
	}
	else {
		if (!m_current_level) return;
		m_current_level->draw();
	}
}


void GameState::update(float dt)
{
	if (dt > 500)
		return;

	float sleep_time = std::max(0.0f, 17.0f - dt);
	std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));

	if (m_in_menu) {
		m_menu->update(dt);

		
		if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
			m_in_menu = false; 
			delete m_menu; 
			m_menu = nullptr;

			m_current_level = new Level();
			m_current_level->init();

			m_player = new Player("ninja");
			m_player->init();
		}
	}
	else {
		if (!m_current_level)
			return;

		m_current_level->update(dt);
		m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
	}
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr) {
		m_unique_instance = new GameState();
		
	}
	return m_unique_instance;
}

GameState::~GameState()
{
	if (m_player) delete m_player;
	if (m_current_level) delete m_current_level;
	if (m_menu) delete m_menu; 
}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath( const std::string& asset)
{

	std::string mystring = getAssetDir() + asset;

	return mystring;
}
GameState* GameState::m_unique_instance = nullptr;