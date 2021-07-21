#pragma once
 
#include "UI_BOX.h"
#include "UI_BUTTON.h"
#include "UI_BUILDER.h"
#include <string>
class UI_WINDOW : UI {
	bool ShowThis = false;
	bool hasText = false;
	bool hasButton = false;

public:
	static UI_WINDOW* Alert_Window(std::string ok,float x, float y, std::string name = "Alert Windows") {
		auto w = new UI_WINDOW();
		w->window_name = name;
		if (!ok.empty())w->hasText = true;
		w->text = ok;
		w->font_size = .7f;
		w->Text_offset.x = 60;
		w->Text_offset.y = -50;
		float uscale = 5;
		w->pos = glm::vec2(x, y);
		auto box = UI_BUILDER::CreateDefaultBox(x, y, 9, 4, uscale);

		w->UIs.push_back(box);
		auto error = UI_BUILDER::createQuickImage("Error!.png", x - 210, y - 120);
		w->UIs.push_back(error);
		auto but = UI_BUILDER::CreateDefaultButton(x - 50 , y - 30, uscale,
			"OK!");
		but->sx = 3;
		but->function = std::bind(&UI_WINDOW::Close, w ); // based
	

		w->buttons.push_back(but);
		return w;

	}
	static UI_WINDOW* ItemDB(float x, float y) {
		auto w = new UI_WINDOW();
		w->font_size = .7f;
		float uscale = 5;
		w->pos = glm::vec2(x, y);
		auto box = UI_BUILDER::CreateDefaultBox(x , y, 12, 13.2, uscale);
	
		w->UIs.push_back(box);
		w->UIs.push_back(UI_BUILDER::CreateDefaultInsideBox(x - 250, y + 15, 5, 12, uscale));

		auto tb = UI_BUILDER::CreateTopBar(x , y - 580, 12, 1, uscale);
		w->UIs.push_back(tb);


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
	glm::vec2 Text_offset;
	std::string window_name;
	
	void Open();
	void Close();
	virtual void Draw(SpriteBatch& renderer, bool selected, _box* box = NULL);
	virtual void DrawText(TextRenderer& Text);
	virtual void update_UI(Mouse_info m);
};