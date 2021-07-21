#include "Page_Editor.h"
bool mOption = false;
int cur_Op = 0;
void Page_Editor::Create_item()
{
}

void Page_Editor::Modify_item()
{
}

void Page_Editor::ItemDB()
{
	windows[1]->Open();
}

void Page_Editor::SeeItemDataBase()
{

} 
void open_item_module() {
	mOption = true;
	cur_Op = 3;
} 


void Page_Editor::Update(float dt)
{

	if (mOption) {

		switch (cur_Op)
		{
		case 1:		 
		 
			break;
		case 2 :
			current->openPage(0, GAME_MENU);
		case 3: 
			ItemDB();
			break;
		default:
			printf("NO OPTION FOR THIS NUMBER: %d\n", cur_Op);
			break;
		}
		cur_Op = -1;
		mOption = false;


	}

}

void Page_Editor::init(int Width, int Height, Game* g)
{
	if (alreadyInit)return;
	alreadyInit = true;
	W = Width;
	H = Height;
	current = g;

	ortho = glm::ortho(0.0f, static_cast<float>(Width),
	static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
	printf("Init Editor.\n");
 
	
	int uscale = 5;
	auto w = UI_WINDOW::Alert_Window("This is just a way to test alert", W/2, H/2,"Alert Window");
	UIs.push_back(UI_BUILDER::CreateDefaultBox(W / 2 - 20, H / 2 + 110, 20.8, 16, uscale));
	UIs.push_back(UI_BUILDER::CreateDefaultBox(  300, H / 2 + 120 ,8, 13.2, uscale));
	
	auto createObj = UI_BUILDER::CreateDefaultButton(120,  100, uscale, "Items");
	createObj->sx = 7;
	createObj->setPos(90, 100);
	createObj->onClick = open_item_module;
	//auto modifyObj = UI_BUILDER::CreateDefaultButton(150,  120, uscale, "Modify Items");


	 


	windows.push_back(w);
	windows.push_back(UI_WINDOW::ItemDB(W / 2 + 270, H / 2 + 120));
	smart_UIs.push_back(createObj);


	

}

 
