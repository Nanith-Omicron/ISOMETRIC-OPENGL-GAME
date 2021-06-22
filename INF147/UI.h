#pragma once
#include "glm/glm.hpp"
#include <texture.h>
#include <SpriteBatch.h>
#include <actor.h>


class UI {
public:
	glm::vec2 pos,offset;
	glm::vec4 col = glm::vec4(1);
	float scale = 3;
	
	Texture2D* img;
	void StickTo(actor * x);
	void setPos(float x, float y);
	bool show = true;
	virtual void  Draw(SpriteBatch& renderer, bool selected);
	 
};