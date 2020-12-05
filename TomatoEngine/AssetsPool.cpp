#include "AssetsPool.h"

AssetsPool *AssetsPool::instance = nullptr;

void AssetsPool::loadTextureData(std::string filename)
{
	auto count = 0;
	result = doc.load_file(filename.c_str());
	pugi::xml_node data = doc.child("DATA");
	
	for (pugi::xml_node info = data.first_child(); info; info = info.next_sibling())
	{
		TextureDetails td;
		td.filename = info.attribute("filename").as_string();
		td.w = info.attribute("w").as_int();
		td.h = info.attribute("h").as_int();
		td.io = info.attribute("io").as_int();
		td.il = info.attribute("il").as_int();
		td.mo = info.attribute("mo").as_int();
		td.ml = info.attribute("ml").as_int();
		td.jo = info.attribute("jo").as_int();
		td.jl = info.attribute("jl").as_int();
		td.ao = info.attribute("ao").as_int();
		td.al = info.attribute("al").as_int();

		textureDetails[info.attribute("id").as_int()] = td;
	}
}