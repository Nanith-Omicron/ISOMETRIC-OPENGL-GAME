#include "UI_BOX.h"

void UI_BOX::resize(float x, float y)
{
	sx = x;
	sy = y-.5;
}

void UI_BOX::Draw(SpriteBatch& renderer, bool selected)
{


	if (!show)return;
	glm::vec2 p = this->pos;



	float sTa = p.x + tl.Width * scale/2;

	float si = (((tm.Width ) * sx * scale)) - (tr.Width + tl.Width) * scale;
	float xsi = (((m.Height) * sy * scale)) - (m.Height + tl.Height) * scale;
 
	float yEnd = tm.Height * scale / 2 + xsi / 2;
	if (si < 0)si = 0;
	float start = sTa    + si / 2;
	float end = start + si - si / 2;
 

	renderer.draw(glm::vec4(p.x, p.y,
		tl.Width * scale, tl.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		tl.ID, 9999999999, col);
	renderer.draw(glm::vec4(start, p.y,
			si, tm.Height * scale),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			tm.ID, 9999999999, col);
	renderer.draw(glm::vec4(end, p.y,
		tr.Width * scale, tr.Height * scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		tr.ID, 9999999999, col);
	if (onlyCenter)return;
	// center
	renderer.draw(glm::vec4(p.x, p.y + yEnd,
		ml.Width * scale, xsi),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		ml.ID, 9999999999, col);

	renderer.draw(glm::vec4(start, p.y + yEnd,
		si, xsi),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		m.ID, 9999999999, col);

	renderer.draw(glm::vec4(end, p.y + yEnd,
		mr.Width * scale, xsi),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		mr.ID, 9999999999, col);

	//  end
	renderer.draw(glm::vec4(p.x, p.y + xsi + ll.Width * scale,
		ll.Width * scale, ll.Width* scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		ll.ID, 9999999999, col);

	renderer.draw(glm::vec4(start, p.y + xsi + lm.Width * scale,
		si, lm.Width* scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		lm.ID, 9999999999, col);

	renderer.draw(glm::vec4(end, p.y + xsi + lr.Width * scale,
		lr.Width * scale, lr.Width* scale),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		lr.ID, 9999999999, col);


}
