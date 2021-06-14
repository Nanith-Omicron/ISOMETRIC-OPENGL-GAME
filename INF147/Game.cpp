#include "Game.h"

#include <GLSL.h>
//Entities type 
//TODO Make a component system . Performer should be the BASE entities for all  
 
 
#include "performer.h" // Animated and Game Object
 
 

#include <vector>		// To store the actors;
#include <algorithm>    // std::sort

#include "GLFW/glfw3.h"
#include <iomanip>
#include "SpriteBatch.h"
 
#include <iostream>
 
#include "global.h"
#include "level.h"

#include <Light.h>

#define str std::string
#define rsm ResourceManager::

SpriteRenderer* Renderer;
SpriteBatch spriteBatch;
TextRenderer* Text;

//
glm::vec2 LocalMouse, lerpPlayerPos;

//Actors
std::vector<actor*> perf;
std::vector<performer*> AI;
performer* player;

//For Shaders  
std::unique_ptr< GLSLProgram> m_program = nullptr;
std::unique_ptr< GLSLProgram> l_program = nullptr;

//Levels
level First;

//Lerp function
float Lerp(float a, float b, float t)
{
	return (1.0f - t) * a + t * b;
}

 
 
void t_q(str text, str id) {
	str s = "textures/" + text + ".png";
	ResourceManager::LoadTexture(s.c_str(), true, id);
}

//Quickly create a Human AI
performer* quickPerformer(int q) {


	auto wq = new performer(glm::vec2(400 + rand() % 2000, rand() % 2000), glm::vec2(100, 134.6), 
		ResourceManager::GetTexture("frag"), glm::vec3(.5, .5, 1));
	wq->platZ = 0;
	wq->Z = 500;
	wq->zDepthOffset = 172;//400;
	wq->size = glm::vec2(100, 100);
	wq->shadow = ResourceManager::GetTexture("shadow");

	animation idle;
	idle.addFrames(rsm GetTexture("q_pep_walk-1"));
	wq->addAnimation(idle);

	animation forward;
	forward.addFrames(rsm GetTexture("q_pep_walk-1"));
	forward.addFrames(rsm GetTexture("q_pep_walk-2"), 1);
	forward.addFrames(rsm GetTexture("q_pep_walk-3"), 3);
	forward.addFrames(rsm GetTexture("q_pep_walk-2"), 1);
	forward.addFrames(rsm GetTexture("q_pep_walk-1"));
	forward.addFrames(rsm GetTexture("q_pep_walk-4"), 1);
	forward.addFrames(rsm GetTexture("q_pep_walk-5"), 3);
	forward.addFrames(rsm GetTexture("q_pep_walk-4"), 1);
	wq->addAnimation(forward);

	animation idle_u;
	idle_u.addFrames(rsm GetTexture("q_pep_walk_u-1"));
	wq->addAnimation(idle_u);

	animation backward;
	backward.addFrames(rsm GetTexture("q_pep_walk_u-1"));
	backward.addFrames(rsm GetTexture("q_pep_walk_u-2"), 1);
	backward.addFrames(rsm GetTexture("q_pep_walk_u-3"), 3);
	backward.addFrames(rsm GetTexture("q_pep_walk_u-2"), 1);
	backward.addFrames(rsm GetTexture("q_pep_walk_u-1"));
	backward.addFrames(rsm GetTexture("q_pep_walk_u-4"), 1);
	backward.addFrames(rsm GetTexture("q_pep_walk_u-5"), 3);
	backward.addFrames(rsm GetTexture("q_pep_walk_u-4"), 1);
	wq->addAnimation(backward);

	animation jump_u;
	jump_u.addFrames(rsm GetTexture("q_pep_walk_u-3"));
	wq->addAnimation(jump_u);

	animation jump;
	jump.addFrames(rsm GetTexture("q_pep_walk-3"));
	wq->addAnimation(jump);
	perf.push_back(wq);
 
 
	if(q != 0)
	AI.push_back(wq);
	return wq;
}

//Bind a freshly created performer to the player
void setupPlayer() {

	player = quickPerformer(0);
	player->platZ = 0; 	player->Z = 500; player->zDepthOffset = 400;
	player->size = glm::vec2(100, 100);	 
	player->quickStat(10, 3);
	return;
}
 
