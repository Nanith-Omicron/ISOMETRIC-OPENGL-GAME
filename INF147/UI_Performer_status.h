#pragma once
#include "UI_BAR.h"
#include "UI_Toggle.h"
#include "performer.h"
class UI_Performer_Status : public UI {
public:
	UI_Toggle* nrj;
	UI_BAR* HP;
	performer* who;
	UI_Performer_Status(performer * w,UI_Toggle* t, UI_BAR* b) {
		HP = b;
		nrj = t;
		who = w;
	  }
	void  Draw(SpriteBatch& renderer, bool selected);
 
};
