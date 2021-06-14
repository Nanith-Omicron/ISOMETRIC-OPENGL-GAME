#include "Game.h"

#include <GLSL.h>
//Entities type 
//TODO Make a component system . Performer should be the BASE entities for all of it 
#include "actor.h" //General Entities
#include "tile.h"  // Static Tiles
#include "performer.h" // Animated and Game Object
#include "blob.h"
#include "Quadtree.h"

#include <vector>		// To store the actors;
#include <algorithm>    // std::sort

#include "GLFW/glfw3.h"
#include <iomanip>
#include "SpriteBatch.h"
#include <memory>
#include <iostream>
#include "Grid.h"
#include "global.h"
#include "level.h"
#include <Light.h>

#define str std::string
#define rsm ResourceManager::

SpriteRenderer* Renderer;
SpriteBatch spriteBatch;

TextRenderer* Text;

glm::vec2 LocalMouse, smallMouse, lerpPlayerPos;
std::vector<tile*> tiles;
std::vector<actor*> perf;
std::vector<performer*> AI;
performer* player;
std::vector<actor*> all;
std::vector<actor*> OnScreen;
std::vector<region*> Regions, Nearby;
std::vector < Texture2D> tileTextures;
std::unique_ptr< GLSLProgram> m_program = nullptr;
std::unique_ptr< GLSLProgram> l_program = nullptr;

level First;
std::unique_ptr < Grid> Area;
glm::mat4 ortho;
glm::mat4 projection;


float Lerp(float a, float b, float t)
{
	return (1.0f - t) * a + t * b;
}

