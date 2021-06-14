#pragma once
#include "actor.h"

class tile : public actor {
public:
	tile() :actor() {};
	float Z = 0.5f, H = .5f;
	float ZFloof = 0;
	float alpha = 1;
	int ID_X, ID_Y, ID_Z;
	 
	
	tile(glm::vec2 pos, float hx, float zx, glm::vec2 siz, Texture2D spr, glm::vec3 color = glm::vec3(1.0f), glm::vec3 velocity = glm::vec3(0.0f), LAYER lay = PHYSICAL) :actor(pos, siz, spr, color = glm::vec3(1.0f), velocity = glm::vec3(0.0f), lay = PHYSICAL) 
	{
		 Z = zx;
		 H = hx;
		 zDepthOffset = H * 10;
		 this->collisionBoundXY = glm::vec2(DEFAULT_COLLISION_BOUND_XY);
		 this->collisionBoundZ = glm::vec2(0, 75 * H/5);
		 isAcollidee = false;
	};

	bool selected = false;
	virtual void Draw(SpriteBatch& renderer, bool selected = false);
	virtual void preCollision(actor* a);
	float shadow(actor* a);
 
	virtual bool CollisionWithMe(actor * a);
	virtual bool CollisionWithMe(glm::vec2 v);
	virtual void update(Grid* g, float dt);
	virtual float drawShadow(actor* a);
	virtual void update(float dt);
	virtual void onTop(actor* a);
	virtual void onSide(actor* a);
};