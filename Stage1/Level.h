#pragma once
#include "gameobject.h"  
#include "box.h"       
#include <vector>
#include <list>
#include "Player.h"
#include "gamestate.h"

class Level :public GameObject,public Box
{

	graphics::Brush m_brush_background;
	graphics::Brush m_brush_text;

	std::vector<GameObject*> m_static_objects;
	std::list <GameObject*> m_dynamic_objects;

	std::vector<Box> m_blocks;
	std::vector<std::string> m_block_names;
	
	std::vector<Box> m_spikes;
	std::vector<std::string> m_spike_names;

	std::vector<Box> m_coins;
	std::vector<std::string> m_coin_names;

	std::vector<Box> m_flag;
	std::vector<std::string> m_flag_names;

	const float m_block_size = 1.0f;
	const float m_spike_size = 0.8f;
	const float m_coin_size = 1.0f;
	const float m_flag_size = 1.0f;

	graphics::Brush m_block_brush;
	graphics::Brush m_spike_brush;
	graphics::Brush m_brush_coin;
	graphics::Brush m_flag_brush;

	graphics::Brush m_block_brush_debug;
	graphics::Brush m_spike_brush_debug;
	graphics::Brush m_coin_brush_debug;
	graphics::Brush m_flag_brush_debug;

	int coin_score = 0;
	int life_score = 100;
	bool finish = false;
	float m_senter_x = 5.0f;
	float m_center_y = 5.0f;


	void drawBlock(int i);
	void drawSpikes(int i);
	void drawCoin(int i);
	void drawFlag(int i);
	void checkCollisions();
	void checkSpikeCollisions();
	void checkCoinCollisions();
	void checkFlagCollisions();
	


		
public:
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;

	Level(const std::string& name = "Level0");
	~Level();

};