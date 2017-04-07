#pragma once

#include <osg/Group>
#include <Block.h>

//вывод в XML-файл по тайлам

class Map : public osg::Group
{
public:
	Map();
	Map(unsigned int size);
	~Map();

	void ReadFile();
	void SaveFile();

	void AddBlock();
	void RemoveBlock();

private:
	unsigned int _size;		//размер карты		
	const unsigned int _step;		//шаг равный размеру одного тайла
	
	std::vector<Tile> tiles;	//тайлы
};

