#pragma once


#include "shader.h"
#include "texture.h"
#include <vector>
/*
struct Vertex {

	glm::vec2 Pos = { 0,0 };
	glm::vec2 col = { 0,0 };
	glm::vec2 tex = { 0,0 };
	float ID= 0;
	
};
static std::array<Vertex, 4> CreateQuad(float x, float y, float ID) {
	float size = 1.0f;
	Vertex v0;
	v0.Pos = { x,y };
	v0.col = { 1,1 };
	v0.tex = { 0,0 };
	v0.ID = ID;
	Vertex v1;
	v1.Pos = { x + size,y };
	v1.col = { 1,1 };
	v1.tex = { 1,0 };
	v1.ID = ID;
	Vertex v2;
	v2.Pos = { x+ size,y+ size };
	v2.col = { 1,1 };
	v2.tex = { 1,1 };
	v2.ID = ID;
	Vertex v3;
	v3.Pos = { x,y + size };
	v3.col = { 1,1 };
	v3.tex = { 0,1 };
	v3.ID = ID;
	return { v0,v1,v2,v3 };
}
*/
class SpriteRenderer
{
public:
	SpriteRenderer(Shader& shader);
	SpriteRenderer();

	
	int numberOfCall = 0;
	~SpriteRenderer();
	glm::vec3 tint = glm::vec3(0);
	std::vector<Texture2D* > Tiles;
	void BatchDrawSprite(Texture2D& tex, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);
	void useShader();
	void DrawSprite(Texture2D& texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));
private:
	Shader       shader;
	unsigned int quadVAO;

	void initRenderData();
};