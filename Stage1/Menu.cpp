#include "Menu.h"
#include "util.h"
#include "GameState.h"

void Menu::init() {
	SETCOLOR(m_brush_text1.fill_color, 0, 0, 0);
	graphics::setFont (m_state->getFullAssetPath("grammatoseira.otf"));
	m_brush_text1.fill_opacity = 1.0f;
	m_brush_bkgnd.outline_opacity = 0.0f;

	m_brush_bkgnd.texture = m_state->getFullAssetPath("background-menu.png");
}
void Menu::draw() {
	float w = m_state->getCanvasWidth();
	float h = m_state->getCanvasHeight();
	float offset_x = m_state->m_global_offset_x + w / 2.0f;
	float offset_y = m_state->m_global_offset_y + h / 2.0f;
	
	graphics::drawRect(offset_x , offset_y,  w,  h, m_brush_bkgnd);
	
	std::string text = "created by Antonis Pavlou-Dimitris Tassopoulos ";
	graphics::drawText(w - 4.0, 5.0f, 0.3f, text, m_brush_text1);
	text = "SUPER NINJA";
	graphics::drawText(4.2, 2.0, 0.5f, text, m_brush_text1);
	text = "To Start Press Enter";
	graphics::drawText(2.8, 3.0, 0.7f, text, m_brush_text1);
}
void Menu::update(float dt) {
	GameObject::update(200);
}
	