void loadTexture() {
	// load textures
	ResourceManager::LoadTexture("textures/tile_2.png", true, "base");
	ResourceManager::LoadTexture("textures/tile_sand.png", true, "sand");
	ResourceManager::LoadTexture("textures/tile_big.png", true, "big");
	ResourceManager::LoadTexture("textures/tile_frag.png", true, "frag");
	ResourceManager::LoadTexture("textures/shadow.png", true, "shadow");
	ResourceManager::LoadTexture("textures/tile_stone.png", true, "dungeon_wall");
	ResourceManager::LoadTexture("textures/tile_stone_top.png", true, "dungeon_wall_top");
	ResourceManager::LoadTexture("textures/dungeon_floor.png", true, "dungeon_floor");
	ResourceManager::LoadTexture("textures/dungeon_floor-1.png", true, "dungeon_floor_1");
	ResourceManager::LoadTexture("textures/dungeon_floor-2.png", true, "dungeon_floor_2");
	ResourceManager::LoadTexture("textures/dungeon_floor-3.png", true, "dungeon_floor_3");
	ResourceManager::LoadTexture("textures/dungeon_floor-4.png", true, "dungeon_floor_4");
	ResourceManager::LoadTexture("textures/dungeon_floor-5.png", true, "dungeon_floor_5");
	ResourceManager::LoadTexture("textures/dungeon_floor-6.png", true, "dungeon_floor_6");
	ResourceManager::LoadTexture("textures/Big_nana.png", true, "big_nana");

	ResourceManager::LoadTexture("textures/UI/HP_Start.png", true, "HP_S");
	ResourceManager::LoadTexture("textures/UI/HP_Mid.png", true, "HP_M");
	ResourceManager::LoadTexture("textures/UI/HP_End.png", true, "HP_E");
	ResourceManager::LoadTexture("textures/UI/HP_BAR.png", true, "HP_B");

	ResourceManager::LoadTexture("textures/UI/NRJ.png", true, "NRJ");
	ResourceManager::LoadTexture("textures/UI/NRJ_BAR.png", true, "NRJ_B");
	ResourceManager::LoadTexture("textures/UI/NRJ_UP.png", true, "NRJ_UP");
	ResourceManager::LoadTexture("textures/UI/HRT_UP.png", true, "HRT_UP");


	t_q("Quad_People_Walking_U_walking-1", "q_pep_walk_u-1");
	t_q("Quad_People_Walking_U_walking-2", "q_pep_walk_u-2");
	t_q("Quad_People_Walking_U_walking-3", "q_pep_walk_u-3");
	t_q("Quad_People_Walking_U_walking-4", "q_pep_walk_u-4");
	t_q("Quad_People_Walking_U_walking-5", "q_pep_walk_u-5");
	t_q("Quad_people_walking-1", "q_pep_walk-1");
	t_q("tile_dirt", "dirt");
	t_q("Quad_People_walking-2", "q_pep_walk-2");
	t_q("Quad_People_walking-3", "q_pep_walk-3");
	t_q("Quad_People_walking-4", "q_pep_walk-4");
	t_q("Quad_People_walking-5", "q_pep_walk-5");
}
 
void ShadersInit() {

	//Initiliazed the SpriteBatch
	spriteBatch.init();

	m_program = std::make_unique<GLSLProgram>();
	m_program->compileShaders("BatchShader.vs", "batchFragment.frag");
	m_program->addAttribute("vertexPosition");
	m_program->addAttribute("vertexColor");
	m_program->addAttribute("vertexUV");
	m_program->linkShaders();

	l_program = std::make_unique<GLSLProgram>();
	l_program->compileShaders("lightShading.vs", "lightShading.frag");
	l_program->addAttribute("vertexPosition");
	l_program->addAttribute("vertexColor");
	l_program->addAttribute("vertexUV");
	l_program->linkShaders();

}


//Graphics setup of Game. Setup the Shaders and load the textures
void setupGraphics() {

	//Create a new renderer
	Renderer = new SpriteRenderer();
	//Initialize the shaders
	ShadersInit();
	//Load all the textures : TODO, Make it automatic based on what's in the /textures/folder
	loadTexture();
 
}



