#include "rect.h"
#include "Physics.h"
#include "actor.h"
 
rect::rect() {

	this->postion = glm::vec2(0, 0);
	this->size = glm::vec2(1);
	
}
//Create a rect. Use the AABB solver in Physics.h
rect::rect(glm::vec2 pos, glm::vec2 siz, actor* a  , bool collision) {

	this->postion = pos;
	this->size = size;
	 
	//If there is an actor, bind to it 
	if (a)
		a->addCollider(this);

}
//Create a rect with a different Solver
/*rect::rect(glm::vec2 pos, glm::vec2 siz ,actor* a , bool collision ) {

	this->postion = pos;
	this->size = size;
	 
	//If there is an actor, bind to it 
	if (a)
		a->addCollider(this);

}*/

//Check if this rect has a collision with another rect.
void rect::hasCollisionWith(rect b) {
	AABB(*this, b);
}