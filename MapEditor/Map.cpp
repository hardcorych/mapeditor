#include "Map.h"


Map::Map() :
_step(8),	//��� ������
//_step(16)	//��� ������
_sizeX(10), _sizeZ(10)
{
	setBorder();
	setGameArea();
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
	setGameArea();
}

Map::~Map()
{
}

void Map::Set(int sizeX, int sizeZ)		//�������� ����� �����
{
	if (_sizeX != sizeX) _sizeX = sizeX;
	if (_sizeZ != sizeZ) _sizeZ = sizeZ;
	setBorder();
	setGameArea();
}

void Map::setBorder()
{
	_step = 16;
	//���������� ������������ �������
	_sizeX = (_sizeX + 3)*_step;	//��������� ����� ��� ����� +3 �� X
	_sizeZ = (_sizeZ + 2)*_step;	//��������� ����� ��� ����� +2 �� Z
	//������������ ������
	//����� � 2 ���������, ������ ������� ������ ���� (��� �����?)

	//���������� ������ ������� �������, ������� � ������ �������
	//������ �������
	int startBorder = -1 * _step;
	for (int x = startBorder; x < _sizeX + startBorder; x += _step)
	{
		addChild(new Block(x, startBorder, TexType::BORDER, FillType::FULL));
	}
	//������ �������
	for (int z = 0; z < _sizeZ + startBorder; z += _step)
	{
		for (int x = _sizeX + 3 * startBorder; x < _sizeX + startBorder; x += _step)
		{
			addChild(new Block(x, z, TexType::BORDER, FillType::FULL));
		}
	}
	//������� �������
	for (int x = _sizeX + 3 * startBorder; x >= startBorder; x -= _step)
	{
		addChild(new Block(x, _sizeZ + 2 * startBorder, TexType::BORDER, FillType::FULL));
	}
	//����� �������
	for (int z = _sizeZ + 3 * startBorder; z > startBorder; z -= _step)
	{
		addChild(new Block(startBorder, z, TexType::BORDER, FillType::FULL));
	}

	_sizeX -= 3 * _step;	//�������� �������������� � ������� ������� �������
	_sizeZ -= 2 * _step;
}

void Map::setGameArea()
{
	for (int z = 0; z < _sizeZ; z += _step)
	{
		for (int x = 0; x < _sizeX; x += _step)
		{
			//���������� ��������� ������� ������� �������
			addChild(new Block(x, z, TexType::EMPTY, FillType::FULL));
		}
	}
}

void Map::Remove()		//�������� �����
{
	removeChildren(0, getNumChildren());
}

void Map::AddBlock(osg::ref_ptr<Block> block, int x, int z)	//��� ������ �� �����
{
	Block* blockOld = nullptr;
	//����� �����, ������� ����� ��������
	for (int i = 0; i < getNumChildren(); i++)
	{
		blockOld = dynamic_cast<Block*>(getChild(i));
		if (blockOld->GetX() == x && blockOld->GetZ() == z)
		{
			replaceChild(blockOld, block);
		}
	}
}