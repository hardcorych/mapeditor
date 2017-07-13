#pragma once
#include <Block.h>

#include <Tile.h>

Block::Block(int x, int z, const BlockType& blockType) :
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

void Block::createFromTiles(const BlockType& blockType)
{
  int tileSize = Tile::Size();

  std::string typeName = blockType.GetTypeName();
  std::string texPath = blockType.GetTexPath();
  std::string fillType = blockType.GetFillType();

  if (blockType.isEmptyType())
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
    if (_blockType.isFillFull())
    {
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, typeName, texPath);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
    }
    else if (_blockType.isFillBottom())
    {
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, "EMPTY", Tile::EmptyTile::LEFT_TOP);
      _rightTop = new Tile(_x + tileSize, 
                           _z + tileSize,
                           "EMPTY",
                           Tile::EmptyTile::RIGHT_TOP);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
    }
    else if (_blockType.isFillLeft())
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
    else if (_blockType.isFillRight())
    {
      _leftBottom = new Tile(_x, _z, "EMPTY", Tile::EmptyTile::LEFT_BOTTOM);
      _leftTop = new Tile(_x, _z + tileSize, "EMPTY", Tile::EmptyTile::LEFT_TOP);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
    }
    else if (_blockType.isFillTop())
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