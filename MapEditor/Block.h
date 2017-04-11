#pragma once

#include <osg/Group>
#include <Tile.h>

enum class BlockType			//разновидности блоков
{
	BORDER,

	BRICK_FULL,		//5 вариаций кирпичей, все 4 тайла
	BRICK_RIGHT,	//по 2 тайла
	BRICK_BOTTOM,
	BRICK_LEFT,
	BRICK_TOP,

	ARMOR_FULL,		//5 вариаций брони, все 4 тайла
	ARMOR_RIGHT,	//по 2 тайла
	ARMOR_BOTTOM,
	ARMOR_LEFT,
	ARMOR_TOP,

	WATER,
	BUSHES,
	ICE,

	EMPTY
};

class Block : public osg::Group		//блока из 4 тайлов, общим размером 16х16
{
public:
	Block();
	Block(int x, int z, BlockType type);
	~Block();

	void Remove();		//???

private:
	int _x;
	int _z;
	const int _size = 16;

	osg::ref_ptr<Tile> _leftBottom = nullptr;
	osg::ref_ptr<Tile> _leftTop = nullptr;
	osg::ref_ptr<Tile> _rightTop = nullptr;
	osg::ref_ptr<Tile> _rightBottom = nullptr;

	BlockType _type;
};

