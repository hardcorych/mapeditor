#pragma once

#include <osg/Geometry>

#include <qstring.h>

class Tile : public osg::Geometry
{
public:
  enum class EmptyTile
  {
    LEFT_BOTTOM,
    LEFT_TOP,
    RIGHT_TOP,
    RIGHT_BOTTOM
  };

public:
  Tile() = default;

  //string textype
  Tile(unsigned int x, 
       unsigned int z,
       std::string typeName, 
       std::string texPath);
  Tile(unsigned int x, 
       unsigned int z,
       std::string typeName,
       EmptyTile empty);	//для пустых тайлов

protected:
  ~Tile();

public:
  //для записи в файл
  inline QString GetX_str()	const;
  inline QString GetZ_str()	const;

  QString GetType_str();

  inline static const int Size();

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

inline QString Tile::GetX_str() const
{ 
  return QString::number(_x + 16);
}	//+16 для согласования

inline QString Tile::GetZ_str() const
{ 
  return QString::number(_z + 16);
}

inline const int Tile::Size() 
{ 
  return _size;
}