//Setup the Game
void Game::Init() {
 
	//Offset to center
	Offset.x = 600;
	Offset.y = 800;
	
	//Setup Text
	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("fonts/FredokaOne-Regular.ttf", 24);
	
	//Setup Graphis and the players
	setupGraphics();
	//Setup the player
	setupPlayer();	

	//===============   Initialize the level  =================//
	First.init("dungeon/dungeon_prototype.png", Width, Height);
	//====================Enter the level======================//
	First.enter(player);

	//Initialized the lerpPlayerPos to -300 for introduction effects
	lerpPlayerPos = player->pos + glm::vec2(0,-300);
}
void Game::Update(float dt) {
 
	//Player move based on Input
	player->Move(player->input_Dir, dt);
	//Make the player Jump
	

	//Move the camera based on the Last cameraPos and current player pos
	lerpPlayerPos.x = Lerp(lerpPlayerPos.x, player->pos.x, .04f * spriteBatch.zoom);
	lerpPlayerPos.y = Lerp(lerpPlayerPos.y, player->pos.y, .04f * spriteBatch.zoom);

	//Set the camera to Lerp Postion + Offset
	spriteBatch.Camera = (-lerpPlayerPos)+ glm::vec2(Offset.y, Offset.x);


	//Update the level
	First.update(dt);
 
}

void Game::ProcessInput(float dt) {

	//Calculate Mouse position in localPosition 
	LocalMouse.x = (mouseX - spriteBatch.Camera.x) / spriteBatch.zoom;
	LocalMouse.y = (mouseY - spriteBatch.Camera.y) / spriteBatch.zoom;

	glm::vec2 player_input_dir = glm::vec2(0, 0);

	//Move based on WASD		
	if (Keys[GLFW_KEY_A])player_input_dir.x -= 1;
	if (Keys[GLFW_KEY_D])player_input_dir.x += 1;
	if (Keys[GLFW_KEY_W])player_input_dir.y -= 1;
	if (Keys[GLFW_KEY_S])player_input_dir.y += 1;

	//Change the Z_layer effects based on X,Z
	if (Keys[GLFW_KEY_X])player->zDepthOffset += 1;
	if (Keys[GLFW_KEY_Z])player->zDepthOffset -= 1;

	//Set the inupt_DIR of the player.
	player->setInputDir(player_input_dir);

	//Scroll the zoom based on the lerp acceleration of the mouse.
	if (abs(mouseScroll )>= 0)spriteBatch.zoom += (mouseScroll * dt * 10);
		 
	mouseScroll = Lerp(mouseScroll, 0,.8f);
	//Min and Max the zoom
	if (spriteBatch.zoom <= .5f)spriteBatch.zoom = .5f;
	if (spriteBatch.zoom >= 2.5f)spriteBatch.zoom = 2.5f;

	//Make the player jump on space 
	if (Keys[GLFW_KEY_SPACE])player->Jump(dt);
}

 

void debug(float dt) {
	if ((dt) > 0) {
		Text->RenderText("FPS", 0, 00, 1);
		Text->RenderText(std::to_string(1 / (dt)), 70, 00, 1);
	}
	Text->RenderText("Player", 5, 35, 1.0F); 	Text->RenderText(std::to_string((int)player->Z), 160, 35, 1.0F);
	Text->RenderText(std::to_string((int)player->localPos().x), 90, 34, 1.0F);
	Text->RenderText(std::to_string((int)player->localPos().y), 90, 60, 1.0F);

	Text->RenderText(std::to_string(player->currentCell->x), 90, 155, 1.0F);
	Text->RenderText(std::to_string(player->currentCell->y), 120, 155, 1.0F);
	Text->RenderText(std::to_string(player->currentCell->peps.size()), 150, 155, 1.0F);
	Text->RenderText("zdepth", 5, 100, 1.0F);
	Text->RenderText(std::to_string(player->zDepthOffset), 90, 100, 1.0F);
 
}

void Game::Render(float dt) {

	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	First.render(&spriteBatch, m_program.get());
	debug(dt);
}
