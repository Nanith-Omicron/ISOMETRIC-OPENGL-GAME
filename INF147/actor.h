#pragma once



#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "VFX.h"
 

#include <glad/glad.h>
#include "global.h"
#include <glm/glm.hpp>
#include "primitive.h"
#include "texture.h"
#include "spriteRenderer.h"
#include "rect.h"
#include "SpriteBatch.h"
#include <string>


enum LAYER {
	PHYSICAL,
	BACKGROUND,
	GHOSTLY

};
enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NORTH,
	SOUTH,
	WEST,
	EAST
};
 
class actor : public primitive {
public:

	glm::vec2 size= glm::vec2(1, 1);
	glm::vec3 color = glm::vec3(1,1,1), fxColors, vel;
	float speed = .5f;
	bool isOnGround = false;
	bool renderMe = true;
	bool collideWithMe = true;
	bool physicsMe = true;
	bool CullByProximity = true;
	bool invisibleByProximity = false;
	bool alwaysProximityVisible = false;
	float lastDistance;
	bool justInvisible = false;

	//Direction of an items


	///Move in a isometric view, Locally
	void localMove(float x, float y) {
		auto local = localPos();
		float xx = local.x + x;
		float yy = local.y + y;
		pos.x = ORIGIN_POINT_X + (xx - yy) * isoW;
		pos.y = ORIGIN_POINT_Y + (xx + yy) * isoH;
	}
	void setlocalPos(float x, float y) {
		pos.x = ORIGIN_POINT_X + (x - y) * isoW;
		pos.y = ORIGIN_POINT_Y + (x + y) * isoH;
	}
	void setlocalX(float y) {
		auto x = localPos().x;
		pos.x = (x - y) * isoW;
		pos.y = (x + y) * isoH;
	}
	void setlocalY(float x) {
		auto y = localPos().y;
		pos.x = (x - y) * isoW;
		pos.y = (x + y) * isoH;
	}
	void localVel(float y, float x) {
		vel.x -= (x - y) * isoW;
		vel.y += (x + y) * isoH;
	}
	bool isLowerThan(glm::vec2 lol) {
		glm::vec2 we = localPos();
		return    we.x <=  lol.x && we.y <= lol.y  ;
	}
	std::vector<VFX> VisualEffects;
	glm::vec2 relativeVel() {
		glm::vec2 lol;
		lol.x = ((vel.y) / isoH + (vel.x) / isoW) / ratio;
		lol.y = ((vel.y) / isoH - (vel.x) / isoW) / ratio;
		return lol;
	}
	bool operator<(const actor & x) const
	{
		return  pos.y < x.pos.y;
	}

	float Z = 0;
	float zDepthOffset = 0;
	float GlobalRotation;
	//Rotation of the object in isometric view;
	int LocalRotation = 0;
	bool toDiscard, FlipX;
	float total_ZLevel = 0;




	rect* rects;
	Texture2D img, shadow;
	LAYER layer;
	bool hasCollision() {
		return numCol >= 0;
	}
	int getNumCollider() {
		return numCol;
	}
	//TODO remove that
	//Actor do not have a collider by default. If they need more, we double the sizeOfCol.
	void addCollider(rect * r) {
		if (numCol >= sizeOfCol) {
			sizeOfCol *= 2;
			rects = new rect[sizeOfCol];
		}
		rects[numCol++] = *r;
	}
	actor() {

	}
	actor(glm::vec2 p, glm::vec2 siz, Texture2D spr, glm::vec3 col = glm::vec3(1.0f), glm::vec3 velocity = glm::vec3(0), LAYER lay = PHYSICAL)
		:primitive(0, pos, 0, 0) {
		img = spr;
		color = col;
		size = siz;
		pos = p;
		this->collisionBoundXY = glm::vec2(.3f);
		this->collisionBoundZ = glm::vec2(7.5f, 37.5f);
		isAcollidee = true;
	}
	virtual float DistanceFrom(actor * a); float DistanceFrom(glm::vec2 pos);
	virtual float drawShadow(actor * a);
	virtual void Draw(SpriteBatch & renderer, bool selected = false);
	virtual bool CollisionWithMe(glm::vec2 v);
	//Collision with an Actor,
	virtual bool CollisionWithMe(actor * a);
	virtual void update(float dt);
	virtual void update(Grid * g, float dt);
	virtual void onTop(actor * a);
	virtual void onSide(actor * a);
	virtual void onBottom(actor * a);
	virtual void preCollision(actor * a);
 
	void activeActor(bool t);
	virtual Direction getDirection();
	std::string name;
	std::string GetName() {

		return name;
	}
private:
	int numCol = 0;
	int sizeOfCol = 1;
};




#endif