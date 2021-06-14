#include "Grid.h"



Grid::Grid(int w, int h, int cs): width(w), height(h),cellSize(cs)
{
	numXCells = (int)ceil((float)width / cellSize);
	numYCells = (int)ceil((float)height/ cellSize);
	const int RESERV = 128;
	cells.resize(numXCells * numYCells);
	for (size_t i = 0; i < cells.size(); i++)
	{
		int x = i % numXCells;
		int y = i / numXCells;
		cells[i].peps.reserve(RESERV);
		cells[i].x = x;
		cells[i].y = y;
	}

}

Grid::~Grid()
{
}

  
void Grid::addPrimitive(actor* p)
{
	Cell* cell = getCell(p->localPos());
	cell->peps.push_back(p);
	p->currentCell = cell;
	p->cind = cell->peps.size() - 1;



}


void Grid::addPrimitives(std::vector<actor*>& p)
{

	for (size_t i = 0; i < p.size(); i++)
	{
		auto w = p[i];
		auto r = w->localPos();
	/*	r.x += CELLSIZE;
		r.y += CELLSIZE;*/
		Cell* cell = getCell(r);
	
		cell->peps.push_back(w);
		w->currentCell = cell;
		w->cind = cell->peps.size() - 1;
	}

}

void Grid::addPrimitive(actor* p, Cell *c)
{
	
	c->peps.push_back(p);
	p->currentCell = c;
	p->cind = c->peps.size() - 1;
}

Cell* Grid::getCell(int x, int y)
{
	if (x < 0)x = 0;
	if (x >= numXCells)x = numXCells -1;
	if (y < 0)y = 0;
	if (y >= numYCells)y = numYCells -1;

	return &cells[y * numXCells +x];
}

Cell* Grid::getCell(const glm::vec2& pos)
{
	int cx = (int)(pos.x / cellSize);
	int cy = (int)(pos.y / cellSize);
	return getCell(cx,cy);
}

void Grid::removePrimitiveFromCell(actor* p)
{
	std::vector<actor*>& peps = p->currentCell->peps;
	//if (!&peps)return;
	peps[p->cind] = peps.back();
	peps.pop_back();
	if (p->cind < (int)peps.size()) {
		peps[p->cind]->cind = p->cind;
	}
	p->cind= -1;
	p->currentCell = nullptr;

}

void Grid::refresh(std::vector<actor*>* p)
{
	for (size_t i = 0; i < p->size(); i++)
	{
		(*p)[i]->isOnGround = false;
		auto lwq = (*p)[i]->localPos();
		lwq.x += CELLSIZE;
		lwq.y += CELLSIZE;
		Cell* newCell = getCell(lwq);
		if (newCell != (*p)[i]->currentCell) {
			removePrimitiveFromCell((*p)[i]);
			addPrimitive((*p)[i], newCell);
		}
	}


}

void Grid::refresh(std::vector<actor*>* p, actor * player)
{


	player->isOnGround = false;
	auto ewe = player->localPos();
	ewe.x += CELLSIZE;
	ewe.y += CELLSIZE;
	Cell* newCell = getCell(ewe);

	if (newCell != player->currentCell) {
		removePrimitiveFromCell(player);
		addPrimitive(player, newCell);
	}
	for (size_t i = 0; i < p->size(); i++)
	{
		(*p)[i]->isOnGround = false;
		auto lwq = (*p)[i]->localPos();
		lwq.x += CELLSIZE;
		lwq.y += CELLSIZE;
		Cell* newCell = getCell(lwq);
		if (newCell != (*p)[i]->currentCell) {
			removePrimitiveFromCell((*p)[i]);
			addPrimitive((*p)[i], newCell);
		}
	}



}

void Grid::refresh(std::vector<item*>* p, actor* player)
{


	player->isOnGround = false;
	auto ewe = player->localPos();
	ewe.x += CELLSIZE;
	ewe.y += CELLSIZE;
	Cell* newCell = getCell(ewe);

	if (newCell != player->currentCell) {
		removePrimitiveFromCell(player);
		addPrimitive(player, newCell);
	}
	for (size_t i = 0; i < p->size(); i++)
	{
		(*p)[i]->isOnGround = false;
		auto lwq = (*p)[i]->localPos();
		lwq.x += CELLSIZE;
		lwq.y += CELLSIZE;
		Cell* newCell = getCell(lwq);
		if (newCell != (*p)[i]->currentCell) {
			removePrimitiveFromCell((*p)[i]);
			addPrimitive((*p)[i], newCell);
		}
	}



}


void Grid::updateCollision()
{
	


	
	for (int i = 0; i < cells.size(); ++i)
	{
		int x = i % numXCells; 
		int y = i / numXCells; 
		Cell& cc = cells[i];
		for (int j = 0; j < cc.peps.size(); ++j)
		{
			actor* p = cc.peps[j];
			if (!p->isAcollidee)continue;

			checkCollision(p, cc.peps, j + 1);
		 	if (x > 0) {
				checkCollision(p, getCell(x - 1, y )->peps, 0);
				if(y >0)checkCollision(p, getCell(x - 1, y - 1)->peps, 0);
				if(y < numYCells -1)
					if (y > 0)checkCollision(p, getCell(x - 1, y + 1)->peps, 0);

			}
			if(y > 0)checkCollision(p, getCell(x, y - 1)->peps, 0);
			 
		}
	}





}

void Grid::checkCollision(actor* p, std::vector<actor*>& check, int ind)
{
 
	for (size_t i = ind	; i < check.size(); i++)
	{
	 
		check[i]->preCollision(p);

	}
}
