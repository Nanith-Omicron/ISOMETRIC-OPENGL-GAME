#include "UI.h"

void UI::StickTo(actor * x)
{
	pos = x->pos + offset;
}

void UI::setPos(float x, float y)
{
	pos =  glm::vec2(x, y);
}

void UI::Draw(SpriteBatch& renderer, bool selected)
{
	if (!show)return; 
 	glm::vec2 p = this->pos;
	float qw = 1;
 
		renderer.draw(glm::vec4(p.x, p.y,
		img.Width * scale, img.Height*scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			img.ID, 999999999999999999, col);
}
 	
 