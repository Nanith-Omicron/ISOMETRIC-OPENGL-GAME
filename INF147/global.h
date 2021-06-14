#pragma once
#include "glm/glm.hpp"
#define isoW 50.0f
#define isoH 33.5f
 
#define ratio 2.0f
#define ORIGIN_POINT_X 400
#define ORIGIN_POINT_Y -200
#define INPUT_FRAME_ACCELERATION 100
#define DEFAULT_COLLISION_BOUND_XY 0.50f
#define actorTest 0 // Limit for 90 fps at 100 block : 70
#define cullingRender 13 // 8 for pretty effect // 20 = whole screen
#define cullingUpdate 8  // 12 for pretty effect
#define CELLSIZE  4    //5
#define NUM_OF_CEL 100   //100
#define GLOBAL_LEVEL_SIZE  15  //15

#define TILE_BIG glm::vec2(100, 130)
#define TILE_FLOOR  glm::vec2(100, 70)
#define TILE_NORMAL glm::vec2(100, 100)
#ifndef Camera
 
#endif // ! Camera

#ifndef  zoom

#endif // ! zoom



//glm::vec2(100, 134.6)