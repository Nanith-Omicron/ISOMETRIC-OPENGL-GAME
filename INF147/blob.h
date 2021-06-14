#pragma once
#include "tile.h"
#include <vector>
class region {
public:
	glm::vec2 pos;
	std::vector<tile*> tiles;
	region(int x, int y) {
		pos = glm::vec2(x , y );
	}
	bool Nearby(actor* a) {

		glm::vec2 q = (a->localPos() -pos);

		return (q.x * q.x + q.y * q.y) < 600; //500

	}

};
