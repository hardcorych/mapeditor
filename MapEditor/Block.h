#pragma once

#include <osg/Group>
#include <Tile.h>

enum class BlockType			//разновидности блоков
{
	BORDER,

	BRICK_FULL,
	BRICK_RIGHT,
	BRICK_BOTTOM,
	BRICK_LEFT,
	BRICK_TOP,

	ARMOR_FULL,
	ARMOR_RIGHT,
	ARMOR_BOTTOM,
	ARMOR_LEFT,
	ARMOR_TOP,

	WATER,
	BUSHES,
	ICE
};

class Block : public osg::Group		//блока из 4 тайлов, общим размером 16х16
{
public:
	Block();
	Block(osg::ref_ptr<Tile> leftBottom, osg::ref_ptr<Tile> leftTop,
		osg::ref_ptr<Tile> rightTop, osg::ref_ptr<Tile> rightBottom);
	~Block();

private:
	osg::ref_ptr<Tile> _leftBottom;
	osg::ref_ptr<Tile> _leftTop;
	osg::ref_ptr<Tile> _rightTop;
	osg::ref_ptr<Tile> _rightBottom;
};

