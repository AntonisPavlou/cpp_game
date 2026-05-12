#include"level.h"
#include "GameState.h"
#include"Player.h"
#include"util.h"
#include"box.h"

void Level::drawBlock(int i)
{
	Box& box = m_blocks[i];
	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	m_block_brush.texture = m_state->getFullAssetPath(m_block_names[i]);

	graphics::drawRect(x, y , m_block_size,m_block_size,m_block_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);
}

void Level::drawFlag(int i)
{
	Box& box = m_flag[i];
	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	m_flag_brush.texture = m_state->getFullAssetPath(m_flag_names[i]);

	graphics::drawRect(x, y, m_flag_size, m_flag_size, m_flag_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_flag_size, m_flag_size, m_flag_brush_debug);
}
void Level::drawSpikes(int i)
{
	Box& box = m_spikes[i];
	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	m_spike_brush.texture = m_state->getFullAssetPath(m_spike_names[i]);

	graphics::drawRect(x, y, m_spike_size, m_spike_size, m_spike_brush);

	if (m_state->m_debugging)
		graphics::drawRect(x, y, m_spike_size, m_spike_size, m_spike_brush_debug);
}


void Level::drawCoin(int i)
{
	Box& box = m_coins[i];
	float x = box.m_pos_x + m_state->m_global_offset_x;
	float y = box.m_pos_y + m_state->m_global_offset_y;
	m_brush_coin.texture = m_state->getFullAssetPath(m_coin_names[i]);

	graphics::drawRect(x, y, m_coin_size, m_coin_size, m_brush_coin);

	if (m_state->m_debugging)
		graphics::drawRect(x, y,0.5f* m_coin_size, 0.5*m_coin_size, m_coin_brush_debug);
}


void Level::checkCollisions() {
	
	for (auto& box : m_blocks) 
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectDown(box))
		{
			m_state->getPlayer()->m_pos_y += offset;

			if (m_state->getPlayer()->m_vy > 1.0f)
				graphics::playSound(m_state->getFullAssetPath("landing-sound.wav"), 0.5f);

			m_state->getPlayer()->m_vy = 0.0f;

			break;
		}
	}
	


	for (auto& box : m_blocks) {
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(box))
		{
			m_state->getPlayer()->m_pos_x += offset;
			m_state->getPlayer()->m_vx = 0.0f;
			break;
		}
	}
}


void Level::checkFlagCollisions() {

	for (auto& box : m_flag)
	{
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersect(box))
		{
			finish = true;
		}
	}



	for (auto& box : m_blocks) {
		float offset = 0.0f;
		if (offset = m_state->getPlayer()->intersectSideways(box))
		{
			m_state->getPlayer()->m_pos_x += offset;
			m_state->getPlayer()->m_vx = 0.0f;
			break;
		}
	}
}


void Level::checkCoinCollisions() {
	
	for (auto it = m_coins.begin(); it != m_coins.end(); ) {
		Box& coin = *it;  

		float offset = m_state->getPlayer()->intersect(coin); 

		if (offset != 0.0f) {  
			
			graphics::playSound(m_state->getFullAssetPath("coin.wav"), 0.5f);
			coin_score++;
			
			it = m_coins.erase(it);  
		}
		else {
			++it;  
			
		}
	}
}

void Level::checkSpikeCollisions() {
	for (auto it = m_spikes.begin(); it != m_spikes.end(); ) {
		Box& spike = *it;

		float offset = m_state->getPlayer()->intersect(spike);

		if (offset != 0.0f) {

			if (graphics::getKeyState(graphics::SCANCODE_D)) {
				m_state->getPlayer()->m_pos_x -= offset;
				m_state->getPlayer()->m_vx = 0.0f;
			}
			else if (graphics::getKeyState(graphics::SCANCODE_A)) {
				m_state->getPlayer()->m_pos_x += offset;
				m_state->getPlayer()->m_vx = 0.0f;
			}
			else {
				m_state->getPlayer()->m_pos_x += offset + 1;
				m_state->getPlayer()->m_vx = 0.0f;
			}

			graphics::playSound(m_state->getFullAssetPath("damage.wav"), 0.5f);

			life_score -= 25;

		break;
		}
		else {
			++it;
		}
	}
}

	
void Level::update(float dt)
{

	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->update(dt);

		checkCollisions();
		checkSpikeCollisions();
		checkCoinCollisions();
		checkFlagCollisions();
		
		if (finish || life_score <= 0) {
			graphics::stopMusic();
		}
	}
	GameObject::update(200);

}

