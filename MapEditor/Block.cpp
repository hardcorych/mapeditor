#include "Block.h"


Block::Block()
{
}

Block::Block(osg::ref_ptr<Tile> leftBottom, osg::ref_ptr<Tile> leftTop,
	osg::ref_ptr<Tile> rightTop, osg::ref_ptr<Tile> rightBottom) :
_leftBottom(leftBottom),
_leftTop(leftTop),
_rightTop(rightTop),
_rightBottom(rightBottom)
{
	addChild(_leftBottom);
	addChild(_leftTop);
	addChild(_rightTop);
	addChild(_rightBottom);
}

Block::~Block()
{
}
