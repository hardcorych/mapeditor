#pragma once

#include <osg/Geode>
#include <osgDB/ReadFile>
#include <qstring.h>

enum class EmptyTile    //???
{
  LEFT_BOTTOM,
  LEFT_TOP,
  RIGHT_TOP,
  RIGHT_BOTTOM
};

class Tile : public osg::Geometry
{
public:
  Tile() = default;
  //Tile(unsigned int x, unsigned int z, TexType type);
  //string textype
  Tile(unsigned int x, unsigned int z, std::string typeName, std::string texPath);
  Tile(unsigned int x, unsigned int z, std::string typeName, EmptyTile empty);	//дл€ пустых тайлов
  ~Tile();

  //дл€ записи в файл
  QString GetX_str()	{ return QString::number(_x + 16); }	//+16 дл€ согласовани€
  QString GetZ_str()	{ return QString::number(_z + 16); }

  QString GetType_str();

  static const int Size() { return _size; }

private:
  int _x;		//координаты тайла
  int _z;
  static const int _size = 8;		//размер тайла 8х8

  std::string _typeName;    //отсекать регул€ркой, начина€ с _
  std::string _texPath;

  osg::ref_ptr<osg::Vec3Array> _vertices = new osg::Vec3Array;
  osg::ref_ptr<osg::Vec3Array> _normals = new osg::Vec3Array;

  void calculateNormals(osg::Vec3 edge1, osg::Vec3 edge2, osg::Vec3 edge3);
  void setTexture(std::string texPath);
  void setEmptyTexture(EmptyTile empty);
};