#include "performer.h"


void NRJ_FX::update(performer* p, float dt)
{
 	p->fxColors =mainEffect.Effect(p->color, dt);
	if(p->NRJ < p->MaxNRJ)
	_timer += dt * 10;
	if (_timer > GiveNRJat )
	{	
		if (p->NRJ > p->MaxNRJ)p->NRJ = p->MaxNRJ;		
		_timer = 0; p->NRJ++;
		mainEffect.reset();
 
	}
	p_fx::update(p, dt);
}


void NRJ_FX::OnReceived(performer* p)
{
	if (timeLeft < 0)isInfinite = true;
	mainEffect.getOg(p->color);
	ID = p->Effects.size() - 1;
}

void p_fx::update(performer* p, float dt)
{
	if (!isInfinite)timeLeft -= dt;
 
	if (timeLeft <= 0 && !isInfinite) {
		OnExpired(p);
	}
}

void p_fx::OnReceived(performer* p)
{
	if (timeLeft < 0)isInfinite = true;
	mainEffect.getOg(p->color);
	ID = p->Effects.size() - 1;
}

void p_fx::OnExpired(performer* p)
{
	p->Effects.erase(p->Effects.begin() + ID);
}

void p_fx::OnHit(performer * p)
{

}

void p_fx::OnDeath(performer * p)
{
}
