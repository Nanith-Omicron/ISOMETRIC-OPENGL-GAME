#pragma once

#include "UI_BAR.h"
#include <string>

struct _box {

	bool empt = true;
	Texture2D  tl , tm, tr, ml, m, mr, ll, lm, lr;
	_box() {

	}
	_box(Texture2D qml, Texture2D qm, Texture2D qmr) {
		 m = qm;
		 ml = qml;
		 mr = qmr;
	 }
};
class UI_BOX : public UI {

public:
	//Pieces of the bar
	_box internal_box;
	bool onlyCenter = false;
	bool hasText = false;
	std::string TextToWrite;
	float font_size = 1.0f;
	glm::vec2 renderedSize() {

		glm::vec2 pop;
		pop.x =( internal_box.tm.Width * sx - internal_box.tl.Width - internal_box.tr.Width)* scale;
		pop.y =( internal_box.tm.Height * sy + internal_box.tl.Height+ internal_box.tr.Height)* scale;
		return pop;
	}
	glm::vec2 centeredPos()
	{
		auto p = pos;
		p.x += ((internal_box.tm.Width * sx) * scale + (internal_box.tr.Width + internal_box.tl.Width) * scale)/2;
	
		auto w = internal_box.tr.Height * scale;
		if (!onlyCenter)w = internal_box.tr.Height * scale * sy - (internal_box.tr.Height + internal_box.tl.Height) * scale;
		p.y += w / 2;
		return p;
	}

	//initilization of the UI bar itself
	
	UI_BOX(_box * b) {
		internal_box = *b;
	}
	UI_BOX( Texture2D ML, Texture2D M, Texture2D MR) {
		internal_box.tl = ML;  internal_box.tm = M;  internal_box.tr = MR;
		internal_box.empt = false;
	 onlyCenter = true;
	}
	UI_BOX(Texture2D  TL, Texture2D TM, Texture2D TR, Texture2D ML, Texture2D M, Texture2D MR, Texture2D LL, Texture2D  LM, Texture2D LR) {
		internal_box.tl = TL;  internal_box.tm = TM;  internal_box.tr = TR;  internal_box.ml = ML;  
		internal_box.m = M;  internal_box.mr = MR;  internal_box.ll = LL; 
		internal_box.lm = LM;  internal_box.lr = LR;
		internal_box.empt = false;
	}
	//From 0 to 1, determined the ratio at which it's completed
	float sx = 5, sy = 5;
	//Resize and clamp the bar
	//Draw routine. Receive an Renderer. Selected change the colors
	void setText(std::string w) {
		hasText = true;
		TextToWrite = w;
	}
	virtual void Draw(SpriteBatch& renderer, bool selected, _box  * box = NULL) ;
	virtual void Draw(SpriteBatch& renderer, bool selected);
	virtual void DrawText(TextRenderer& Text);
	void resize(float x, float y);
};
