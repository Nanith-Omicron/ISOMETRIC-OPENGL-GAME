#pragma once
#include "performer.h"
#include "Grid.h"
#include <algorithm>

void performer::Draw(SpriteBatch& renderer, bool selected) {

	actor::Draw(renderer, selected);
}
void performer::update(float dt) {
	for (size_t i = 0; i < Effects.size(); i++)
		Effects[i]->update(this,dt);
	
	if (isOnGround)	time_On_Ground += dt;
	else time_On_Ground = 0;

	jump_Timer += dt;
	if (NRJ < 0)NRJ = 0; if (NRJ > MaxNRJ)NRJ = MaxNRJ;
	if (HP < 0)HP = 0;  if (HP > Max_HP)HP = Max_HP;
	animate(dt);
	actor::update(dt);
}
void performer::update(Grid *g, float dt) {


	animate(dt);
	actor::update(dt);
}
void performer::onSide(actor* a)
{
	
	
	item* w =dynamic_cast<item*> (a);
	
	if (!w)return;
 
	printf(w->name.c_str());
	printf(" is in the pocket :smirk:\n");
	w->owner = a;
	w->CullByProximity = false;
	w->renderMe = false;
	w->collideWithMe = false;
	w->isAcollidee = false;
	Inventory.push_back(w);
	 


}
void performer::Drop(item* w)
{
	Inventory.erase(std::remove(Inventory.begin(), Inventory.end(), w), Inventory.end());
}


Direction performer::getDirection()
{
	if (Sight.x == 1 && Sight.y == 0)
		return NORTH;
	if (Sight.x == -1 && Sight.y == 0)
		return SOUTH;
	if (Sight.x == -.5 && Sight.y == .5)
		return DOWN;
	if (Sight.x == .5 && Sight.y == -.5)
		return UP;
	if (Sight.x == .5 && Sight.y == .5)
		return RIGHT;
	if (Sight.x == -.5 && Sight.y == -.5)
		return LEFT;
	if (Sight.x == 0 && Sight.y == 1)
		return EAST;
	if (Sight.x == 0 && Sight.y == -1)
		return WEST;
	return Last_Direction;

}
//TODO, USELESS
void performer::setInputDir(glm::vec2 v)
{
	input_Dir = v;
}
void performer::animate(float dt)
{
	if (!animated || Animations.size() <= 0)return;
	if (frameRate < 0)frameRate = 1;
	
	float f = 0.07f / (frameRate );

	timer += dt;
	if (timer > f) {
		timer = 0;
		img = Animations[cur_Animation_ID].currentFrame();
	}
}


bool performer::addAnimation(animation a)
{
	Animations.push_back(a);
	return false;
}
//Change the animation. Return TRUE if animation has changed.
bool performer::ChangeAnimation(int x)
{
	this->cur_Animation_ID = x;
	Animations[cur_Animation_ID].reset_current_Frame();
	return true;
}
Direction testDir;


void performer::Move(glm::vec2 v, float dt)
{
	 Sight.x = (v.x - v.y) / 2;
	 Sight.y = (v.x + v.y) / 2;

	bool isZero = Sight.y == 0 && Sight.x == 0;
	Direction dir = getDirection();
	vel += glm::vec3(v * speed, 0);

	ChangeAnimation(0);

	if (Last_Direction == NORTH || Last_Direction == UP || Last_Direction == WEST || Last_Direction == LEFT) { cur_Animation_ID = 2; }
 
	if (!isZero) {
		if (dir == NORTH || dir == UP) {

			FlipX = true;
			cur_Animation_ID = 3;
		}
		if (dir == WEST || dir == LEFT) {

			FlipX = false;
			cur_Animation_ID = 3;
		}
		if (dir == EAST || dir == RIGHT) {
			FlipX = false;
			cur_Animation_ID = 1;
		}
		if (dir == SOUTH || dir == DOWN) {
			FlipX = false;
			if (dir == SOUTH)FlipX = true;
			cur_Animation_ID = 1;
		}
	}
	if (!isOnGround) {
		cur_Animation_ID = 5;
		if (dir == NORTH || dir == UP || dir == WEST || dir == LEFT)
			cur_Animation_ID = 4;
	}

	Last_Direction = dir;
	testDir = dir;

}

void performer::Jump(float dt)
{
 
	 if (Z < -15) vel.z += 60;
	if (!isOnGround|| NRJ == 0 || jump_Timer < jump_Delay 
		|| time_On_Ground < .006) return;
	jump_Timer = 0;
	NRJ--;
	vel.z += 26;
}

