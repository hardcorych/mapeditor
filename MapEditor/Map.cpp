#include "Map.h"


Map::Map() :
_step(8),	//для тайлов
//_step(16)	//для блоков
_sizeX(5), _sizeZ(5)
{
	setBorder();
}

Map::Map(unsigned int sizeX, unsigned int sizeZ) :
_sizeX(sizeX),
_sizeZ(sizeZ),
_step(8)
{
	//указанный размер карты
	//размер задается в количестве блоков игровой области
	//формирование границ
	setBorder();
}

Map::~Map()
{
}

void Map::setBorder()
{
	//вывести поблочно?
	//блоки 16х161
	//у блоков step = 16

	//_step = 16;
	//потайловое формирование границы
	_sizeX = (_sizeX + 2)*_step;	//+2 выделение места под рамку
	_sizeZ = (_sizeZ + 2)*_step;
	//формирование границ
	//карта с 2 индексами, каждый элемент хранит тайл (тип тайла?)

	//заполнение против часовой стрелки, начиная с нижней границы
	//нижняя граница
	int startBorder = -1 * _step;
	for (int x = startBorder; x < _sizeX + startBorder; x += _step)
	{
		tileMap[std::make_pair(x, startBorder)] = 
			new Tile(x, startBorder, TileType::BORDER);

		addChild(tileMap[std::make_pair(x, startBorder)]);
	}
	//правая граница
	for (int z = 0; z < _sizeZ + startBorder; z += _step)
	{
		tileMap[std::make_pair(_sizeX + 2 * startBorder, z)] = 
			new Tile(_sizeX + 2 * startBorder, z, TileType::BORDER);

		addChild(tileMap[std::make_pair(_sizeX + 2 * startBorder, z)]);
	}
	//верхняя граница
	for (int x = _sizeX + 3 * startBorder; x >= startBorder; x -= _step)
	{
		tileMap[std::make_pair(x, _sizeZ + 2 * startBorder)] = 
			new Tile(x, _sizeZ + 2 * startBorder, TileType::BORDER);

		addChild(tileMap[std::make_pair(x, _sizeZ + 2 * startBorder)]);
	}
	//левая граница
	for (int z = _sizeZ + 3 * startBorder; z > startBorder; z -= _step)
	{
		tileMap[std::make_pair(startBorder, z)] =
			new Tile(startBorder, z, TileType::BORDER);

		addChild(tileMap[std::make_pair(startBorder, z)]);
	}

	blockMap[std::make_pair(24, 24)] = new Block(24, 24, BlockType::ARMOR_LEFT);
	addChild(blockMap[std::make_pair(24, 24)]);

	blockMap[std::make_pair(8, 8)] = new Block(8, 8, BlockType::BRICK_FULL);
	addChild(blockMap[std::make_pair(8, 8)]);

	unsigned int g = getChildIndex(tileMap[std::make_pair(40, 16)]);
	unsigned int g2 = g;
	//узнать, какой child удалять
	//removeChild(5);
	_sizeX -= 2 * _step;	//обратное преобразование к размеру игровой области
	_sizeZ -= 2 * _step;
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
