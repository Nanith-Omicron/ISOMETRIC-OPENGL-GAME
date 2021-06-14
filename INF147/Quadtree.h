#include <actor.h>
#include <vector>	
#include <memory>
#pragma once
class Quadtree {

	int max_Obj = 32;
	int max_level = 8;
	int level = 0;
	std::vector<actor*> objs;
	std::shared_ptr<Quadtree> nodes[4];
	glm::vec2 pos;
	glm::vec2 bounds;
	bool isEmpty() {
		return nodes[0]==nullptr;
	}
public:
	Quadtree();
	Quadtree(int l, glm::vec2 b, glm::vec2 p) {
		level = l;
		bounds = b;
		pos = p;


	}
	std::vector<actor*> canCollideWith(std::vector<actor*>& list, actor* a) {
		int ind = getIndex(a);
		if (ind != -1 && !isEmpty()) {
			nodes[ind]->canCollideWith(list, a);
		}
		list.insert(list.end(), objs.begin(), objs.end());
		return  list;

	}
	void clear() {
		objs.clear();
		for (int i = 0; i < 4; i++)
		{
			if (nodes[i] != nullptr) {
				nodes[i]->clear();
				nodes[i] = nullptr;
			}
		}

	}
	void insert(actor* a) {
		if (!isEmpty()) {
			int ind = getIndex(a);
			if (ind != -1)nodes[ind]->insert(a);
			return;
		}
		objs.push_back(a);

		if (objs.size() > max_Obj && level < max_level && isEmpty()) {
			 
				split();
			 

			auto  i = objs.begin();
			while (i != objs.end()) {

				int ind = getIndex(*i);
				if (ind != -1) {
					nodes[ind]->insert(*i);
					i = objs.erase(i);

				}
				else {
					++i;
				}


			}
			/*
			for (auto i = objs.begin(); i != objs.end(); ++i)
			{
				int ind = getIndex(*i);
				if (ind != -1) {
					auto w = *i;
					nodes[ind]->insert(w);
					objs.erase(i);
				}

			}*/

		}

	}
	void split() {
		float sw = bounds.x / 2;
		float sh = bounds.y / 2;
		nodes[0] = std::make_shared<Quadtree>(level + 1, glm::vec2(sw, sh), glm::vec2(pos.x + sw, pos.y));
		nodes[1] = std::make_shared<Quadtree>(level + 1, glm::vec2(sw, sh), glm::vec2(pos.x, pos.y));
		nodes[2] = std::make_shared<Quadtree>(level + 1, glm::vec2(sw, sh), glm::vec2(pos.x, pos.y + sh));
		nodes[3] = std::make_shared<Quadtree>(level + 1, glm::vec2(sw, sh), glm::vec2(pos.x + sw, pos.y + sh));
		 
	}
	int getIndex(actor * a) {
		int index = -1;
		float vmp = pos.x + bounds.x / 2;
		float hmp = pos.y + bounds.y / 2;
		glm::vec2 apos = a->localPos();
		bool tquad = apos.y < hmp && apos.y + a->collisionBoundXY.y < hmp;
		bool bquad = apos.y > hmp;

		if (apos.x < vmp && apos.x + a->collisionBoundXY.x < vmp) {
			if (tquad)index = 1;
			else if (bquad)index = 2;

		}
		else if (apos.x > vmp)
		{
			if (tquad)index = 0;
			else if (bquad)index = 3;
		}

		return index;
	}

};