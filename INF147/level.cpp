#include "level.h"
#include "NRJ_FX.h"



void level::createRoom(glm::vec2 there)
{



}
void level::createFloor(glm::vec2 there) {

	auto r = ResourceManager::GetTexture("dungeon_floor");
	int qw = rand() % 42;
	switch (qw)
	{
	case 0: case 8: case 9:
		r = ResourceManager::GetTexture("dungeon_floor_1");
		break;
	case 1:
		r = ResourceManager::GetTexture("dungeon_floor_2");
		break;
	case 2: case 15:
		r = ResourceManager::GetTexture("dungeon_floor_3");
		break;
	case 3:
		r = ResourceManager::GetTexture("dungeon_floor_4");
		break;
	case 4:
		r = ResourceManager::GetTexture("dungeon_floor_5");
		break;
	case 5: case 12: case 32:
		r = ResourceManager::GetTexture("dungeon_floor_6");
		break;
	default:
		r = ResourceManager::GetTexture("dungeon_floor");
		break;
	}
	int x = there.x;
	int y = there.y;
	auto w = new tile(glm::vec2((x - y) * 50 + ORIGIN_POINT_X,
		ORIGIN_POINT_Y + (x + y) * 33.5f),
		2.0f, 5, TILE_NORMAL, r);
	w->alwaysProximityVisible = true;
	w->ID_X = x;
	w->ID_Y = y;
	w->ID_Z = 0;
	all.push_back(w);
	Tiles.push_back(w);

}
void level::createWall(glm::vec2 there, bool black) {
	int x = there.x;
	int y = there.y;
	for (int i = 0; i < 2; i++)
	{

		auto w = new tile(glm::vec2((x - y) * 50 + ORIGIN_POINT_X,
			ORIGIN_POINT_Y + (x + y) * 33.5f),
			65.0f, i * 55 + 20, TILE_BIG, ResourceManager::GetTexture("dungeon_wall"));
		w->zDepthOffset += i * 20;
		if (black) {
			w->color = glm::vec3(0, 0, 0);
			w->justInvisible = true;
			//	w->invisibleByProximity = true;
		}

		w->ID_X = x;
		w->ID_Y = y;
		w->ID_Z = i + 1;

		all.push_back(w);
		Tiles.push_back(w);

	}
	for (int i = 2; i < 3; i++)
	{

		auto w = new tile(glm::vec2((x - y) * 50 + ORIGIN_POINT_X,
			ORIGIN_POINT_Y + (x + y) * 33.5f),
			65.0f, i * 55 + 20, TILE_BIG, ResourceManager::GetTexture("dungeon_wall_top"));
		if (black) {
			w->color = glm::vec3(0, 0, 0);
			w->justInvisible = true;
			//	w->invisibleByProximity = true;
		}
		w->ID_X = x;
		w->ID_Y = y;
		w->ID_Z = i + 1;
		w->zDepthOffset += i * 20;
		all.push_back(w);
		Tiles.push_back(w);

	}
}
void level::init(const char* file, int Width, int Height)
{
	ScreenH = Height;
	ScreenW = Width;
	Area = std::make_unique<Grid>(NUM_OF_CEL, NUM_OF_CEL, CELLSIZE);
	ortho = glm::ortho(0.0f, static_cast<float>(Width),
		static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	if (data == nullptr) {
		printf("INVALID FILE AT %s IMBECILE", file);
		assert(false);
	}
	level_size_X = width;
	level_size_Y = height;
	level_size_Z = 3;


	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			auto i = nrChannels * (y * width + x);
			int R = *(data + i + 0);
			int G = *(data + i + 1);
			int B = *(data + i + 2);
			int A = *(data + i + 3);
			//if white
			if (R == 255 && G == 255 && B == 255 && A == 255) {
				createWall(glm::vec2(x, y), false);

			}
			if (R == 129 && G == 129 && B == 129 && A == 255) {
				createWall(glm::vec2(x, y), true);

			}
			if (R == 0 && G == 0 && B == 0 && A == 255) {
				createFloor(glm::vec2(x, y));

			}
			//printf("R%d", *(data + i + 0));
			//printf("G%d", *(data + i + 1));
			//printf("B%d", *(data + i + 2));
			//printf("A%d ", *(data + i + 3));
		}
		//printf("\n");
	}


	//GridTile = new tile*[level_size_X * level_size_Y * level_size_Z];
	int size = level_size_Y * level_size_X * level_size_Y;
	MetaTile* mt = new  MetaTile[size];

	for (size_t i = 0; i < Tiles.size(); i++)
	{
		int num = Tiles[i]->ID_Z * level_size_X * level_size_Y + level_size_X * Tiles[i]->ID_Y + Tiles[i]->ID_X;
		int onTop = Tiles[i]->ID_Z * level_size_X * level_size_Y + level_size_X * Tiles[i]->ID_Y + Tiles[i]->ID_X;
		mt[num]._tile = Tiles[i];
		mt[num].HasTile = true;

		//printf("Save as %d but s number %d but has a X of %d, Y of %d, Z of %d \n", num, i,	Tiles[i]->ID_X, Tiles[i]->ID_Y, Tiles[i]->ID_Z);

	}
	for (size_t i = 0; i < Tiles.size(); i++)
	{
		int num = Tiles[i]->ID_Z * level_size_X * level_size_Y + level_size_X * Tiles[i]->ID_Y + Tiles[i]->ID_X;
		int onTop = (Tiles[i]->ID_Z + 1) * level_size_X * level_size_Y + level_size_X * Tiles[i]->ID_Y + Tiles[i]->ID_X;
		if (onTop < size)
			if (mt[num].HasTile) {
				if (mt[onTop].HasTile) {
					mt[num].onTop = &mt[onTop];
					mt[num].HasOnTop = true;
				}
			}

	}
	//	grid_Tile = &ss;
	metaTile = mt;

	auto banana = new item();
	banana->name = "Banana";
	banana->img = ResourceManager::GetTexture("big_nana");
	banana->amount = 1;
	banana->setlocalPos(28, 2);
 
	banana->value = 1;
	banana->onDrop(0);
 banana->shadow= ResourceManager::GetTexture("shadow");
	 
	Items.push_back(banana);

	// NPCs.push_back(banana); //oh god no
	
	all.push_back(banana);
	stbi_image_free(data);
	Area->addPrimitives(all);
 


	 
}

