#pragma once

#include "UI_BAR.h"
#include "UI_BOX.h"
#include "UI_BUTTON.h"
#include "glm/glm.hpp"
#include "SpriteBatch.h"
#include "textrenderer.h"
#include "GLSL.h"
class page {
	UI_BUTTON * test_Buttons;
public: 
	int W, H;
	std::vector<UI*> UIs;
	std::vector< UI_BUTTON*> smart_UIs;
	void (*letsGO)();
	void (*con_Click)(Game* b);
	Game* current;
	glm::mat4 ortho;
	void init(int Width, int Height, Game * g);
	void Render(SpriteBatch* sp, TextRenderer* Text, GLSLProgram* pr);
	void Update(float dt);
	void Update_UI(Mouse_info m);
	void UI_Render(SpriteBatch* sp);
	int toGo;
	 



};