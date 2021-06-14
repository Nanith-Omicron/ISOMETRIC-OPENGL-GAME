#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>


#define DEBUG_RECT false
//Rectangle-based Collision . An Performer can have multiple rect 
class actor;
class rect {

public:
	glm::vec2 postion, size;
	bool collision;
	rect();

	rect(glm::vec2 pos, glm::vec2 siz, actor* a = nullptr, bool collision = true);
	rect(glm::vec2 pos, glm::vec2 siz, void* so(rect a, rect b), actor* a = nullptr, bool collision = true);
	//In case we want more deffinition in our solver, otherwise, just use AABB
	void hasCollisionWith(rect b);
 
	//Events to fire up when entering , While colliding, and exiting the rect;
	void (*EventCollideEnter)(), (*EventCollide)(), (*EventCollideExit)();

	/*To compare against the previous frame. If this flipped, we just enter. if this is = to true & it do not change, we are still in collision.
	* While, if this flipped when = true, we exit.
	*This will served  when firing collision.
	*/
	bool isColliding = false;

};