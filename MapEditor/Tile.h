#pragma once

#include <osg/Geode>
#include <osgDB/ReadFile>

enum class TileType
{
	BORDER,		//������� ������� �������
	BRICK,		//������
	ARMOR,		//�����
	WATER,		//����
	BUSHES,		//������
	ICE,		//���
	EMPTY		//��������� ����
};

enum class EmptyTile
{
	LEFT_BOTTOM,
	LEFT_TOP,
	RIGHT_TOP,
	RIGHT_BOTTOM
};

//���� �������, �� ������� ������������ ��������

class Tile : public osg::Geometry		
{
public:
	Tile();
	Tile(unsigned int x, unsigned int z, TileType type);
	Tile(unsigned int x, unsigned int z, TileType type, EmptyTile empty);	//��� ������ ������
	~Tile();

	void SetXZ(unsigned int x, unsigned int z) { _x = x; _z = z; }
	//����������� ��������= ��� ��������� ���� �����?
	void SetType(TileType type);
	std::pair<int, int> GetXZ() { return std::make_pair(_x, _z); }	//��� ������ � ����
	TileType GetType() { return _type; }

	static const int Size() { return _size; }

private:
	int _x;		//���������� �����
	int _z;
	static const int _size = 8;		//������ ����� 8�8
	TileType _type;

	osg::ref_ptr<osg::Vec3Array> _vertices = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> _normals = new osg::Vec3Array;

	void calculateNormals(osg::Vec3 edge1, osg::Vec3 edge2, osg::Vec3 edge3);
	void setTexture();
	void setEmptyTexture(EmptyTile empty);
};

