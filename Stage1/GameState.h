#pragma once
#include "sgg/graphics.h"
#include <stdio.h>
#include<string>
#include "util.h"
#include "Menu.h"

class GameState {
private:

	std::string m_asset_path = "assets\\";
	float m_canvas_width = 10.0f;
	float m_canvas_height = 6.0f;

	static  GameState* m_unique_instance;
	GameState();
	class Player* m_player = 0;
	class Level* m_current_level = 0;
	class Menu* m_menu = nullptr; 
	bool m_in_menu = true; 
public:

	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	bool m_debugging = false;
	void init();
	void draw();
	void update(float dt);


	static GameState* getInstance();
	~GameState();
	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);
	class Player* getPlayer() {
		return m_player;
	}
};
