#pragma once
#include "glm/glm.hpp"
#include <texture.h>
#include <SpriteBatch.h>
#include <actor.h>
#include "Mouse_Info.h"
#include "textrenderer.h"


class UI {
public:
	glm::vec2 pos,offset;
	glm::vec4 col = glm::vec4(1);
	float scale = 3;
	glm::vec2 centeredPos()
	{
		auto p = pos;
		p.x -= img.Width / 2;
		p.y -= img.Height / 2;
		return p;
	}

	
	Texture2D img;
	void StickTo(actor * x);
	void setPos(float x, float y);
	bool show = true;
	virtual void  Draw(SpriteBatch& renderer, bool selected);
	 
};