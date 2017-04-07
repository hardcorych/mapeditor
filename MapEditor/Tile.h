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

class Tile		//тайл размером 8x8 пикселей
{
public:
	Tile();
	Tile(unsigned int x, unsigned int z, TileType type);
	~Tile();

private:
	unsigned int _x;		//координаты тайла
	unsigned int _z;
	TileType _type;
};

