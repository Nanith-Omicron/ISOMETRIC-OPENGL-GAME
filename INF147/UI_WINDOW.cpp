#include "UI_WINDOW.h"

void UI_WINDOW::Open()
{
	 
	printf(("Opened window : " + window_name + "\n" ).c_str());
	ShowThis = true;
}

void UI_WINDOW::Close()
{
	ShowThis = false;
}

void UI_WINDOW::Draw(SpriteBatch& renderer, bool selected, _box* box)
{
	if (!ShowThis)return;
	 
	for (int i = 0; i < UIs.size(); i++)	 
		UIs[i]->Draw(renderer, selected);

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->Draw(renderer,selected);
	}
	 
}

void UI_WINDOW::DrawText(TextRenderer& Tx)
{
	if (!ShowThis)return;
	for (int i = 0; i < buttons.size(); i++)
		buttons[i]->DrawText(Tx);
		
	if (!hasText)return;
	Tx.RenderText(text,
		pos.x + renderedSize().x / 2 + 24 * font_size - (text.size()) * 9 * font_size + Text_offset.x,
		pos.y - font_size * 24/2   * 9 + Text_offset.y, font_size, glm::vec4(.8, .8, .8, .2));


}

void UI_WINDOW::update_UI(Mouse_info m)
{
	hasButton = false; 
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->Update(m, hasButton))hasButton = true;
	}
}
