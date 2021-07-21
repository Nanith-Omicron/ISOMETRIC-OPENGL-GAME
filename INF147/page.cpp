#include "page.h"


 std::vector<page*>   page::Books;

bool menuOption = false;
int cur_option = -1;
int nextImage = 0;

void uwu() {
	printf("Open Editor\n");
	cur_option = 2;
	menuOption = true;
}


void lol() {
	printf("Trying Dungeon 1 \n");
	menuOption = true;
	cur_option = 1;
   }
void setFalse() {

	cur_option = -1;
	menuOption = false;
}

void page::init(int Width, int Height, Game * g)
{
	if (alreadyInit)return;
	alreadyInit = true;
	 W = Width;
	 H = Height;
	ortho = glm::ortho(0.0f, static_cast<float>(Width),
		static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
	printf("Init Main Menu.\n");
	_box cl, ho, no;
	current = g;
	int uscale = 5;

	auto box = UI_BUILDER::CreateDefaultBox(Width / 2, Height / 2 + 400, 6, 5, uscale);
 


 
	UIs.push_back(box);
 
	int offset = 40;
	float text_size = .8f;
	int but_x = 0;
	test_Buttons = UI_BUILDER::CreateDefaultButton(but_x, box->pos.y + offset , 
		uscale, "Dungeon 1 Test", text_size);
	but_x = box->pos.x + 28;
	test_Buttons->pos.x = but_x;
	test_Buttons->onClick = *lol;
 
	auto wrr = UI_BUILDER::CreateDefaultButton(but_x, box->pos.y +
		offset + 100, uscale, "Open Editor",text_size);
	auto qww = UI_BUILDER::CreateDefaultButton(but_x, box->pos.y 
		+ offset + 200, uscale,"Quit", text_size);
	wrr->onClick = *uwu;
	qww->onClick = *g->Quit;
	auto eq = new UI();
	eq->img = ResourceManager::GetTexture("krinj");
	eq->pos.x = but_x + eq->img.Width * eq->scale/2;
	eq->show = true;
	eq->pos.y = 350;
	eq->scale = 6;

	UIs.push_back(eq);
	smart_UIs.push_back(test_Buttons);
	smart_UIs.push_back(qww);
	smart_UIs.push_back(wrr);

}

void page::Render(SpriteBatch* sp, TextRenderer* Text, GLSLProgram* pr)
{
	pr->use();
	sp->begin(GlyphSortType::FRONT_TO_BACK);
	auto m_cameraMatrix = glm::translate(ortho, glm::vec3(sp->Camera, 0));
	m_cameraMatrix = glm::translate(ortho, glm::vec3(0, 0, 0));
	glUniform1i(pr->getUniformLocation("mySampler"), 0);
	glUniformMatrix4fv(pr->getUniformLocation("P"), 1, GL_FALSE, &m_cameraMatrix[0][0]);
	;

	int x = 0, y = 0;
	int x_size =0;
	
	int total = 0;
	/*
	for (auto const& imap : ResourceManager::Textures)
	{
	
		total++;
		if (total > nextImage)break;
		x++;
		if ( x > 30) {
			x = 0;
			x_size = 0;
			y++;
		}
		int h = 0;
		if (total == nextImage) {
			h = 30;
	   }
		auto b = imap.second;
		x_size += b.Width * 4 + 50 ;
		sp->draw(glm::vec4(50 + x * 50, 50 + y * 50 + h,
			b.Width * 3, b.Height * 3),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			b.ID, 9999999999, glm::vec4(1));
		total++;
	}	nextImage++;*/

	UI_Render(sp);

	sp->end();
	sp->renderBatch();
	pr->unuse();

	Render_Text(Text);

}

void page::Render_Text(TextRenderer* Text)
{
	for (int i = 0; i < smart_UIs.size(); i++)
	{
		smart_UIs[i]->DrawText(*Text);
	}
	for (int i = 0; i < windows.size(); i++)
	{
		windows[i]->DrawText(*Text);
	}
}


void page::Update(float dt)
{
	if (menuOption) {

		switch (cur_option)
		{
		case 1:
		
			current->loadTestLevel();

			break;
		case 2:
			current->openPage(1, GAME_EDITOR);
			;
		default:
			break;	
		}

		setFalse();

	}
	
}

void page::Update_UI(Mouse_info m)
{
	bool alreadSelected = false;
	for (int i = 0; i < windows.size(); i++)
	{
		windows[i]->update_UI(m);
	}
	for (int i = 0; i <smart_UIs.size(); i++)
	{
		if (smart_UIs[i]->Update(m, alreadSelected))alreadSelected = true;
	}
}

void page::UI_Render(SpriteBatch* sp)
{

	for (int i = 0; i < UIs.size(); i++) UIs[i]->Draw(*sp, false);
 

 	for (int i = 0; i < smart_UIs.size(); i++)
	{
		smart_UIs[i]->Draw(*sp, false);
	}
	for (int i = 0; i < windows.size(); i++)
	{
		windows[i]->Draw(*sp, false);
	}

}

 