/*glm::vec2 getQuadrant(glm::vec2 p) {
	return glm::vec2(0);
}*/
void createmap() {
	srand(time(0));
	auto Number_Of_Blob = GLOBAL_LEVEL_SIZE;
	auto cube = CELLSIZE;
	for (int q = 0; q < Number_Of_Blob; q++) {
		for (int e = 0; e < Number_Of_Blob; e++) {
			auto reg = new region(q * cube + 8, e * cube + 8);
			printf(" YO THERE IS A NEW PLACE TO LIVE IN");
			printf("X %d ", reg->pos.x); printf("Y %d \n", reg->pos.y);
			for (int z = 0; z < 1; z++)
				for (int x = 0; x < cube; x++)
				{

					for (int y = 0; y < cube; y++)
					{

						auto w = new tile(glm::vec2((x - y) * 50 + (q - e) * (cube * 50) + ORIGIN_POINT_X,
							ORIGIN_POINT_Y + (x + y) * 33.5f + (q + e) * (cube * 33.5f)), 5.0f, 0, glm::vec2(100, 100), ResourceManager::GetTexture("base"));

						w->Z = 300;
						all.push_back(w);
						reg->tiles.push_back(w);
						//	Area->addPrimitive(w);

					}
				}

			Regions.push_back(reg);
		}

	}

}
//Quickly load a texture
void t_q(str text, str id) {
	str s = "textures/" + text + ".png";
	ResourceManager::LoadTexture(s.c_str(), true, id);
}
performer* quickPerformer() {


	auto wq = new performer(glm::vec2(400 + rand() % 2000, rand() % 2000), glm::vec2(100, 134.6), ResourceManager::GetTexture("frag"), glm::vec3(.5, .5, 1));
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
	wq->Jump(1);
	int qeq = -49 + rand() % 50;
	int qwq = -49 + rand() % 50;


	wq->Move(glm::vec2(qeq, qwq), 1);
	AI.push_back(wq);
	return wq;
}
void setupPlayer() {


	player = new performer(glm::vec2(500, 500), glm::vec2(100, 134.6), ResourceManager::GetTexture("frag"));
	player->platZ = 0;
	player->Z = 500;
	player->zDepthOffset = 400;//old 90
	player->size = glm::vec2(100, 100);
	player->shadow = ResourceManager::GetTexture("shadow");

	animation idle;
	idle.addFrames(rsm GetTexture("q_pep_walk-1"));
	player->addAnimation(idle);

	animation forward;
	forward.addFrames(rsm GetTexture("q_pep_walk-1"));
	forward.addFrames(rsm GetTexture("q_pep_walk-2"), 1);
	forward.addFrames(rsm GetTexture("q_pep_walk-3"), 3);
	forward.addFrames(rsm GetTexture("q_pep_walk-2"), 1);
	forward.addFrames(rsm GetTexture("q_pep_walk-1"));
	forward.addFrames(rsm GetTexture("q_pep_walk-4"), 1);
	forward.addFrames(rsm GetTexture("q_pep_walk-5"), 3);
	forward.addFrames(rsm GetTexture("q_pep_walk-4"), 1);
	player->addAnimation(forward);

	animation idle_u;
	idle_u.addFrames(rsm GetTexture("q_pep_walk_u-1"));
	player->addAnimation(idle_u);

	animation backward;
	backward.addFrames(rsm GetTexture("q_pep_walk_u-1"));
	backward.addFrames(rsm GetTexture("q_pep_walk_u-2"), 1);
	backward.addFrames(rsm GetTexture("q_pep_walk_u-3"), 3);
	backward.addFrames(rsm GetTexture("q_pep_walk_u-2"), 1);
	backward.addFrames(rsm GetTexture("q_pep_walk_u-1"));
	backward.addFrames(rsm GetTexture("q_pep_walk_u-4"), 1);
	backward.addFrames(rsm GetTexture("q_pep_walk_u-5"), 3);
	backward.addFrames(rsm GetTexture("q_pep_walk_u-4"), 1);
	player->addAnimation(backward);

	animation jump_u;
	jump_u.addFrames(rsm GetTexture("q_pep_walk_u-3"));
	player->addAnimation(jump_u);

	animation jump;
	jump.addFrames(rsm GetTexture("q_pep_walk-3"));
	player->addAnimation(jump);
	perf.push_back(player);


}
void improvedTileCollision(actor * a) {

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
void setupArea() {

}
void CollideWithTiles(actor * a) {

	a->isOnGround = false;
	bool w = false;
	bool f = false;
	for (int i = 0; i < tiles.size(); i++)
	{
		auto cqq = a->DistanceFrom(tiles[i]);
		tiles[i]->alpha = 1 - cqq * 0.06f;
		if (tiles[i]->alpha < .5f)tiles[i]->alpha = .5f;
		if (cqq > cullingUpdate) {

			//tiles[i]->ZFloof = 9;
			//tiles[i]->alpha = 1 - cqq * 0.06f;
			//tiles[i]->alpha = .2f;
			continue;
		}

		bool l = tiles[i]->CollisionWithMe(a->localPos());
		//	bool q = tiles[i]->CollisionWithMe(smallMouse) && !f;
		if (l) {
			w = true;
			//tiles[i]->pos.y+=20;
			float b = tiles[i]->Z + tiles[i]->H;
			if (a->Z + 20 >= b)
				a->platZ = b;
		}
		/*if (ClickL && q) {
			tiles[i]->Z += 10;
			f = true;
		}*/

		bool boob = tiles[i]->CollisionWithMe(a);
		//tiles[i]->selected = boob;
	}

}
void Game::Init() {
	projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	Offset.x = 600;
	Offset.y = 800;
	Renderer = new SpriteRenderer(); //TODO delete, Obselete
	spriteBatch.Camera = glm::vec2(0);
	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("fonts/FredokaOne-Regular.ttf", 24);
	//Area = new Quadtree(0, glm::vec2(500, 500), glm::vec2(0, 0)); // Delete, Obselete
	loadTexture();



	//tileTextures.push_back(rsm GetTexture("big"));
	//Area = std::make_unique<Grid>(NUM_OF_CEL, NUM_OF_CEL, CELLSIZE);
	setupPlayer();
	player->quickStat(10, 3);
	First.init("dungeon/dungeon_prototype.png",Width,Height);
	First.enter(player);
	//createmap();
	spriteBatch.zoom = 1.5f;

	all.push_back(player);

	for (int i = 0; i < actorTest; i++)
	{
		all.push_back(quickPerformer());

	}

	lerpPlayerPos = player->pos;
	Renderer->tint = glm::vec3(0); //glm::vec3(-.3, -.3, .1);

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


	ortho = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

	//Area->addPrimitives(all);
}
void Game::Update(float dt) {
 
	player->Move(player->input_Dir, dt);

	for (size_t i = 0; i < AI.size(); i++)
	{
		auto o = player->localPos() - AI[i]->localPos();
		glm::normalize(o);
		auto q = player->DistanceFrom(AI[i]);
		auto t = glm::vec2(0);
		if (q > 4 && q < 100) {
		
			if (o.x > 0)t.x = 1;
			if (o.x < 0) t.x = -1;
			if (o.y > 0)t.y = 1;
			if (o.y < 0) t.y = -1;
			 
		}

		if (AI[i]->Z < 0)AI[i]->Jump(dt);

		AI[i]->Move(glm::vec2(t.x,t.y), dt);
	}
	lerpPlayerPos.x = Lerp(lerpPlayerPos.x, player->pos.x, .04f * spriteBatch.zoom);
	lerpPlayerPos.y = Lerp(lerpPlayerPos.y, player->pos.y, .04f * spriteBatch.zoom);
	spriteBatch.Camera = (-lerpPlayerPos)
		+ glm::vec2(Offset.y, Offset.x);

	if (Keys[GLFW_KEY_SPACE] && (player->isOnGround || player->Z <= 6))player->Jump(dt);
	if (Keys[GLFW_KEY_C])Offset.x--;

	First.update(dt);


	return;
	Area.get()->refresh(&perf);
	Area.get()->updateCollision();
	for (int i = 0; i < all.size(); i++)	all[i]->update(dt);


	return; // Old Method past that
	for (int i = 0; i < perf.size(); i++)
	{
		auto cur_act = perf[i];
		if (player->DistanceFrom(cur_act) > cullingRender * cullingRender - 10)continue;
		cur_act->isOnGround = false;
		for (int z = 0; z < Regions.size(); z++)
		{
			if (Regions[z]->Nearby(cur_act)) {

				for (int y = 0; y < Regions[z]->tiles.size(); y++)
				{
					Regions[z]->tiles[y]->preCollision(cur_act);
				}
			}
		}
		//CollideWithTiles(cur_act);
		for (int q = 0; q < perf.size(); q++)
			if (perf[i] != perf[q]) {
				perf[q]->CollisionWithMe(perf[i]);
				//perf[i]->CollisionWithMe(perf[q]); //Todo, just do one fucking call 
			}
	}
	OnScreen.insert(OnScreen.end(), perf.begin(), perf.end());
	if (player->DistanceFrom(lastPos) > 20) {

		Nearby.clear();
		for (int i = 0; i < Regions.size(); i++)
		{
			if (Regions[i]->Nearby(player)) {
				Nearby.push_back(Regions[i]);
			}
		}

		lastPos = player->localPos();
	}
	for (int i = 0; i < Nearby.size(); i++)
	{
		for (int y = 0; y < Nearby[i]->tiles.size(); y++)
		{
			if (player->DistanceFrom(Nearby[i]->tiles[y]) > cullingRender * cullingRender) continue;
			OnScreen.push_back(Nearby[i]->tiles[y]);

		}
	}
	for (int i = 0; i < OnScreen.size(); i++)
	{
		OnScreen[i]->update(dt);
	}

	OnScreen.clear();

}

void Game::ProcessInput(float dt) {


	LocalMouse.x = (mouseX - spriteBatch.Camera.x) / spriteBatch.zoom;
	LocalMouse.y = (mouseY - spriteBatch.Camera.y) / spriteBatch.zoom;
	glm::vec2 player_input_dir = glm::vec2(0, 0);
	

	/*if (Keys[GLFW_KEY_A])player->vel.x -= dt * INPUT_FRAME_ACCELERATION;
	if (Keys[GLFW_KEY_D])player->vel.x += dt * INPUT_FRAME_ACCELERATION;
	if (Keys[GLFW_KEY_W])player->vel.y -= dt * INPUT_FRAME_ACCELERATION;
	if (Keys[GLFW_KEY_S])player->vel.y += dt * INPUT_FRAME_ACCELERATION;*/
	if (Keys[GLFW_KEY_A])player_input_dir.x -= 1;
	if (Keys[GLFW_KEY_D])player_input_dir.x += 1;
	if (Keys[GLFW_KEY_W])player_input_dir.y -= 1;
	if (Keys[GLFW_KEY_S])player_input_dir.y += 1;

	player->setInputDir(player_input_dir);

	if (Keys[GLFW_KEY_X])player->zDepthOffset += 1;
	if (Keys[GLFW_KEY_Z])player->zDepthOffset -= 1;


	/*if (Keys[GLFW_KEY_UP])Renderer->Camera.y += 4;
	if (Keys[GLFW_KEY_DOWN])Renderer->Camera.y -= 4;
	if (Keys[GLFW_KEY_LEFT])Renderer->Camera.x += 4;
	if (Keys[GLFW_KEY_RIGHT])Renderer->Camera.x -= 4;*/

	if (abs(mouseScroll )>= 0)spriteBatch.zoom += (mouseScroll * dt * 10);
	 
	 
	mouseScroll = Lerp(mouseScroll, 0,.8f);


	if (spriteBatch.zoom <= .5f)spriteBatch.zoom = .5f;
	if (spriteBatch.zoom >= 2.5f)spriteBatch.zoom = 2.5f;


	//player->isOnGround = false;



}

int posx = 300, posy = 300;
float rot = 0;

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
	/*
		std::sort(all.begin(), all.end(), [](actor * a, actor * b)
		{ return ((a->pos.y + a->zDepthOffset + a->Z)
			< b->pos.y + b->zDepthOffset + b->Z
			); });

		for (int x = 0; x < perf.size(); x++)
		{
			perf[x]->Draw(*Renderer, false);
		}*/

		/*
				for (int i = 0; i < all.size(); i++)
				{
					if (player->DistanceFrom(all[i]) > cullingRender * cullingRender) {

						continue;
					}
					all[i]->Draw(*Renderer);

				}*/


				//player->Draw(*Renderer);

				/*	float xx = ((LocalMouse.y - -200) / isoH + (LocalMouse.x - 400) / isoW) / ratio;
					float yy = ((LocalMouse.y - -200) / isoH - (LocalMouse.x - 400) / isoW) / ratio;
					smallMouse.x = xx;
					smallMouse.y = yy;
					Text->RenderText("World", 5, 15, 1.0F);

					Text->RenderText("Mouse", 5, 90, 1.0F);
					Text->RenderText(std::to_string(xx), 90, 90, 1.0F);
					Text->RenderText(std::to_string(yy), 90, 120, 1.0F);
					Text->RenderText("zdepth", 5, 140, 1.0F);
					Text->RenderText(std::to_string(player->zDepthOffset), 90, 155, 1.0F);
					Text->RenderText("Relative Vel", 5, 190, 1.0F);
					auto relv = player->relativeVel();
					Text->RenderText(std::to_string(relv.x), 140, 190 + 40, 1.0F);
					Text->RenderText(std::to_string(relv.y), 140, 230 + 40, 1.0F);

					Text->RenderText("Direction", 5, 290, 1.0F);
					auto sss = player->Sight;
					Text->RenderText(std::to_string(sss.x), 140, 290 + 40, 1.0F);
					Text->RenderText(std::to_string(sss.y), 140, 320 + 40, 1.0F);
					std::string dirto;
					switch (player->Last_Direction) {
					case UP: dirto = "UP";
						break;
					case DOWN: dirto = "DOWN";
						break;
					case LEFT:dirto = "LEFT";
						break;
					case RIGHT:dirto = "RIGHT";
						break;
					case NORTH:dirto = "NORTH";
						break;
					case SOUTH:dirto = "SOUTH";
						break;
					case WEST:dirto = "WEST";
						break;
					case EAST:dirto = "EAST";
						break;
					}
					Text->RenderText(dirto, 140, 290, 1.0F);*/


}

