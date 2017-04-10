#pragma once

#include <osg/Group>
#include <Block.h>

//вывод в XML-файл по тайлам

class Map : public osg::Group
{
public:
	Map();
	Map(unsigned int sizeX, unsigned int sizeZ);
	~Map();

	void ReadFile();
	void SaveFile();

	void AddBlock();
	void RemoveBlock();

private:
	int _sizeX;
	int _sizeZ;
	unsigned int _size;		//размер карты. задается любыми цифрами, затем умножается на 16(перевод в блоки) или 8 (перевод в тайлы)	
	const int _step;		//шаг равный размеру одного тайла
	
	std::vector<osg::ref_ptr<Tile>> tiles;	//тайлы
	//Tile tile;
	osg::ref_ptr<Tile> tile = new Tile;
	std::map<std::pair<int, int>, osg::ref_ptr<Tile>> tileMap;
	//std::map<std::pair<unsigned int, unsigned int>, TileType> tileMap;
	//std::map<std::pair<unsigned int, unsigned int>, BlockType> blockMap;

	void setBorder();
};

