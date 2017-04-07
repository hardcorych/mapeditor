#include "Map.h"


Map::Map() :
_step(8)
{
	//стандартный размер карты
	_size = 10 * _step;
	//формирование границ
	std::vector<Tile> tiles;

	for (int z = 0; z < _size; z += _step)
	{
		for (int x = 0; x < _size; x += _step)
		{
			tiles.push_back(Tile(x, z, BORDER));
		}
	}
}

Map::Map(unsigned int size) :
_size(size),
_step(8)
{
	//указанный размер карты
	//формирование границ
}

Map::~Map()
{
}

void Map::AddBlock()
{

}

void Map::RemoveBlock()
{

}

void Map::ReadFile()
{

}

void Map::SaveFile()
{

}
