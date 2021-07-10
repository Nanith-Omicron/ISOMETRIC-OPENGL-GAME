#include "page.h"
#include "UI_BUILDER.h"



void uwu() {
	printf("Uwu this Function pointer works \n");
}
void lol() {
  }

void page::init(int Width, int Height, Game * g)
{
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


	UI_Render(sp);

	sp->end();
	sp->renderBatch();
	pr->unuse();


	for (int i = 0; i < smart_UIs.size(); i++)
	{
		smart_UIs[i]->DrawText(*Text);
	}
}


void page::Update(float dt)
{

}

void page::Update_UI(Mouse_info m)
{
	bool alreadSelected = false;
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

}

 