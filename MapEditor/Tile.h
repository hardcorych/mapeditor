#pragma once

#include <osg/Geometry>

enum TileType
{
	BORDER,
	BRICK,
	ARMOR,
	WATER,
	BUSHES,
	ICE
};

class Tile		//���� �������� 8x8 ��������
{
public:
	Tile();
	Tile(unsigned int x, unsigned int z, TileType type);
	~Tile();

private:
	unsigned int _x;		//���������� �����
	unsigned int _z;
	TileType _type;
};

