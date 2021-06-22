#pragma once
#include "UI.h"

//An class to represent a bar of all sort based on float between 0 an 1
class UI_BAR : public UI {

public:
	//Pieces of the bar
	Texture2D  Start,  Mid, End, Back;
	//initilization of the UI bar itself
	UI_BAR(Texture2D  S, Texture2D M, Texture2D E, Texture2D B) {
		Start =   S; Mid =  M; End =  E; Back =   B;
	}

	UI_BAR(Texture2D  S, Texture2D M, Texture2D E ) {
		Start = S; Mid = M; End = E; Back = M;
	}
	//From 0 to 1, determined the ratio at which it's completed
	float ui_ratio = 1;
	//Resize and clamp the bar
	void resize(float w);
	//Draw routine. Receive an Renderer. Selected change the colors
	virtual void Draw(SpriteBatch& renderer, bool selected);
};