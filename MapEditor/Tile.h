#pragma once

#include <osg/Geode>
#include <osgDB/ReadFile>

enum TileType
{
	BORDER,		//������� ������� �������
	BRICK,		//������
	ARMOR,		//�����
	WATER,		//����
	BUSHES,		//������
	ICE			//���
};

//���� �������, �� ������� ������������ ��������

class Tile : public osg::Geometry		
{
public:
	Tile();
	Tile(unsigned int x, unsigned int z, TileType type);
	~Tile();

private:
	unsigned int _x;		//���������� �����
	unsigned int _z;
	const unsigned int _size = 8;		//������ ����� 8�8
	TileType _type;

	osg::ref_ptr<osg::Vec3Array> _vertices = new osg::Vec3Array;
};