void Level::init()
{
	graphics::playMusic(m_state->getFullAssetPath("background-music.wav"), 0.4f, true, 0);
	SETCOLOR(m_brush_text.fill_color,0,1,0);
	graphics::setFont(m_state->getFullAssetPath("grammatoseira.otf"));
	m_brush_text.fill_opacity = 1.0f;
	m_brush_background.outline_opacity = 0.0f;

	m_brush_background.texture = m_state->getFullAssetPath("background.png");

	for (auto p_gob : m_static_objects) 
		if (p_gob) p_gob->init();


	for (auto p_gob : m_dynamic_objects) 
		if (p_gob)p_gob->init();

	////////////////////////////////////////////////////////////////////////patwma
	for (int i = 1;i <= 100; i++)
	{
		m_blocks.push_back(Box(i * m_block_size, 6 * m_block_size, m_block_size, m_block_size));
		m_block_names.push_back("blocks.png");
		m_blocks.push_back(Box(i*m_block_size, 7, m_block_size, m_block_size));
		m_block_names.push_back("blocks.png");
	}
	

	//////////////////////////////////////////////////////////////////toixos arxikos-telikos
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 5; j++)	
		{
			m_blocks.push_back(Box(i * m_block_size, j * m_block_size, m_block_size, m_block_size));
			m_block_names.push_back("blocks.png");
		}
	}
	for (int i = 99; i <= 100; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			m_blocks.push_back(Box(i * m_block_size, j * m_block_size, m_block_size, m_block_size));
			m_block_names.push_back("blocks.png");
		}
	}
	

	//////////////////////////////////////////////////////////////////
	m_coins.push_back(Box(13 * m_coin_size, 2.5, m_coin_size, m_coin_size));
	m_coin_names.push_back("coin.png");///////////////////////////////////////////////////////////// 1 coin
	m_blocks.push_back(Box(13 * m_block_size, 3.5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_blocks.push_back(Box(14 * m_block_size, 3.5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_blocks.push_back(Box(15 * m_block_size, 3.5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_spikes.push_back(Box(14 , 2.6 , 1, 1));
	m_spike_names.push_back("spikes.png");
	m_blocks.push_back(Box(17 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_spikes.push_back(Box(18, 5.1, 1, 1));
	m_spike_names.push_back("spikes.png");
	//////////////////////////////////////////////////////////////////            
	m_blocks.push_back(Box(28 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_spikes.push_back(Box(29, 5.1, 1, 1));
	m_spike_names.push_back("spikes.png");
	m_coins.push_back(Box(30, 3, m_coin_size, m_coin_size));//////////////////////////////////////// 2 coin
	m_coin_names.push_back("coin.png");
	m_spikes.push_back(Box(30, 5.1, 1, 1));
	m_spike_names.push_back("spikes.png");
	m_spikes.push_back(Box(31, 5.1, 1, 1));
	m_spike_names.push_back("spikes.png");
	m_blocks.push_back(Box(32 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	//////////////////////////////////////////////////////////////////
	m_blocks.push_back(Box(40 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_blocks.push_back(Box(42 * m_block_size, 3.5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_blocks.push_back(Box(40 * m_block_size, 2.0 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_coins.push_back(Box(40, 1.0, 1, 1));
	m_coin_names.push_back("coin1.png");//////////////////////////////////////////////////////////// 3 coin

	//////////////////////////////////////////////////////////////////
	m_blocks.push_back(Box(49 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_spikes.push_back(Box(50, 5.1, 1, 1));
	m_spike_names.push_back("spikes.png");

	for (int i = 50; i <= 53; i++)
	{
		m_blocks.push_back(Box( i* m_block_size, 3.3 * m_block_size, m_block_size, m_block_size));
		m_block_names.push_back("blocks.png");
	}
	m_coins.push_back(Box(52, 2, m_coin_size, m_coin_size));//////////////////////////////////////// 4 coin
	m_coin_names.push_back("coin.png");
	m_spikes.push_back(Box(54.5, 5.1, 1, 1));
	m_spike_names.push_back("spikes.png");
	//////////////////////////////////////////////////////////////////
	m_blocks.push_back(Box(65 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	for (int i = 4; i <= 5; i++)
	{
		m_blocks.push_back(Box(67 * m_block_size, i * m_block_size, m_block_size, m_block_size));
		m_block_names.push_back("blocks.png");
	}
	for (int i = 3; i <= 5; i++)
	{
		m_blocks.push_back(Box(74 * m_block_size, i * m_block_size, m_block_size, m_block_size));
		m_block_names.push_back("blocks.png");
	}
	m_blocks.push_back(Box(68 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_blocks.push_back(Box(70 * m_block_size, 3 * m_block_size, m_block_size, m_block_size));
	m_block_names.push_back("blocks.png");
	m_coins.push_back(Box(70, 2, m_coin_size, m_coin_size));//////////////////////////////////////// 5 coin
	m_coin_names.push_back("coin.png");
	//////////////////////////////////////////////////////////////////

	m_coins.push_back(Box(83, 5, m_coin_size, m_coin_size));//////////////////////////////////////// 6 coin
	m_coin_names.push_back("coin.png");
	m_coins.push_back(Box(86, 4, m_coin_size, m_coin_size));//////////////////////////////////////// 7 coin
	m_coin_names.push_back("coin.png");
	//////////////////////////////////////////////////////////////////
	m_flag.push_back(Box(90 * m_block_size, 5 * m_block_size, m_block_size, m_block_size));
	m_flag_names.push_back("flag.png");

	

	//////////////////////////////////////////////////////////////////
	

	m_block_brush.outline_opacity = 0.0f;
	m_block_brush_debug.fill_opacity = 0.1f;
	SETCOLOR(m_block_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_block_brush_debug.fill_color, 0.3f, 1.0f, 0.2f);
	
	m_brush_coin.fill_opacity = 0.0f;
	m_brush_coin.outline_opacity = 0.0f;
	SETCOLOR(m_coin_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_coin_brush_debug.fill_color, 0.3f, 1.0f, 0.2f);

	m_flag_brush.outline_opacity = 0.0f;
	m_flag_brush_debug.fill_opacity = 0.0f;
	SETCOLOR(m_flag_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_flag_brush_debug.fill_color, 0.3f, 1.0f, 0.2f);

	m_spike_brush.outline_opacity = 0.0f;
	m_spike_brush_debug.fill_opacity = 0.0f;
	SETCOLOR(m_spike_brush_debug.fill_color, 0.2f, 1.0f, 0.1f);
	SETCOLOR(m_spike_brush_debug.fill_color, 0.3f, 1.0f, 0.2f);
}

void Level::draw()
{
	
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();
	float offset_x = m_state->m_global_offset_x + w / 2.0f;
	float offset_y = m_state->m_global_offset_y + h / 2.0f;
	for (int i = 0;i <= 8;i++) {
		graphics::drawRect(offset_x + i * (2.0f * w), offset_y, 2.0f * w, 4.0f * w, m_brush_background);
	}
	
	if (m_state->getPlayer()->isActive()) {
		m_state->getPlayer()->draw();

	}
	
	for (int i = 0; i < m_blocks.size(); i++) {
		drawBlock(i);
	}
	
	for (int i = 0; i < m_spikes.size(); i++) {
		drawSpikes(i);
	}

	
	for (int i = 0; i < m_coins.size(); i++) {
		drawCoin(i);
	}
	for (int i = 0; i < m_flag.size(); i++) {
		drawFlag(i);
	}

	
	std::string text = "Coin Score : " + std::to_string(coin_score);
	graphics::drawText(8.5, 0.3, 0.3f, text, m_brush_text);
	

	text = "Life Points : " + std::to_string(life_score);
	graphics::drawText(0.5, 0.3, 0.3f, text, m_brush_text);
	if (life_score <= 0) {
		text = "GAME OVER";
		graphics::drawText(2.5, 3, 2.0f, text, m_brush_text);
		m_state->getPlayer()->setActive(false);
	}
	if (finish) {
		text = "YOU WON";
		graphics::drawText(2.5, 3, 2.0f, text, m_brush_text);
		 text = "YOU GOT: " + std::to_string(coin_score) + "/7 COINS";
		graphics::drawText(2.1, 4, 1.0f, text, m_brush_text);
		m_state->getPlayer()->setActive(false);
		
	}
}

Level::Level(const std::string& name)
{
}

Level::~Level()
{
	for (auto p_gob : m_static_objects) {
		if (p_gob) delete p_gob;

	}

	for (auto p_gob : m_dynamic_objects) {
		if (p_gob) delete p_gob;

	}
}
