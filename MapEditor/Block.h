#pragma once

#include <osg/Group>
#include <Tile.h>

class Block		//����� �� 4 ������, ����� �������� 16�16
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

