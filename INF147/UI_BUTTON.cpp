#include "UI_BUTTON.h"
//TO DO, function are better
bool UI_BUTTON::Update(Mouse_info m, bool x)
{
	bool UseClick = state == CLICKED;
	state = NORMAL;
	if (x)return false;
	ui_size_y = norm.tr.Height * scale;
	if (!onlyCenter)ui_size_y = norm.tr.Height * scale * sy - (norm.tr.Height + norm.tl.Height) * scale;
	ui_size_x = (norm.tm.Width * sx) * scale - (norm.tr.Width + norm.tl.Width) * scale;


	if (m.rawX > pos.x && m.rawX < pos.x + ui_size_x)
		if (m.rawY > pos.y - ui_size_y / 2 && m.rawY < pos.y + ui_size_y / 2) {

			if (m.buttons[0]) {
				state = CLICKED;
				if (!UseClick && onClick != NULL) {
					onClick();

					return true;
				}
				if (!UseClick && function != NULL) {
					function();
					return true;
				}
			}
			else if (m.buttons[1])state = RIGHT_CLICKED;
			else state = HOVER;


		}
	return state != NORMAL;
}

void UI_BUTTON::Draw(SpriteBatch& renderer, bool selected, _box* box)
{
	_box* lol = &norm;


	switch (state)
	{
	case NORMAL:
		lol = &norm;
		lol->empt = false;

		break;
	case HOVER:
		lol = &hov;
		lol->empt = false;

		break;
	case CLICKED:
		lol = &click;
		lol->empt = false;
		break;
	case RIGHT_CLICKED:
		break;
	case DRAGGED:
		break;
	default:
		lol = &norm;
		lol->empt = false;

		break;
	}
	UI_BOX::Draw(renderer, selected, lol);

}


