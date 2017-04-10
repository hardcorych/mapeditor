#pragma once

#include <osg/Group>
#include <Tile.h>

class Block : public osg::Group		//����� �� 4 ������, ����� �������� 16�16
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

