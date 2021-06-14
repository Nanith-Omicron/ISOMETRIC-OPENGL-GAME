#pragma once
#include "UI.h"

class UI_Toggle :public UI{
public:
	UI_Toggle(Texture2D a, Texture2D b){
		On = a;
		Off = b;
	}
	Texture2D On, Off;
	bool isOn = true;
	virtual void  Draw(SpriteBatch& renderer, bool selected);

};