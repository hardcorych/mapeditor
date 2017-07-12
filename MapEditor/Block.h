#pragma once

#include <osg/Group>

#include <qstring.h>

#include "BlockType.h"
#include "Tile.h"

class Block : public osg::Group		//block consists 4 tiles, block size 16x16
{
public:
  Block() = delete;
  Block(const Block&) = default;
  Block(int x, int z, const BlockType& blockType);

  Block& operator=(const Block&) = delete;

protected:
  ~Block() = default;

public:
  inline BlockType GetType() const;

  inline int GetX() const;
  inline int GetZ() const;

  //для записи в файл
  inline QString GetXToQStr() const;
  inline QString GetZToQStr() const;

private:
  void createFromTiles(const BlockType& blockType);

private:
  int _x;
  int _z;
  int _size;

  osg::ref_ptr<Tile> _leftBottom;
  osg::ref_ptr<Tile> _leftTop;
  osg::ref_ptr<Tile> _rightTop;
  osg::ref_ptr<Tile> _rightBottom;

  BlockType _blockType;
};

inline BlockType Block::GetType() const
{
  return _blockType; 
}

inline int Block::GetX() const
{
  return _x; 
}
inline int Block::GetZ() const
{ 
  return _z; 
}

inline QString Block::GetXToQStr() const
{
  return QString::number(_x + _size); //+16 for matching with file
}	

inline QString Block::GetZToQStr() const
{
  return QString::number(_z + _size);
}