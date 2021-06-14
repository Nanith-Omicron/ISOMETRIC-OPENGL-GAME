#pragma once
#include "UI.h"
class UI_BAR : public UI {

public:
	Texture2D  Start,  Mid, End, Back;
	UI_BAR(Texture2D  S, Texture2D M, Texture2D E, Texture2D B) {
		Start =   S; Mid =  M; End =  E; Back =   B;
	}
	float size = 1;
	void resize(float w);
	virtual void Draw(SpriteBatch& renderer, bool selected);
};