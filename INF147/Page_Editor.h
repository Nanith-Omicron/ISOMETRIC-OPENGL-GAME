#pragma once
#include "page.h"

 
class Page_Editor : public page {

	

public:
	void Create_item();
	void Modify_item();
	void ItemDB();
	void SeeItemDataBase();
	void  Update(float dt);
	virtual void init(int Width, int Height, Game* g);
 

};