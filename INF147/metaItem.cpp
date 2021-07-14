#include "metaItem.h"


metaItem metaItem::LoadMetaItem()
{

	fs::path targetDir("./items");

	fs::directory_iterator it(targetDir), eod;
	printf("Looking for Meta Items:\n");

	BOOST_FOREACH(fs::path const& p, std::make_pair(it, eod))
	{
		if (fs::is_regular_file(p))
		{
			printf("now loading : ");
			printf(p.string().c_str());
			printf("\n");
			ifstream ni(p.string().c_str());
			string line, val;
			vector<string>  ow;
			int i = 0;
			while (getline(ni, line, '|')) {
				//printf("ow[%d]", i);
			//	printf(line.c_str());
				ow.push_back(line);
				//printf("\n");
				i++;

			}
			 printf(" -\n");
			if (ow[0] == "item") {
				auto lol = new metaItem(ow[1], ow[2], ow[3], ow[5]);
				if (!ow[6].empty()) {
					lol->value = atof(ow[6].c_str());
				}
				if (!ow[7].empty()) {
					lol->type = (itemType)atoi(ow[7].c_str());
				}
				if (!ow[8].empty())  lol->x_size = atof(ow[8].c_str());
				if (!ow[9].empty())  lol->y_size = atof(ow[9].c_str());
				if (!ow[10].empty())  lol->z_size = atof(ow[10].c_str());

				metaItem::AddMetaItem(lol);
			}
		}
	}


	metaItem mi;




	return mi;
}

void metaItem::AddMetaItem(metaItem* m)
{

	//items[m->internalName] = *m;
	printf("Add item: ");
	printf(m->internalName.c_str());
	printf("\n\n");
	SaveMetaItem(m);

}

void metaItem::SaveMetaItem(metaItem* m)
{
	string path = "./items/" + m->internalName + ".item";
	ofstream file(path);
	file << "item|";
	file << m->internalName + "|";
	file << m->Name + "|";
	file << m->Description + "|";
	file << m->tex_Icon + "|";
	file << m->tex_menu + "|";
	file << m->tex_tangible + "|";
	file << m->type + "|";
	file << m->value; file << "|";
	file << m->x_size; file << "|";
	file << m->y_size; file << "|";
	file << m->z_size; file << "|";

	file.flush();
	file.close();


}
