#pragma once
#include <glad/glad.h>
#include "global.h"
#include <glm/glm.hpp>
#include "texture.h"
#include "spriteRenderer.h"
#include "rect.h"

struct Cell;
class Grid;
 
class primitive {

public:
	glm::vec2 pos;
	int ID;
	float Z = 0, H = 0;
	glm::vec2 collisionBoundXY = glm::vec2(.3f), collisionBoundZ = glm::vec2(7.5f, 37.5f);
	bool isAcollidee = true;
	Cell* currentCell = nullptr;
	int cind = -1;
	float platZ = 0;	float alpha = 1;
	primitive() {};
	primitive(int d, glm::vec2 p, float z, float h, glm::vec2 bdXY = glm::vec2(.5), glm::vec2 bdZ = glm::vec2(.5))
	{
		ID = d;
		pos = p;
		Z = z;
		H = h;
		collisionBoundXY = bdXY;
		collisionBoundZ = bdZ;
	}
	glm::vec2 localPos() {
		glm::vec2 lol;
		lol.x = ((pos.y - ORIGIN_POINT_Y) / isoH + (pos.x - ORIGIN_POINT_X) / isoW) / S_ratio;
		lol.y = ((pos.y - ORIGIN_POINT_Y) / isoH - (pos.x - ORIGIN_POINT_X) / isoW) / S_ratio;
		return lol;
	}

	virtual void preCollision(actor* a);
	virtual float DistanceFrom(primitive* a);
	virtual bool CollisionWithMe(primitive* a);
	virtual bool CollisionWithMe(glm::vec2 v);
	virtual void update(Grid* g, float dt);
	virtual void update(float dt);

};

