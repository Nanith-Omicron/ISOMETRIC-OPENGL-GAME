#pragma once
#include "UI_BOX.h"
#include <functional>
 
enum UI_BUTTON_STATE {
	NORMAL,
	HOVER,
	CLICKED,
	RIGHT_CLICKED,
	DRAGGED
};
class UI_BUTTON : public UI_BOX {

public:
 
	 
	_box norm, hov, click;
	UI_BUTTON_STATE state;
	double ui_size_x, ui_size_y;
	UI_BUTTON(_box* normal, _box* hover, _box* clicked, bool onlyCentr = false) :UI_BOX(normal) {
		norm = *normal;
		hov = *hover;
		click = *clicked;
		onlyCenter = onlyCentr;
		internal_box = *normal;
		ui_size_x = (norm.tm.Width * sx) * scale - (norm.tr.Width + norm.tl.Width) * scale;

	}
	void (*onClick)();
	std::function<void()> function;
	
	virtual bool Update(Mouse_info m, bool x);
	virtual void Draw(SpriteBatch& renderer, bool selected, _box* box = NULL) override;
	 
};