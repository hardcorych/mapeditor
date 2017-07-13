#pragma once

#include <osg/Geometry>

#include <qstring.h>

///the smallest unit of block
class Tile : public osg::Geometry
{
public:
  enum EmptyTile
  {
    LEFT_BOTTOM,
    LEFT_TOP,
    RIGHT_TOP,
    RIGHT_BOTTOM
  };

public:
  Tile() = delete;
  Tile(const Tile&) = delete;
  Tile(unsigned int x, unsigned int z, std::string typeName, std::string texPath);
  //для пустых тайлов
  Tile(unsigned int x, unsigned int z, std::string typeName, EmptyTile empty);	

  Tile& operator=(const Tile&) = delete;
protected:
  ~Tile() = default;

public:
  //для записи в файл
  inline QString GetXToQStr() const;
  inline QString GetZToQStr() const;

  QString GetTypeToQStr();

  inline static const int Size();

  inline bool isEmptyType() const;
  inline bool isBorderType() const;
  inline bool isNotEmptyType() const;
  inline bool isNotBorderType() const;

private:
  void calculateNormals(osg::Vec3 edge1, osg::Vec3 edge2, osg::Vec3 edge3);
  void setTexture(std::string texPath);
  void setEmptyTexture(EmptyTile empty);

private:
  int _x;		//координаты тайла
  int _z;
  static const int _size = 8;		//размер тайла 8х8

  std::string _typeName;    
  std::string _texPath;

  osg::ref_ptr<osg::Vec3Array> _vertices;
  osg::ref_ptr<osg::Vec3Array> _normals;
};

inline QString Tile::GetXToQStr() const
{ 
  return QString::number(_x + 16);  //+16 для согласования
}	

inline QString Tile::GetZToQStr() const
{ 
  return QString::number(_z + 16);
}

inline const int Tile::Size() 
{ 
  return _size;
}

inline bool Tile::isEmptyType() const
{
  return (_typeName == "EMPTY");
}

inline bool Tile::isBorderType() const
{
  return (_typeName == "BORDER");
}

inline bool Tile::isNotEmptyType() const
{
  return !(_typeName == "EMPTY");
}

inline bool Tile::isNotBorderType() const
{
  return !(_typeName == "BORDER");
}