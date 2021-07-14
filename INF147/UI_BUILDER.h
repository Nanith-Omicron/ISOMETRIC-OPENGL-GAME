#pragma once
#include "UI_BUTTON.h"
#include <string>
class UI_BUILDER {
public:
	static UI_BUTTON * CreateDefaultButton(int x, int y,float scale,  std::string w ="", float fontsize = .8f) {
		_box cl, ho, no;

		no.tl = ResourceManager::GetTexture("Metal_UI_BUTTON_R");
		no.tm = ResourceManager::GetTexture("Metal_UI_BUTTON_C");
		no.tr = ResourceManager::GetTexture("Metal_UI_BUTTON_L");

		cl.tl = ResourceManager::GetTexture("Metal_UI_BUTTON_R");
		cl.tm = ResourceManager::GetTexture("Metal_UI_BUTTON_CC");
		cl.tr = ResourceManager::GetTexture("Metal_UI_BUTTON_L");

		ho.tl = ResourceManager::GetTexture("Metal_UI_BUTTON_R");
		ho.tm = ResourceManager::GetTexture("Metal_UI_BUTTON_H");
		ho.tr = ResourceManager::GetTexture("Metal_UI_BUTTON_L");
		auto b = new UI_BUTTON(&no, &ho, &cl,true);
		if (!w.empty())b->setText(w);
		b->scale = scale;
		b->font_size = fontsize;
		b->pos.x = x;
		b->pos.y = y;
		return b;
	}
	static UI* createQuickImage(std::string w, int x, int y, float uscale = 5) {
		auto q = new UI();
		q->img = ResourceManager::GetTexture(w);
		q->pos = glm::vec2(x, y);
		q->scale = uscale;
		return q;
	}
	static UI_BOX* CreateDefaultBox(int x, int y, float sx, float sy, float scale) {

		auto box = new UI_BOX(
			ResourceManager::GetTexture("UI_BOX_METAL_TL"),
			ResourceManager::GetTexture("UI_BOX_METAL_TM"),
			ResourceManager::GetTexture("UI_BOX_METAL_TR"),
			ResourceManager::GetTexture("UI_BOX_METAL_ML"),
			ResourceManager::GetTexture("UI_BOX_METAL_M"),
			ResourceManager::GetTexture("UI_BOX_METAL_MR"),
			ResourceManager::GetTexture("UI_BOX_METAL_LL"),
			ResourceManager::GetTexture("UI_BOX_METAL_LM"),
			ResourceManager::GetTexture("UI_BOX_METAL_LR")
		);
		box->scale = scale;
		box->resize(sx, sy);
		auto cp = box->renderedSize();
		box->pos.x = x -cp.x/2;
		box->pos.y = y -cp.y/2;

		return box;


	}


};