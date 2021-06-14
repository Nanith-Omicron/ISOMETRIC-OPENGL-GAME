#pragma once
#include "ressourceManager.hpp"
#include "spriteRenderer.h"
#include "textrenderer.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{

public:

	// game state

	GameState    State;
	bool         Keys[1024];
	bool ClickR, ClickL;
	unsigned int Width, Height;
	float mouseX, mouseY, mouseScroll;
	float lastTime = 0;
	float UpdateTimer = 0, renderTimer = 0;
	glm::vec2 lastPos = glm::vec2(-999,999);
	
	glm::vec2 Offset;
	// constructor/destructor
	Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {


	}
	~Game() {


	}
	// initialize game state (load all shaders/textures/levels)
	void Init();
	// game loop
	void ProcessInput(float dt);
	void Update(float dt);
	void Render(float dt);
};
