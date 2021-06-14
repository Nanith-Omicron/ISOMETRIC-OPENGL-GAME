#pragma once
#include "tile.h"

void tile::preCollision(actor* a) {
	
 
	auto cqq = a->DistanceFrom(this);

	/*alpha = 1 - cqq * 0.03f;
	if (alpha < .5f)alpha = .5f;*/
	float b = Z + H;
	if (a->Z + 20 >= b)a->platZ = b;
	if (cqq > cullingUpdate * cullingUpdate)return;
	
	if (cqq > .75f)return;		//Size of Tile is 1


	CollisionWithMe(a);

}
float tile::shadow(actor* a) {

 
	auto cqq = a->DistanceFrom(this);
	alpha = 1.125 - ((cqq +45) * 0.016);//0.014
 

	return cqq;
}
bool tile::CollisionWithMe(actor * a) {
	float localx = this->localPos().x;
	float localy = this->localPos().y;
	glm::vec2 act_pos = a->localPos();
	float act_z = a->Z;
	glm::vec2 act_bound = a->collisionBoundXY;
	bool grd = false;
	//To fired off events. We do not take the Actual size in count. 
	if (act_pos.x > localx - 1 && act_pos.x < localx + 1)
		if (act_pos.y > localy - 1 && act_pos.y < localy + 1)
			//40
			if (this->Z + 25 > act_z && this->Z < act_z + 30) {
				onTop(a);
				if (this->Z > act_z && this->Z < act_z + 1)
					if (a->vel.z < 0 || (a->Z + a->vel.z) < Z)a->vel.z = 0;

				if ((act_z + a->vel.z) < Z)act_z = 0;

				grd = true;
				a->Z = Z + 2;
				//if(!a->isOnGround && a->vel.z < 1)a->vel.z = 15;




			}

	//Collision Side
	if (act_pos.x + act_bound.x > localx - this->collisionBoundXY.x &&
		act_pos.x - act_bound.x < localx + this->collisionBoundXY.x) {
		if (act_pos.y + act_bound.y > localy - this->collisionBoundXY.y &&
			act_pos.y - act_bound.y < localy + this->collisionBoundXY.y) {

			if (this->Z + collisionBoundZ.x > act_z - a->collisionBoundXY.x
				&& this->Z - collisionBoundZ.y < act_z + a->collisionBoundZ.y) {

				if (Z > act_z) {
					a->Z = act_z - 1;
					a->vel.z = 0;
					onBottom(a);
				}
				//x 10 y -30 for Tweaking reason.
				if (this->Z + collisionBoundZ.x > act_z - a->collisionBoundXY.x + 10
					&& this->Z - collisionBoundZ.y < act_z + a->collisionBoundZ.y - 30) {
					auto vec = (act_pos - localPos());

					if (vec.length() > 0)vec /= vec.length();


					float aBoundx = a->collisionBoundXY.x + collisionBoundXY.x;
					float aBoundy = a->collisionBoundXY.y + collisionBoundXY.y;
					if (abs(vec.y) < abs(vec.x)) {
						if (act_pos.x > localx)act_pos.x = localx + aBoundx;
						if (act_pos.x < localx)act_pos.x = localx - aBoundx;
					}
					else {
						if (act_pos.y > localy)act_pos.y = localy + aBoundy;
						if (act_pos.y < localy)act_pos.y = localy - aBoundy;
					}

					a->setlocalPos(act_pos.x, act_pos.y);
					vec *= .09f;
					onSide(a);
					a->localVel(vec.x, vec.y);
					return true;
				}
				return true;
			}
		}
	}



	return false;
}



void tile::onTop(actor * a) {
	ZFloof = 12.0f;
	a->isOnGround = true;
}
void tile::onSide(actor * a) {

}
void tile::update(float td) {

 
	zDepthOffset = Z + 50;
	if (ZFloof > 0) {
		ZFloof -= td * 900;//70
	}
	else {
		ZFloof = 0;
	}
	if (alpha <= 1) {
		alpha += td  ;
	 
	}
}

bool tile::CollisionWithMe(glm::vec2 v) {


	float x = this->localPos().x - .1f;
	float y = this->localPos().y - .1f;
	if (v.x > x - .5f && v.x < x + .5f)
		if (v.y > y - .5f && v.y < y + .5f)
			return true;

	return false;
}

void tile::update(Grid* g, float dt)
{ 


}

float tile::drawShadow(actor* a)
{
	return  actor::drawShadow(a);
}


void  tile::Draw(SpriteBatch & renderer, bool selected) {
	if (!&img)return;
	glm::vec3 c = this->color;
	glm::vec2 p = this->pos;
	float qw = 1;
	p.y -= (Z - ZFloof);
	if (GHOSTLY)c * .3f;
	if (invisibleByProximity && alpha != 0 && !alwaysProximityVisible)qw = 3.7f - 4 * alpha ;
	if (qw < .4)qw = 0;
	if (selected || this->selected) {/* p.y += 20;*/ c *= 0.3f; }
 	if (justInvisible)qw = 0;
	//renderer.DrawSprite(this->img, p, this->size, this->GlobalRotation, glm::vec4(c.x, c.y, c.z, alpha) * alpha);
	renderer.draw(glm::vec4(p.x, p.y,
		size.x, size.y),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		img.ID,pos.y+ zDepthOffset + Z, glm::vec4(c * alpha, qw));
}