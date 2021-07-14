#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include "boost/filesystem/operations.hpp"
#include <boost/foreach.hpp> 
#include "ressourceManager.hpp"
namespace fs = boost::filesystem;
using namespace std;


enum itemType {
	item_GENERIC =-1 ,
	item_QUEST = 1,
	item_EQUIPMENT =2,
	item_USE =3,
};
class metaItem {

public:
	std::string internalName;
	 string Name;
	std::string Description;
	std::string tex_menu, tex_tangible, tex_Icon;
	itemType type = item_GENERIC;
	double value = -1.0;
	float x_size =1 , y_size =1, z_size=1;

	metaItem() {

	}
	metaItem(string in, string na, string des, string tex) {
		internalName = in;
		Name = na;
		Description = des;
        tex_menu = tex;
	}
	static map<std::string, metaItem> items;

	
	static metaItem LoadMetaItem();

	static void AddMetaItem(metaItem * m);
	static void SaveMetaItem(metaItem* m);
};