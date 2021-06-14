#pragma once
 

 
#include "Vertex.h"
#include <vector>
#include <algorithm>
#include "Game.h"
enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};
class Glyph {
public:
	 Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const glm::vec4& color, float angle);
	
	 Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, glm::vec4& color);

	GLuint texture;
	float depth;
	Vertex tL, bL, tR, bR;

private:
	glm::vec2 rotatePoint(glm::vec2 pos, float angle);
};
class RenderBatch {
public:
	RenderBatch(GLuint of, GLuint Nv, GLuint tex) : offset(of), numVertices(Nv), texture(tex) {

	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;

};
class SpriteBatch {
public: 
	SpriteBatch();
	~SpriteBatch();
	void init(); 
	
	void begin(GlyphSortType sT = GlyphSortType::TEXTURE);  void end();
	void dispose();

	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture,float depth,  glm::vec4 color );
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, glm::vec4 color, float angle);
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth,  glm::vec4 color, const glm::vec2& dir);
	void renderBatch();
	float zoom = 1.5f;
	glm::vec2 Camera = glm::vec2(0);
 
private:

	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();
	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);
	GLuint _vbo;
	GLuint _vao;
	GlyphSortType _sortType;
	std::vector<Glyph*> _glyphs;
	std::vector<Glyph> _actualGlyphs;
	std::vector<RenderBatch> _renderBatches;



};