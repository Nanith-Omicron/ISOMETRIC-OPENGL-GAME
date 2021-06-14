#pragma once
#include "Grid.h"
#include "Actor.h"
#include "tile.h"
#include <iomanip>
#include <vector>
#include <string>
#include "SpriteBatch.h"
#include "stbi.h"
#include <blob.h>
#include <GLSL.h>
#include "glm/glm.hpp"
#include <UI.h>
#include "UI_Performer_status.h"
#include <item.h>


struct MetaTile {
public:
	bool HasTile = false;
	bool HasOnTop = false;
	tile* _tile;
	MetaTile* onTop;

};

class level {
	
public:

	//Level creation function

	void createRoom(glm::vec2 there);

	void createFloor(glm::vec2 there);

	void createWall(glm::vec2 there, bool t);

	//General function
	virtual void init(const char* file, int Width, int Height);
	virtual void enter(performer* player);
 
	virtual void update(float dt);
	bool  visit(glm::vec2 p1, float l);
	void raytrace(glm::vec2 from, glm::vec2 there);
	void raycastAlgorithm();
	virtual void render(SpriteBatch* sp, GLSLProgram * pr);
	virtual void exit();

	std::string level_Name;
	int level_size_X, level_size_Y, level_size_Z;
	int ScreenH, ScreenW;
	int level_ID;
	int cellSize = 3;
	int heightOfWall = 3;
	tile** grid_Tile;
	MetaTile* metaTile;
	glm::vec2 LastPLayerPos;
	performer* player;
	glm::mat4 ortho;
	std::unique_ptr < Grid> Area;
	std::vector<tile*> Tiles;
	std::vector<UI*> UIs;
	std::vector<actor*> NPCs, all;
	std::vector<actor*> Viewable;
	std::vector<item*> Items;
	std::vector<region*> Regions, Nearby;

 

};
 
