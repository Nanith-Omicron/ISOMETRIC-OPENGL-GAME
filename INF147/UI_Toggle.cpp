#include "UI_Toggle.h"

void UI_Toggle::Draw(SpriteBatch& renderer, bool selected)
{

 
	if (!show)return;
	glm::vec2 p = this->pos;


	renderer.draw(glm::vec4(p.x, p.y,
		Off.Width * scale, Off.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Off.ID, 9999999999, col);
	if (!isOn)return;
	renderer.draw(glm::vec4(p.x, p.y-1*scale,
		On.Width * scale, On.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		On.ID, 9999999999, col);
}
