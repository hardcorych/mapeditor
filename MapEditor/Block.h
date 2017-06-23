#pragma once

#include <osg/Group>
#include <qstring.h>

#include <BlockType.h>
#include <Tile.h>

class Block : public osg::Group		//block consists 4 tiles, block size 16x16
{
public:
  Block();
  Block(int x, int z, BlockType blockType);
  ~Block();

  std::pair<QString, QString> GetType_str();

  BlockType GetType() const { return _blockType; }

  int GetX()	{ return _x; }
  int GetZ()	{ return _z; }

  //для записи в файл
  QString GetX_str()	{ return QString::number(_x + 16); }	//+16 for matching with file
  QString GetZ_str()	{ return QString::number(_z + 16); }

  void SetType(BlockType blockType);

private:
  int _x;
  int _z;
  const int _size = 16;

  osg::ref_ptr<Tile> _leftBottom = nullptr;
  osg::ref_ptr<Tile> _leftTop = nullptr;
  osg::ref_ptr<Tile> _rightTop = nullptr;
  osg::ref_ptr<Tile> _rightBottom = nullptr;

  BlockType _blockType;

  void createFromTiles(BlockType blockType);
};