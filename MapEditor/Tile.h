#pragma once

#include <osg/Geode>
#include <osgDB/ReadFile>

enum TileType
{
	BORDER,		//граница игровой области
	BRICK,		//кирпич
	ARMOR,		//брон€
	WATER,		//вода
	BUSHES,		//зелень
	ICE			//лед
};

//тайл полигон, на который нат€гиваетс€ текстура

class Tile : public osg::Geometry		
{
public:
	Tile();
	Tile(unsigned int x, unsigned int z, TileType type);
	~Tile();

private:
	unsigned int _x;		//координаты тайла
	unsigned int _z;
	const unsigned int _size = 8;		//размер тайла 8х8
	TileType _type;

	osg::ref_ptr<osg::Vec3Array> _vertices = new osg::Vec3Array;
};

