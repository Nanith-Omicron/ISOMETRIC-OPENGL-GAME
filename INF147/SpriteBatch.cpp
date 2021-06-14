#include "SpriteBatch.h"

Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, glm::vec4& color) :
	texture(Texture),
	depth(Depth) {
	// z represents width and w represents height
	tL.col = color;
	tL.setPosition(destRect.x, destRect.y + destRect.w);
	tL.setUv(uvRect.x, uvRect.y + uvRect.w);
	bL.col= color;
	bL.setPosition(destRect.x, destRect.y);
	bL.setUv(uvRect.x, uvRect.y);
	bR.col = color;
	bR.setPosition(destRect.x + destRect.z, destRect.y);
	bR.setUv(uvRect.x + uvRect.z, uvRect.y);
	tR.col = color;
	tR.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	tR.setUv(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}





Glyph::Glyph(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint Texture, float Depth, const glm::vec4& color, float angle) :
	texture(Texture),
	depth(Depth) {


	glm::vec2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);
	glm::vec2 tl(-halfDims.x, halfDims.y); // tl = topleft
	glm::vec2 bl(-halfDims.x, -halfDims.y); // bl = bottomleft
	glm::vec2 br(halfDims.x, -halfDims.y); // br = bottomright
	glm::vec2 tr(halfDims.x, halfDims.y); // tr = topright

	tl = rotatePoint(tl, angle) + halfDims;
	bl = rotatePoint(bl, angle) + halfDims;
	br = rotatePoint(br, angle) + halfDims;
	tr = rotatePoint(tr, angle) + halfDims;


	// z represents width and w represents height
	tL.col = color;
	tL.setPosition(destRect.x + tl.x, destRect.y + destRect.w + tl.y);
	tL.setUv(uvRect.x, uvRect.y + uvRect.w);
	bL.col = color;
	bL.setPosition(destRect.x + bl.x, destRect.y + bl.y);
	bL.setUv(uvRect.x, uvRect.y);
	bR.col = color;
	bR.setPosition(destRect.x + br.x, destRect.y + br.y);
	bR.setUv(uvRect.x + uvRect.z, uvRect.y);
	tR.col = color;
	tR.setPosition(destRect.x + tr.x, destRect.y + tr.y);
	tR.setUv(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

 
  
 
}





glm::vec2 Glyph::rotatePoint(glm::vec2 pos, float angle) {

	glm::vec2 newv; // new vector
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;

}


SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::dispose() {
	 if (_vao != 0) {
		glDeleteVertexArrays(1, &_vao);
		_vao = 0;
	}
	if (_vbo != 0) {
		glDeleteBuffers(1, &_vbo);
		_vbo = 0;
	} 
}
void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sT)
{
	_sortType = sT;
	_renderBatches.clear();
	_actualGlyphs.clear();
}

void SpriteBatch::end()
{
	_glyphs.resize(_actualGlyphs.size());
	for (size_t i = 0; i < _actualGlyphs.size(); ++i) {
		_glyphs[i] = &_actualGlyphs[i];
	}
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, glm::vec4 color)
{
	auto e = destRect + glm::vec4(  -destRect.z/2  ,  -destRect.w / 2, 0, 0) ;
 
	_actualGlyphs.emplace_back(e, uvRect, texture, depth, color);
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth,  glm::vec4 color, float angle)
{

	_actualGlyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth,  glm::vec4 color, const glm::vec2& dir)
{
	const glm::vec2 right(1.0f, 0.0f);
	float angle = acos(glm::dot(right, dir)); // will always be a positive angle
	if (dir.y < 0.0f) angle = -angle;

	_actualGlyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(_vao);
	for (int i = 0; i < _renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}
	glBindVertexArray(0);

}

void SpriteBatch::createRenderBatches()
{
	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);
	if (_glyphs.empty()) {
		return;
	}
	int offset = 0;
	int cv = 0;
	_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
	vertices[cv++] = _glyphs[0]->tL;
	vertices[cv++] = _glyphs[0]->bL;
	vertices[cv++] = _glyphs[0]->bR;
	vertices[cv++] = _glyphs[0]->bR;
	vertices[cv++] = _glyphs[0]->tR;
	vertices[cv++] = _glyphs[0]->tL;
	offset += 6;
	for (int cg = 1; cg < _glyphs.size(); cg++)
	{
		if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture) {
			_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
		}
		else {
			_renderBatches.back().numVertices += 6;
		}

		vertices[cv++] = _glyphs[cg]->tL;
		vertices[cv++] = _glyphs[cg]->bL;
		vertices[cv++] = _glyphs[cg]->bR;
		vertices[cv++] = _glyphs[cg]->bR;
		vertices[cv++] = _glyphs[cg]->tR;
		vertices[cv++] = _glyphs[cg]->tL;

		offset += 6;

	}
	glBindBuffer(GL_ARRAY_BUFFER,_vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr,GL_DYNAMIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void SpriteBatch::createVertexArray()
{

	if (_vao == 0)glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	if (_vbo == 0)glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	
	glBindVertexArray(0);



}

void SpriteBatch::sortGlyphs()
{
	switch (_sortType) {
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
		break;

	}


}

bool SpriteBatch::compareFrontToBack(Glyph * a, Glyph * b)
{
	return(a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph * a, Glyph * b)
{
	return(a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph * a, Glyph * b)
{
	return (a->texture < b->texture);
}
