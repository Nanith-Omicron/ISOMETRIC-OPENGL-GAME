#include "UI_BAR.h"
#include "UI_BOX.h"

void UI_BAR::resize(float w)
{
	ui_ratio = w;
	if (ui_ratio > 1)ui_ratio = 1;
	if (ui_ratio < 0)ui_ratio = 0;
}



void UI_BAR::Draw(SpriteBatch& renderer, bool selected)
{

	if (ui_ratio < 0)ui_ratio = 0;
	if (!show)return;
	glm::vec2 p = this->pos;

	if (&Back)
		renderer.draw(glm::vec4(p.x, p.y,
			Back.Width * scale, Back.Height * scale),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			Back.ID, 9999999999, col);


	float sTa = p.x - (Back.Width * scale) / 2 + Start.Width * scale;
	renderer.draw(glm::vec4(sTa, p.y,
		Start.Width * scale, Start.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		Start.ID, 9999999999, col);

	float si = (((Back.Width - Mid.Width + 1) * ui_ratio * scale)) - (End.Width + Start.Width) * scale;
	if (si < 0)si = 0;
	float start = sTa + Start.Width * scale / 2 + si / 2;
	float end = start + si - si / 2;
	if (si > 0)
		renderer.draw(glm::vec4(start, p.y,
			si, Mid.Height * scale),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			Mid.ID, 9999999999, col);
	renderer.draw(glm::vec4(end, p.y,
		End.Width * scale, End.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		End.ID, 9999999999, col);

}
