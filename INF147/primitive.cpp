#pragma once
#include "primitive.h"
#include "Grid.h"

void primitive::preCollision(actor * a)
{
	//printf("Primitive san");

}

float primitive::DistanceFrom(primitive* a)
{
	return 0.0f;
}

bool primitive::CollisionWithMe(primitive* a)
{
	return false;
}

bool primitive::CollisionWithMe(glm::vec2 v)
{
	float x = this->localPos().x - .1f;
	float y = this->localPos().y - .1f;
	if (v.x > x - .5f && v.x < x + .5f)
		if (v.y > y - .5f && v.y < y + .5f)
			return true;

	return false;

	return false;
}

void primitive::update(Grid * g,float dt)
{
	/*
	 */

}

void primitive::update(float dt)
{
}
