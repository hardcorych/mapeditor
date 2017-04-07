#include "Block.h"


Block::Block()
{
}

Block::Block(Tile leftBottom, Tile leftTop, Tile rightTop, Tile rightBottom) :
_leftBottom(leftBottom),
_leftTop(leftTop),
_rightTop(rightTop),
_rightBottom(rightBottom)
{
}

Block::~Block()
{
}
