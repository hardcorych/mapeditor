#include "Block.h"
#include <Tile.h>

//принимает координаты, тип блока
Block::Block(int x, int z, BlockType blockType) :
    _x(x),
    _z(z),
    _blockType(blockType),
    _size(16),
    _leftBottom(nullptr),
    _leftTop(nullptr),
    _rightTop(nullptr),
    _rightBottom(nullptr)
{
  int tileSize = Tile::Size();

  createFromTiles(_blockType);

  if (_leftBottom != nullptr) addChild(_leftBottom);
  if (_leftTop != nullptr) addChild(_leftTop);
  if (_rightTop != nullptr) addChild(_rightTop);
  if (_rightBottom != nullptr) addChild(_rightBottom);
}

Block::~Block()
{
}

void Block::createFromTiles(BlockType blockType)
{
  int tileSize = Tile::Size();

  std::string typeName = blockType.GetTypeName();
  std::string texPath = blockType.GetTexPath();
  std::string fillType = blockType.GetFillType();

  if (typeName == "EMPTY")
  {
    _leftBottom = new Tile(_x, _z, typeName, Tile::EmptyTile::LEFT_BOTTOM);
    _leftTop = new Tile(_x, _z + tileSize, typeName, Tile::EmptyTile::LEFT_TOP);
    _rightTop = new Tile(_x + tileSize,
                         _z + tileSize,
                         typeName, 
                         Tile::EmptyTile::RIGHT_TOP);
    _rightBottom = new Tile(_x + tileSize, _z, typeName, Tile::EmptyTile::RIGHT_BOTTOM);
  }
  else
  {
    if (fillType == "FULL")
    {
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, typeName, texPath);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
    }
    else if (fillType == "BOTTOM")
    {
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, "EMPTY", Tile::EmptyTile::LEFT_TOP);
      _rightTop = new Tile(_x + tileSize, 
                           _z + tileSize,
                           "EMPTY",
                           Tile::EmptyTile::RIGHT_TOP);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
    }
    else if (fillType == "LEFT")
    {
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, typeName, texPath);
      _rightTop = new Tile(_x + tileSize, 
                           _z + tileSize,
                           "EMPTY",
                           Tile::EmptyTile::RIGHT_TOP);
      _rightBottom = new Tile(_x + tileSize, 
                              _z,
                              "EMPTY", 
                              Tile::EmptyTile::RIGHT_BOTTOM);
    }
    else if (fillType == "RIGHT")
    {
      _leftBottom = new Tile(_x, _z, "EMPTY", Tile::EmptyTile::LEFT_BOTTOM);
      _leftTop = new Tile(_x, _z + tileSize, "EMPTY", Tile::EmptyTile::LEFT_TOP);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
    }
    else if (fillType == "TOP")
    {
      _leftBottom = new Tile(_x, _z, "EMPTY", Tile::EmptyTile::LEFT_BOTTOM);
      _leftTop = new Tile(_x, _z + tileSize, typeName, texPath);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, 
                              _z,
                              "EMPTY",
                              Tile::EmptyTile::RIGHT_BOTTOM);
    }
  }
}