#pragma once
#include "actor.h"
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include "P_fx.h"
#include "item.h"
struct frame {

	Texture2D tx;
	int repeat, w_flag;
	frame() {

	}
	frame(Texture2D f, int t = 1) {
		tx = f; repeat = t;
	}

};



//TODO addEvent To certain frame
struct animation {

private:
	int cur_Frame_Rep = 0;
public:
	std::vector<frame> frames;
	int currentFrame_ID = 0;
	bool flipX, flipY;
	bool playInverse = false;

	void addFrames(Texture2D t, int rep = 1) {
		auto w = frame(t, rep);
		frames.push_back(w);
		cur_Frame_Rep = frames[currentFrame_ID].repeat;

	}
	void reset_current_Frame() {
		currentFrame_ID = 0;
		cur_Frame_Rep = 0;
		if (frames.size() == 0) {
			throw std::invalid_argument("Imbecile. You forgot to give a frame");
		}
	}
	Texture2D currentFrame() {


		if (frames.size() == 1)return frames[currentFrame_ID].tx;
		if (currentFrame_ID >= frames.size())
		{
			currentFrame_ID = 0;
		}

		if (cur_Frame_Rep > 0)
		{

			cur_Frame_Rep--;
			return frames[currentFrame_ID].tx;
		}
		else {
			//Return the next animation and set the repeat var to next frame number of repeat




			auto xd = frames[currentFrame_ID];
			currentFrame_ID++;
			if (currentFrame_ID >= frames.size())currentFrame_ID = 0;
			cur_Frame_Rep = xd.repeat;
			return xd.tx;
		}

	}

};


class performer : public actor {


	float timer = 0;

public:

	performer();
	performer(glm::vec2 pos, glm::vec2 siz, Texture2D   spr, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), LAYER lay = PHYSICAL)
		:actor(pos, siz, spr)
	{

		spr_default = spr;
	};

	//Stats logic
	float HP = 10, Max_HP = 10;
	float jump_Delay = .02, jump_Timer = 0;
	float time_On_Ground;
	int NRJ = 3, MaxNRJ = 3;
	void quickStat(float hp, int nj) {
		Max_HP = hp;
		MaxNRJ = nj;
		HP = hp;
		NRJ = nj;

	}

	std::vector<animation> Animations;
	Texture2D  spr_default;
	glm::vec2 Sight;
	int frameRate = 100;
	glm::vec2 input_Dir;
	int cur_Animation_ID;
	Direction Last_Direction;
	bool animated = true;
	std::vector<p_fx*> Effects;
	std::vector<item*> Inventory;
	

	virtual void ApplyEffects(p_fx * ef) {
		ef->OnReceived(this);
		Effects.push_back(ef);
	}

	virtual void TakeDamage(float w) {
		HP -= w;
		for (size_t i = 0; i < Effects.size(); i++)
			Effects[i]->OnHit(this);

		if (HP < 0) {

			HP = 0;
			Death();
		}

	}
	virtual void Death() {
		for (size_t i = 0; i < Effects.size(); i++)
			Effects[i]->OnDeath(this);
		printf("Died");
	}
	virtual void Draw(SpriteBatch & renderer, bool selected);
	virtual void animate(float dt);
	virtual bool addAnimation(animation a);
	virtual bool ChangeAnimation(int x);
	virtual void Move(glm::vec2 v, float dt);
	virtual void Jump(float dt);
	virtual void update(float dt);
	virtual void update(Grid * g, float dt);
	virtual void onSide(actor* a);
	virtual void Drop(item* w);

	virtual  Direction getDirection();
	void setInputDir(glm::vec2 v);
};

