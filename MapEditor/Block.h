#pragma once

#include <osg/Group>
#include <qstring.h>

#include <Tile.h>

enum class FillType		//block filling
{
  FULL,		//4 tiles
  RIGHT,	//2 tiles
  BOTTOM,
  LEFT,
  TOP
};

class Block : public osg::Group		//block consists 4 tiles, block size 16x16
{
public:
  Block();
  Block(int x, int z, TexType type, FillType fillType);
  ~Block();

  TexType GetType() { return _type; }
  FillType GetFillType()	{ return _fType; }

  std::pair<QString, QString> GetType_str();

  int GetX()	{ return _x; }
  int GetZ()	{ return _z; }

  //для записи в файл
  QString GetX_str()	{ return QString::number(_x + 16); }	//+16 for matching with file
  QString GetZ_str()	{ return QString::number(_z + 16); }

  void SetType(TexType texType, FillType fillType);

  void SetPassability(bool isPassable)  { _isPassable = isPassable; }
  void SetDrawingUnderTank(bool isUnderTank)  { _isUnderTank = isUnderTank; }

private:
  int _x;
  int _z;
  const int _size = 16;

  osg::ref_ptr<Tile> _leftBottom = nullptr;
  osg::ref_ptr<Tile> _leftTop = nullptr;
  osg::ref_ptr<Tile> _rightTop = nullptr;
  osg::ref_ptr<Tile> _rightBottom = nullptr;

  TexType _type;
  FillType _fType;

  bool _isUnderTank = true;	//drawing under tank
  bool _isPassable = true;	//obstacle or not

  void createFromTiles(TexType texType, FillType fillType);
};