void Game::Render(float dt) {



	First.render(&spriteBatch, m_program.get());
	debug(dt);

	/* LIGHT TEST //FAILED
	
	Light playerLight;
	playerLight.color = glm::vec4(1, 1, 1,.8);
	playerLight.position = player->pos;
	playerLight.size = 30.0f;

	l_program->use();
	auto m_cameraMatrix = glm::translate(ortho, glm::vec3(spriteBatch.Camera, 0));
	glm::vec3 scale(spriteBatch.zoom, spriteBatch.zoom, 0.0f); //x,y,z
	m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
	glUniformMatrix4fv(m_program->getUniformLocation("P"), 1, GL_FALSE, &m_cameraMatrix[0][0]);


	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	spriteBatch.begin();
	playerLight.draw(spriteBatch);
	spriteBatch.end();
	spriteBatch.renderBatch();
	l_program->unuse();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
;*/
	return;

	//OnScreen.insert(OnScreen.end(), perf.begin(), perf.end());
	OnScreen.push_back(player);
	for (size_t i = 1; i < perf.size(); i++)
	{
		bool e = player->DistanceFrom(perf[i]) > cullingRender * cullingRender;
		perf[i]->activeActor(!e);
		perf[i]->drawShadow(player);
		if(!e)OnScreen.push_back(perf[i]);
	}
	if (player->DistanceFrom(lastPos) > 50) {

		Nearby.clear();
		for (int i = 0; i < Regions.size(); i++)
		{
			if (Regions[i]->Nearby(player)) {
				Nearby.push_back(Regions[i]);
			}
		}

		lastPos = player->localPos();
	}
	for (int i = 0; i < Nearby.size(); i++)
	{
		for (int y = 0; y < Nearby[i]->tiles.size(); y++)
		{
			if (player->DistanceFrom(Nearby[i]->tiles[y]) > cullingRender * cullingRender) continue;
			 Nearby[i]->tiles[y]->shadow(player);
			OnScreen.push_back(Nearby[i]->tiles[y]);

		}
	}
 

	/*m_program->use();
	spriteBatch.begin(GlyphSortType::FRONT_TO_BACK);

	auto m_cameraMatrix = glm::translate(ortho, glm::vec3(spriteBatch.Camera, 0));

	glm::vec3 scale(spriteBatch.zoom, spriteBatch.zoom, 0.0f); //x,y,z
	m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;



	glUniform1i(m_program->getUniformLocation("mySampler"), 0);
	glUniformMatrix4fv(m_program->getUniformLocation("P"), 1, GL_FALSE, &m_cameraMatrix[0][0]);*/


	for (int i = 0; i < OnScreen.size(); i++) {

		if (player->DistanceFrom(OnScreen[i]) > cullingRender * cullingRender) continue;
		OnScreen[i]->Draw(spriteBatch);
	}
	spriteBatch.end();
	spriteBatch.renderBatch();
	m_program->unuse();
	OnScreen.clear();

	debug(dt);
	Text->RenderText("offset", 5, 35 + 60, 1.0F);
	Text->RenderText(std::to_string((int)Offset.x), 90, 34 + 60, 1.0F);
	Text->RenderText(std::to_string((int)Offset.y), 90, 60 + 60, 1.0F);
	lastTime = dt;
}
