#pragma once

#include <osg/Group>
#include <Tile.h>

class Block		//блока из 4 тайлов, общим размером 16х16
{
public:
	Block();
	Block(Tile leftBottom, Tile leftTop, Tile rightTop, Tile rightBottom);
	~Block();

private:
	Tile _leftBottom;
	Tile _leftTop;
	Tile _rightTop;
	Tile _rightBottom;
};

