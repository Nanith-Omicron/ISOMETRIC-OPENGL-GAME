#pragma once
 
#include "UI_BOX.h"
#include "UI_BUTTON.h"
#include "UI_BUILDER.h"

class UI_WINDOW : UI {

	static UI_WINDOW* Alert_Window(float x, float y) {
		auto w = new UI_WINDOW();
		float uscale = 5;
		w->pos = glm::vec2(x, y);
		auto box = UI_BUILDER::CreateDefaultBox(x, y, 5, 3, uscale);
		w->UIs.push_back(box);
		auto error = UI_BUILDER::createQuickImage("Error.png", x - 300, y - 50);
		w->UIs.push_back(error);
		auto but = UI_BUILDER::CreateDefaultButton(x, y + 50, uscale,
			"OK!");
		but->sx = 3;
		return w;

	}
	std::vector<UI_BUTTON* > buttons;
	std::vector<UI*> UIs;
	std::string text = " ";
	glm::vec2 ren_size;
	glm::vec2 renderedSize() {

		return ren_size;

	}
	float font_size = 0.9f;
	bool ShowThis = false;
	bool hasText = false;
	void Open();
	void Close();
	virtual void Draw(SpriteBatch& renderer, bool selected, _box* box = NULL);
	virtual void DrawText(TextRenderer& Text);

};