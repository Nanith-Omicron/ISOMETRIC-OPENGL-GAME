#pragma once
#include "performer.h"
#include <string>
 
class performer;
class p_fx {
public:
	int ID;
	Texture2D   tex;
	float timeLeft= -1;
	bool isInfinite = false;	
	std::string name;
	VFX mainEffect = VFX(glm::vec4(1,1,1,1),2);

	p_fx(Texture2D q) {
		tex = q;
	}
	virtual void update(performer* p, float dt);
	virtual void OnReceived(performer* p);
	virtual void OnExpired(performer* p);
	virtual void OnHit(performer* p);
	virtual void OnDeath(performer* p);

};
class NRJ_FX : public p_fx {
public:

	NRJ_FX(Texture2D  q) : p_fx(q) {
		tex = q;
	}
	VFX mainEffect = VFX(glm::vec4(1, .7f, 0, 1), 10);
	int Amount = 0;
	float _timer = 0, GiveNRJat = 1;
	virtual void OnReceived(performer* p);
	virtual void update(performer* p, float dt);
	
};