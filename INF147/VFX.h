#include <texture.h>
#include "glm/glm.hpp"
#pragma once
struct VFX{

	float  _internalTime =1;
	float Speed = 5;
	glm::vec4 ToApply;
	glm::vec4 ogColor;
	VFX() {

	}
	VFX(glm::vec4 color, float s) {
		ToApply = color;
		Speed = s;
	}
	void getOg(glm::vec3 og) {
			ogColor = glm::vec4(og, 1);
		_internalTime = 1;
	}
	void reset() {
		_internalTime = 1;
	}
 
	virtual glm::vec3 Effect(glm::vec3  color, float dt) {
		
		_internalTime -= dt * 10 * Speed;
		 
		 
	 	if(_internalTime >= 0)
			return ToApply * _internalTime * 2.0f /*+ ogColor * ( 1.0f - _internalTime)*/;
		else {
			return glm::vec4(0,0,0, 1);;
		} 
		
	 
	}


};