void level::enter(performer * player)
{
	this->player = player;
	Area->addPrimitive(player);
	player->zDepthOffset = 210;
	//UI
	auto HP = new UI_BAR(ResourceManager::GetTexture("HP_S"),
		ResourceManager::GetTexture("HP_M"),
		ResourceManager::GetTexture("HP_E"),
		ResourceManager::GetTexture("HP_B")
	);
	auto NRJ = new UI_Toggle(ResourceManager::GetTexture("NRJ"),
		ResourceManager::GetTexture("NRJ_B"));

	auto viva = new UI_Performer_Status(player, NRJ, HP);
	UIs.push_back(viva);
	auto brh = new NRJ_FX(ResourceManager::GetTexture("NRJ_UP"));
	brh->isInfinite = true;
	brh->GiveNRJat = 1;
	player->ApplyEffects(brh);
	player->setlocalPos(28, 5);
	Items[0]->CullByProximity = true;
 

}
void level::update(float dt)
{
	player->update(dt);
	Area.get()->refresh(&NPCs, player);
	Area.get()->refresh(&Items, player);
	Area.get()->updateCollision();
 
	for (int i = 0; i < all.size(); i++)	all[i]->update(dt);
}

bool level::visit(glm::vec2 p1, float l) {
	bool t = false;
	for (int i = 0; i < 2; i++)
	{
		auto omama = i * level_size_X * level_size_Y + level_size_X * (int)p1.y + (int)p1.x;
		if (omama > level_size_X * level_size_Y * level_size_Z || omama < 0)continue;

		if (!metaTile[omama].HasTile)continue;
		tile * q = metaTile[omama]._tile;

		float w = l;
	//	if (i > 0)w = 0;
		// if (i > 0 && player->isLowerThan(q->localPos()+ glm::vec2(-.5, -.5)))w =0;
		MetaTile  re = metaTile[omama];
		while (re.HasOnTop)
		{
			re.onTop->_tile->alpha = w;
			re = *re.onTop;
		}
		q->alpha = w;
		if (i > 0)  t = true;
			
		 
	}
	return t;

}
void level::raytrace(glm::vec2 from, glm::vec2 there)
{
	float  dx = abs(there.x - from.x);
	float dy = abs(there.y - from.y);
	float  x = from.x;
	float  y = from.y;
	float  n = dx + dy;
	float  x_inc = (there.x > from.x) ? 1 : -1;
	float  y_inc = (there.y > from.y) ? 1 : -1;
	float  error = dx - dy;
	dx *= 2;
	dy *= 2;

	float light = 1.3;
	for (; n > 0 && light > 0; --n)
	{
		if (visit(glm::vec2(x, y), light))return;
		light -= .111;
		if (error > 0)
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}
}
void level::raycastAlgorithm() {

	auto e = player->localPos() - glm::vec2(-.5,-.5);

	for (size_t i = 0; i < 360; i += 1)
	{
		glm::vec2 th;
		th.x = cos(i);
		th.y = sin(i);
		raytrace(e, e + th * 10.0f);
	}


}
void level::render(SpriteBatch * sp, GLSLProgram * pr)
{
	Viewable.push_back(player);

	for (size_t i = 1; i < NPCs.size(); i++)
	{
		bool e = player->DistanceFrom(NPCs[i]) > cullingRender * cullingRender;
		NPCs[i]->activeActor(!e);
		NPCs[i]->drawShadow(player);
		if (!e)Viewable.push_back(NPCs[i]);
	}
	for (size_t i = 0; i < Items.size(); i++)
	{
		bool e = player->DistanceFrom(Items[i]) > cullingRender * cullingRender;
		Items[i]->activeActor(!e);
		Items[i]->drawShadow(player);
		if (!e)Viewable.push_back(Items[i]);
	}
	for (size_t i = 0; i < this->Tiles.size(); i++)
	{
		if (player->DistanceFrom(Tiles[i]) > cullingRender * cullingRender) continue;
		// Tiles[i]->shadow(player);
		 Tiles[i]->alpha = 0;
		auto wq = Tiles[i]->pos.y - player->pos.y;
		//Tiles[i]->invisibleByProximity =wq > -20 && Tiles[i]->Z > player->Z;
		//

		 Viewable.push_back(Tiles[i]);
	}

	raycastAlgorithm();

	LastPLayerPos = player->localPos();
	pr->use();
	sp->begin(GlyphSortType::FRONT_TO_BACK);
	auto m_cameraMatrix = glm::translate(ortho, glm::vec3(sp->Camera, 0));
	glm::vec3 scale(sp->zoom, sp->zoom, 0.0f);
	m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
	glUniform1i(pr->getUniformLocation("mySampler"), 0);
	glUniformMatrix4fv(pr->getUniformLocation("P"), 1, GL_FALSE, &m_cameraMatrix[0][0]);

	for (size_t i = 0; i < Viewable.size(); i++)
	{
		Viewable[i]->Draw(*sp);
	}
	Viewable[0]->Draw(*sp, true);
	UIs[0]->pos = player->pos;

	for (size_t i = 0; i < UIs.size(); i++)
	{
		UIs[0]->Draw(*sp, false);
	}
	sp->end();
	sp->renderBatch();
	pr->unuse();
	Viewable.clear();

	//UI 
	/*pr->use();
	sp->begin(GlyphSortType::FRONT_TO_BACK);
	m_cameraMatrix = glm::translate(ortho, glm::vec3(0,0,0));
	glUniform1i(pr->getUniformLocation("mySampler"), 0);
	glUniformMatrix4fv(pr->getUniformLocation("P"), 1, GL_FALSE, &m_cameraMatrix[0][0]);

	//UIs[0]->Draw(*sp, false);
	sp->end();
	sp->renderBatch();
	pr->unuse();
	*/
}

void level::exit()
{
	this->player = nullptr;
}
