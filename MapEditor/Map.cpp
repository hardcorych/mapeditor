#include "Map.h"


Map::Map() :
_step(8),	//для тайлов
//_step(16)	//для блоков
_sizeX(10), _sizeZ(10)
{
	setBorder();
}

Map::Map(unsigned int sizeX, unsigned int sizeZ) :
_sizeX(sizeX),
_sizeZ(sizeZ),
_step(16)
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
	_step = 16;
	//потайловое формирование границы
	_sizeX = (_sizeX + 3)*_step;	//выделение места под рамку +3 по X
	_sizeZ = (_sizeZ + 2)*_step;	//выделение места под рамку +2 по Z
	//формирование границ
	//карта с 2 индексами, каждый элемент хранит тайл (тип тайла?)

	//заполнение против часовой стрелки, начиная с нижней границы
	//нижняя граница
	int startBorder = -1 * _step;
	for (int x = startBorder; x < _sizeX + startBorder; x += _step)
	{
		blockMap[std::make_pair(x, startBorder)] = 
			new Block(x, startBorder, BlockType::BORDER);

		addChild(blockMap[std::make_pair(x, startBorder)]);
	}
	//правая граница
	for (int z = 0; z < _sizeZ + startBorder; z += _step)
	{
		for (int x = _sizeX + 3 * startBorder; x < _sizeX + startBorder; x += _step)
		{
			blockMap[std::make_pair(x, z)] =
				new Block(x, z, BlockType::BORDER);

			addChild(blockMap[std::make_pair(x, z)]);
		}
	}
	//верхняя граница
	for (int x = _sizeX + 3 * startBorder; x >= startBorder; x -= _step)
	{
		blockMap[std::make_pair(x, _sizeZ + 2 * startBorder)] = 
			new Block(x, _sizeZ + 2 * startBorder, BlockType::BORDER);

		addChild(blockMap[std::make_pair(x, _sizeZ + 2 * startBorder)]);
	}
	//левая граница
	for (int z = _sizeZ + 3 * startBorder; z > startBorder; z -= _step)
	{
		blockMap[std::make_pair(startBorder, z)] =
			new Block(startBorder, z, BlockType::BORDER);

		addChild(blockMap[std::make_pair(startBorder, z)]);
	}

	blockMap[std::make_pair(5*_step, 5*_step)] = new Block(5*_step, 5*_step, BlockType::ARMOR_FULL);
	addChild(blockMap[std::make_pair(5*_step, 5*_step)]);

	blockMap[std::make_pair(5 * _step, 7 * _step)] = new Block(5 * _step, 7 * _step, BlockType::BRICK_RIGHT);
	addChild(blockMap[std::make_pair(5 * _step, 7 * _step)]);

	blockMap[std::make_pair(4 * _step, 7 * _step)] = new Block(4 * _step, 7 * _step, BlockType::BUSHES);
	addChild(blockMap[std::make_pair(4 * _step, 7 * _step)]);

	//unsigned int g = getChildIndex(tileMap[std::make_pair(40, 16)]);
	//unsigned int g2 = g;
	//узнать, какой child удалять
	//removeChild(5);
	_sizeX -= 3 * _step;	//обратное преобразование к размеру игровой области
	_sizeZ -= 2 * _step;

	setGameArea();
}

void Map::setGameArea()
{
	for (int z = 0; z < _sizeZ; z += _step)
	{
		for (int x = 0; x < _sizeX; x += _step)
		{
			//заполнение свободной области пустыми блоками
			//ok
			addChild(new Block(x, z, BlockType::EMPTY));
			//addChild(new Block(x, z, BlockType::BRICK_FULL));
		}
	}

}

void Map::AddBlock(int x, int z, BlockType type)
{
	if (blockMap.find(std::make_pair(x, z)) == blockMap.end())		//проверка на существование блока в карте
	{
		blockMap[std::make_pair(x, z)] = new Block(x, z, type);
		addChild(blockMap[std::make_pair(x, z)]);
	}
}

void Map::RemoveBlock(int x, int z)
{
	if (blockMap.find(std::make_pair(x, z)) != blockMap.end())
	{
		unsigned int indexRemove = getChildIndex(blockMap[std::make_pair(x, z)]);
		removeChild(indexRemove);
		//удаление блока из карты?
		blockMap.erase(std::make_pair(x, z));
	}
}

void Map::ReadFile()
{

}

void Map::SaveFile()
{

}
