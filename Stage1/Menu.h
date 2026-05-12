#pragma once
#include "level.h"

class Menu :public GameObject, public Box {
private:

	graphics::Brush m_brush_text1;
	graphics::Brush m_brush_bkgnd;
public:
	Menu () {

	}
	~Menu(){}
	 void update(float dt) ;
	 void init() ;
	 void draw() ;
};
