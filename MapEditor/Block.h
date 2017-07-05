#pragma once

#include <osg/Group>

#include <qstring.h>

#include <BlockType.h>
#include <Tile.h>

class Block : public osg::Group		//block consists 4 tiles, block size 16x16
{
public:
  Block() = default;
  Block(int x, int z, BlockType blockType);

protected:
  ~Block();

public:
  inline BlockType GetType() const;

  inline int GetX() const;
  inline int GetZ() const;

  //для записи в файл
  inline QString GetX_str() const;
  inline QString GetZ_str() const;

private:
  void createFromTiles(BlockType blockType);

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

inline QString Block::GetX_str() const
{
  return QString::number(_x + _size); //+16 for matching with file
}	

inline QString Block::GetZ_str() const
{
  return QString::number(_z + _size);
}