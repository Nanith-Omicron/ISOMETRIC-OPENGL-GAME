#pragma once
#include <glm/glm.hpp>


 



struct Vertex {

	glm::vec2 pos;
	glm::vec4 col;
	glm::vec2 uv;
	void setPosition(float x, float y) {
		pos.x = x;
		pos.y = y;
	}
	void setColor(float r, float g, float b, float a) {
		col.r = r;
		col.g = g;
		col.b = b;
		col.a = a;
	}

	void setUv(float u, float v) {
		uv.x = u;
		uv.y = v;
	}


};
