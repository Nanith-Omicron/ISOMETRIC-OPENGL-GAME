#pragma once

#include "UI_BAR.h"
#include "UI_BOX.h"
#include "UI_BUTTON.h"
#include "glm/glm.hpp"
#include "SpriteBatch.h"
#include "textrenderer.h"
#include "GLSL.h"
#include "UI_BUILDER.h"
#include "UI_WINDOW.h"
class page {
	UI_BUTTON * test_Buttons;

public: 
	 
 


	static std::vector<page*>   Books;
	std::vector<UI_WINDOW* > windows;
	int W, H;
	bool alreadyInit = false;
	std::vector<UI*> UIs;
	std::vector< UI_BUTTON*> smart_UIs;
	void (*letsGO)();
	void (*con_Click)(Game* b);
	Game* current;
	glm::mat4 ortho;
	virtual void init(int Width, int Height, Game * g);
	virtual void Render(SpriteBatch* sp, TextRenderer* Text, GLSLProgram* pr);
	virtual void Render_Text(TextRenderer* Text);
	virtual void Update_UI(Mouse_info m);
	
	void Update(float dt);

	void UI_Render(SpriteBatch* sp);
	int toGo;
	 



};