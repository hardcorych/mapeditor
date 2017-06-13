#pragma once

#include <osg/Geode>
#include <osgDB/ReadFile>
#include <qstring.h>

enum class TexType    //???
{
  BORDER,		//������� ������� �������
  BRICK,		//������
  ARMOR,		//�����
  WATER,		//����
  BUSHES,		//������
  ICE,		//���
  EMPTY		//��������� ����
};

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
  Tile();
  Tile(unsigned int x, unsigned int z, TexType type);
  Tile(unsigned int x, unsigned int z, TexType type, EmptyTile empty);	//��� ������ ������
  ~Tile();

  //��� ������ � ����
  QString GetX_str()	{ return QString::number(_x + 16); }	//+16 ��� ������������
  QString GetZ_str()	{ return QString::number(_z + 16); }

  QString GetType_str();

  static const int Size() { return _size; }

private:
  int _x;		//���������� �����
  int _z;
  static const int _size = 8;		//������ ����� 8�8
  TexType _type;

  osg::ref_ptr<osg::Vec3Array> _vertices = new osg::Vec3Array;
  osg::ref_ptr<osg::Vec3Array> _normals = new osg::Vec3Array;

  static std::map<std::string, std::string> _textures;    //name-path
  static bool _isFilled;

  void calculateNormals(osg::Vec3 edge1, osg::Vec3 edge2, osg::Vec3 edge3);
  void setTexture();
  void setEmptyTexture(EmptyTile empty);
};

