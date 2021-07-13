#include "UI_Performer_status.h"

void powerBottom(SpriteBatch& renderer) {


}
void UI_Performer_Status::Draw(SpriteBatch& renderer, bool selected)
{
	if (!show || !who)return;
	glm::vec2 p = this->pos;
	HP->ui_ratio = who->HP / who->Max_HP;
	HP->Draw(renderer,selected);
	HP->pos = p += glm::vec2(0, 10)*scale;


	float start = (( HP->Back.Width/ 2) - 3.1)* scale  ;
	for (size_t i = 0; i < who->MaxNRJ; i++)
	{
		
		nrj->pos = p + glm::vec2(i * 4 * scale-start,6 * scale)  ;
		nrj->isOn = !(i >= who->NRJ);
		nrj->Draw(renderer, selected);
		 
	}
	
	Texture2D  ty;
	float s = scale/2;
	for (size_t i = 0; i < who->Effects.size(); i++)
	{
		ty = who->Effects[i]->tex;
	 
		renderer.draw(
			glm::vec4(p.x + i * s - s*25, p.y - s * 12,
			ty.Width * s, ty.Height * s),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			ty.ID, 9999999999, col);
	
	} 

}
