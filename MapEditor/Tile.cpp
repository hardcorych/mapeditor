#include "Tile.h"


Tile::Tile() :
_x(0), _z(0),
_type(BORDER)
{
}

Tile::Tile(unsigned int x, unsigned int z, TileType type) :
_x(x), _z(z),
_type(type)
{
}


Tile::~Tile()
{
}
