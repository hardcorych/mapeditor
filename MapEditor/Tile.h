#pragma once

#include <osg/Geode>
#include <osgDB/ReadFile>
#include <qstring.h>

/*
enum class TexType    //???
{
  BORDER,		//граница игровой области
  BRICK,		//кирпич
  ARMOR,		//броня
  WATER,		//вода
  BUSHES,		//зелень
  ICE,		//лед
  EMPTY		//свободный тайл
};
*/

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
  Tile(unsigned int x, unsigned int z, std::string typeName, EmptyTile empty);	//для пустых тайлов
  ~Tile();

  //для записи в файл
  QString GetX_str()	{ return QString::number(_x + 16); }	//+16 для согласования
  QString GetZ_str()	{ return QString::number(_z + 16); }

  QString GetType_str();

  static const int Size() { return _size; }

private:
  int _x;		//координаты тайла
  int _z;
  static const int _size = 8;		//размер тайла 8х8
  //TexType _type;    //old

  std::string _typeName;
  std::string _texPath;

  osg::ref_ptr<osg::Vec3Array> _vertices = new osg::Vec3Array;
  osg::ref_ptr<osg::Vec3Array> _normals = new osg::Vec3Array;

  //static std::map<std::string, std::string> _textures;    //name-path
  //static bool _isFilled;

  void calculateNormals(osg::Vec3 edge1, osg::Vec3 edge2, osg::Vec3 edge3);
  //void setTexture();
  void Tile::setTexture(std::string texPath);
  void setEmptyTexture(EmptyTile empty);
};

