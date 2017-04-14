#include "Block.h"


Block::Block()
{
}

//принимает координаты, тип блока
Block::Block(int x, int z, BlockType type) :
_x(x), _z(z),
_type(type)
{
	//x *= 16;
	//перевод в тайловые координаты
	int tileSize = Tile::Size();
	//x *= tileSize;
	//z *= tileSize;
	//x *= _size;
	//z *= _size;

	switch (_type)
	{
	case BlockType::ARMOR_FULL:
		_leftBottom = new Tile(x, z, TileType::ARMOR);
		_leftTop = new Tile(x, z + tileSize, TileType::ARMOR);
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::ARMOR);
		_rightBottom = new Tile(x + tileSize, z, TileType::ARMOR);
		break;
	case BlockType::ARMOR_BOTTOM:
		_leftBottom = new Tile(x, z, TileType::ARMOR);
		_rightBottom = new Tile(x + tileSize, z, TileType::ARMOR);
		break;
	case BlockType::ARMOR_LEFT:
		_leftBottom = new Tile(x, z, TileType::ARMOR);
		_leftTop = new Tile(x, z + tileSize, TileType::ARMOR);
		break;
	case BlockType::ARMOR_RIGHT:
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::ARMOR);
		_rightBottom = new Tile(x + tileSize, z, TileType::ARMOR);
		break;
	case BlockType::ARMOR_TOP:
		_leftTop = new Tile(x, z + tileSize, TileType::ARMOR);
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::ARMOR);
		break;
	case BlockType::BORDER:
		_leftBottom = new Tile(x, z, TileType::BORDER);
		_leftTop = new Tile(x, z + tileSize, TileType::BORDER);
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::BORDER);
		_rightBottom = new Tile(x + tileSize, z, TileType::BORDER);
		break;
	case BlockType::BRICK_FULL:
		_leftBottom = new Tile(x, z, TileType::BRICK);
		_leftTop = new Tile(x, z + tileSize, TileType::BRICK);
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::BRICK);
		_rightBottom = new Tile(x + tileSize, z, TileType::BRICK);
		break;
	case BlockType::BRICK_BOTTOM:
		_leftBottom = new Tile(x, z, TileType::BRICK);
		_rightBottom = new Tile(x + tileSize, z, TileType::BRICK);
		break;
	case BlockType::BRICK_LEFT:
		_leftBottom = new Tile(x, z, TileType::BRICK);
		_leftTop = new Tile(x, z + tileSize, TileType::BRICK);
		break;
	case BlockType::BRICK_RIGHT:
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::BRICK);
		_rightBottom = new Tile(x + tileSize, z, TileType::BRICK);
		break;
	case BlockType::BRICK_TOP:
		_leftTop = new Tile(x, z + tileSize, TileType::BRICK);
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::BRICK);
		break;
	case BlockType::BUSHES:
		_leftBottom = new Tile(x, z, TileType::BUSHES);
		_leftTop = new Tile(x, z + tileSize, TileType::BUSHES);
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::BUSHES);
		_rightBottom = new Tile(x + tileSize, z, TileType::BUSHES);
		break;
	case BlockType::EMPTY:
		_leftBottom = new Tile(x, z, TileType::EMPTY, EmptyTile::LEFT_BOTTOM);
		_leftTop = new Tile(x, z + tileSize, TileType::EMPTY, EmptyTile::LEFT_TOP);
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::EMPTY, EmptyTile::RIGHT_TOP);
		_rightBottom = new Tile(x + tileSize, z, TileType::EMPTY, EmptyTile::RIGHT_BOTTOM);
		break;
	case BlockType::ICE:
		_leftBottom = new Tile(x, z, TileType::ICE);
		_leftTop = new Tile(x, z + tileSize, TileType::ICE);
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::ICE);
		_rightBottom = new Tile(x + tileSize, z, TileType::ICE);
		break;
	case BlockType::WATER:
		_leftBottom = new Tile(x, z, TileType::WATER);
		_leftTop = new Tile(x, z + tileSize, TileType::WATER);
		_rightTop = new Tile(x + tileSize, z + tileSize, TileType::WATER);
		_rightBottom = new Tile(x + tileSize, z, TileType::WATER);
		break;
	}

	if (_leftBottom != nullptr)	addChild(_leftBottom);
	if (_leftTop != nullptr) addChild(_leftTop);
	if (_rightTop != nullptr) addChild(_rightTop);
	if (_rightBottom != nullptr) addChild(_rightBottom);
}

Block::~Block()
{
}
