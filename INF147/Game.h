#pragma once
#include "ressourceManager.hpp"
#include "spriteRenderer.h"
#include "textrenderer.h"
#include "Mouse_Info.h"
 
 
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_EDITOR
};

class Game
{

public:
	 
	GameState    State;
	bool         Keys[1024];
	Mouse_info  Cursor;
	unsigned int Width, Height;
	void (*Quit)();
	void (*TestLoad)();
  
	
	glm::vec2 Offset;


	// constructor/destructor
	Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

		 
	}
	~Game() {


	}
	void loadTestLevel();
 
	//Initialize game state (load all shaders/textures/levels)
	void Init();
	//ProcessInput run each clock, before update
	void ProcessInput(float dt);
	//Update run each clock
	void Update(float dt);
	//Render run each clock, after update
	void Render(float dt);
	
	void FetchDirectory();

	void openPage(int i, GameState w);
};
