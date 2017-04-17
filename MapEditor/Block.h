#pragma once

#include <osg/Group>
#include <Tile.h>

enum class FillType		//������������� �����
{
	FULL,		//4 �����
	RIGHT,		//�� 2 �����
	BOTTOM,
	LEFT,
	TOP
};

class Block : public osg::Group		//����� �� 4 ������, ����� �������� 16�16
{
public:
	Block();
	Block(int x, int z, TexType type, FillType fillType);
	~Block();

	TexType GetType() { return _type; }

	void Remove();		//???
	void SetBlock(TexType texType, FillType fillType);

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

	void createBlock(TexType texType, FillType fillType);
};

