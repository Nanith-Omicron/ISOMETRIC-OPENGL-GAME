#pragma once

#include "UI_BAR.h"

class UI_BOX : public UI {

public:
	//Pieces of the bar
	Texture2D  tl, tm, tr, ml, m, mr, ll, lm, lr;
	bool onlyCenter = false;
	//initilization of the UI bar itself
	UI_BOX( Texture2D ML, Texture2D M, Texture2D MR) {
	 tl = ML; tm = M; tr = MR; 
	 onlyCenter = true;
	}
	UI_BOX(Texture2D  TL, Texture2D TM, Texture2D TR, Texture2D ML, Texture2D M, Texture2D MR, Texture2D LL, Texture2D  LM, Texture2D LR) {
		tl = TL; tm = TM; tr = TR; ml = ML; m = M; mr = MR; ll = LL; lm = LM; lr = LR;
	}
	//From 0 to 1, determined the ratio at which it's completed
	float sx = 5, sy = 5;
	//Resize and clamp the bar
	void resize(float x, float y);
	//Draw routine. Receive an Renderer. Selected change the colors
	virtual void Draw(SpriteBatch& renderer, bool selected);
};