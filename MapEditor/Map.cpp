#include "Map.h"


Map::Map() :
_step(8),	//��� ������
//_step(16)	//��� ������
_sizeX(10), _sizeZ(10)
{
	setBorder();
}

Map::Map(unsigned int sizeX, unsigned int sizeZ) :
_sizeX(sizeX),
_sizeZ(sizeZ),
_step(16)
{
	//��������� ������ �����
	//������ �������� � ���������� ������ ������� �������
	//������������ ������
	setBorder();
}

Map::~Map()
{
}

void Map::setBorder()
{
	//������� ��������?
	//����� 16�161
	//� ������ step = 16

	_step = 16;
	//���������� ������������ �������
	_sizeX = (_sizeX + 3)*_step;	//+2 ��������� ����� ��� �����
	_sizeZ = (_sizeZ + 2)*_step;
	//������������ ������
	//����� � 2 ���������, ������ ������� ������ ���� (��� �����?)

	//���������� ������ ������� �������, ������� � ������ �������
	//������ �������
	int startBorder = -1 * _step;
	for (int x = startBorder; x < _sizeX + startBorder; x += _step)
	{
		blockMap[std::make_pair(x, startBorder)] = 
			new Block(x, startBorder, BlockType::BORDER);

		addChild(blockMap[std::make_pair(x, startBorder)]);
	}
	//������ �������
	for (int z = 0; z < _sizeZ + startBorder; z += _step)
	{
		for (int x = _sizeX + 3 * startBorder; x < _sizeX + startBorder; x += _step)
		{
			blockMap[std::make_pair(x, z)] =
				new Block(x, z, BlockType::BORDER);

			addChild(blockMap[std::make_pair(x, z)]);
		}
	}
	//������� �������
	for (int x = _sizeX + 3 * startBorder; x >= startBorder; x -= _step)
	{
		blockMap[std::make_pair(x, _sizeZ + 2 * startBorder)] = 
			new Block(x, _sizeZ + 2 * startBorder, BlockType::BORDER);

		addChild(blockMap[std::make_pair(x, _sizeZ + 2 * startBorder)]);
	}
	//����� �������
	for (int z = _sizeZ + 3 * startBorder; z > startBorder; z -= _step)
	{
		blockMap[std::make_pair(startBorder, z)] =
			new Block(startBorder, z, BlockType::BORDER);

		addChild(blockMap[std::make_pair(startBorder, z)]);
	}

	blockMap[std::make_pair(5*_step, 5*_step)] = new Block(5*_step, 5*_step, BlockType::ARMOR_FULL);
	addChild(blockMap[std::make_pair(5*_step, 5*_step)]);

	//unsigned int g = getChildIndex(tileMap[std::make_pair(40, 16)]);
	//unsigned int g2 = g;
	//������, ����� child �������
	//removeChild(5);
	_sizeX -= 3 * _step;	//�������� �������������� � ������� ������� �������
	_sizeZ -= 2 * _step;
}

void Map::AddBlock(int x, int z, BlockType type)
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
