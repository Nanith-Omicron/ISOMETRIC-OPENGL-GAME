#pragma once
#include "Primitive.h"
#include "tile.h"
#include <vector>
#include <item.h>

struct Cell {
	std::vector<actor*>peps;
	int x;
	int y;
};

class Grid {

public:
 
	Grid(int w, int h, int cs);
	~Grid();
	void addPrimitive(actor* p);
	void addPrimitives(std::vector<actor*>& p);
	void addPrimitive(actor* p, Cell* c);
	Cell* getCell(int x, int y);
	Cell* getCell(const glm::vec2& pos);
	void removePrimitiveFromCell(actor* p);
	void refresh(std::vector<actor*>* p);
	void refresh(std::vector<actor*>* p, actor* player);
	void refresh(std::vector<item*>* p, actor* player);
	std::vector<Cell> cells;
	int cellSize, width, height, numXCells, numYCells;
	void updateCollision();
	
	void checkCollision(actor* p, std::vector<actor*>& check, int ind);
};