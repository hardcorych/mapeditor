#pragma once

#include <osg/Group>
#include <Tile.h>

enum class BlockType			//������������� ������
{
	BORDER,

	BRICK_FULL,		//5 �������� ��������, ��� 4 �����
	BRICK_RIGHT,	//�� 2 �����
	BRICK_BOTTOM,
	BRICK_LEFT,
	BRICK_TOP,

	ARMOR_FULL,		//5 �������� �����, ��� 4 �����
	ARMOR_RIGHT,	//�� 2 �����
	ARMOR_BOTTOM,
	ARMOR_LEFT,
	ARMOR_TOP,

	WATER,
	BUSHES,
	ICE,

	EMPTY
};

class Block : public osg::Group		//����� �� 4 ������, ����� �������� 16�16
{
public:
	Block();
	Block(int x, int z, BlockType type);
	~Block();

	void Remove();		//???

private:
	int _x;
	int _z;
	const int _size = 16;

	osg::ref_ptr<Tile> _leftBottom = nullptr;
	osg::ref_ptr<Tile> _leftTop = nullptr;
	osg::ref_ptr<Tile> _rightTop = nullptr;
	osg::ref_ptr<Tile> _rightBottom = nullptr;

	BlockType _type;
};

