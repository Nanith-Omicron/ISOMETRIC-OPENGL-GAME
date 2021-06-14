#include "glm/glm.hpp"
#include "SpriteBatch.h"
#include "global.h"


class Light {
public:
	void draw(SpriteBatch& spriteBatch) {
		glm::vec4 destRect;
		// The position of the box is actually the center of the box not the corner of the box
		destRect.x = position.x; //- (size / 2.0f);
		destRect.y = position.y; //- (size / 2.0f);
	
		destRect.z = TILE_FLOOR.x  * size;
		destRect.w = TILE_FLOOR.y   * size;
		spriteBatch.draw(destRect, glm::vec4(-1, -1, 2, 2.0f), 0, 0.0f, color);
	}

	glm::vec4 color;
	glm::vec2 position;
	float size;
};