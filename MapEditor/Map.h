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

	void AddBlock(int x, int z, BlockType type);
	void RemoveBlock();

private:
	int _sizeX;
	int _sizeZ;
	unsigned int _size;		//размер карты. задается любыми цифрами, затем умножается на 16(перевод в блоки) или 8 (перевод в тайлы)	
	int _step;		//шаг равный размеру одного блока/тайла
	
	std::map<std::pair<int, int>, osg::ref_ptr<Tile>> tileMap;	//тайлы, ключ - координаты XZ
	std::map<std::pair<int, int>, osg::ref_ptr<Block>> blockMap;	//блоки, ключ - координаты XZ

	void setBorder();
};

