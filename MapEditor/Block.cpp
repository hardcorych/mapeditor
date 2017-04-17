#include "Block.h"


Block::Block()
{
}

//��������� ����������, ��� �����
Block::Block(int x, int z, TexType type, FillType fillType) :
_x(x), _z(z),
_type(type),
_fType(fillType)
{
	//x *= 16;
	//������� � �������� ����������
	int tileSize = Tile::Size();
	//x *= tileSize;
	//z *= tileSize;
	//x *= _size;
	//z *= _size;

	createBlock(type, fillType);

	if (_leftBottom != nullptr)	addChild(_leftBottom);
	if (_leftTop != nullptr) addChild(_leftTop);
	if (_rightTop != nullptr) addChild(_rightTop);
	if (_rightBottom != nullptr) addChild(_rightBottom);
}

Block::~Block()
{
}

void Block::createBlock(TexType texType, FillType fillType)
{
	int tileSize = Tile::Size();

	_type = texType;
	_fType = fillType;

	if (texType == TexType::EMPTY)
	{
		_leftBottom = new Tile(_x, _z, TexType::EMPTY, EmptyTile::LEFT_BOTTOM);
		_leftTop = new Tile(_x, _z + tileSize, TexType::EMPTY, EmptyTile::LEFT_TOP);
		_rightTop = new Tile(_x + tileSize, _z + tileSize, TexType::EMPTY, EmptyTile::RIGHT_TOP);
		_rightBottom = new Tile(_x + tileSize, _z, TexType::EMPTY, EmptyTile::RIGHT_BOTTOM);
	}
	else
	{
		switch (fillType)
		{
		case FillType::FULL:
			_leftBottom = new Tile(_x, _z, texType);
			_leftTop = new Tile(_x, _z + tileSize, texType);
			_rightTop = new Tile(_x + tileSize, _z + tileSize, texType);
			_rightBottom = new Tile(_x + tileSize, _z, texType);
			break;
		case FillType::BOTTOM:
			_leftBottom = new Tile(_x, _z, texType);
			_leftTop = new Tile(_x, _z + tileSize, TexType::EMPTY, EmptyTile::LEFT_TOP);
			_rightTop = new Tile(_x + tileSize, _z + tileSize, TexType::EMPTY, EmptyTile::RIGHT_TOP);
			_rightBottom = new Tile(_x + tileSize, _z, texType);
			break;
		case FillType::LEFT:
			_leftBottom = new Tile(_x, _z, texType);
			_leftTop = new Tile(_x, _z + tileSize, texType);
			_rightTop = new Tile(_x + tileSize, _z + tileSize, TexType::EMPTY, EmptyTile::RIGHT_TOP);
			_rightBottom = new Tile(_x + tileSize, _z, TexType::EMPTY, EmptyTile::RIGHT_BOTTOM);
			break;
		case FillType::RIGHT:
			_leftBottom = new Tile(_x, _z, TexType::EMPTY, EmptyTile::LEFT_BOTTOM);
			_leftTop = new Tile(_x, _z + tileSize, TexType::EMPTY, EmptyTile::LEFT_TOP);
			_rightTop = new Tile(_x + tileSize, _z + tileSize, texType);
			_rightBottom = new Tile(_x + tileSize, _z, texType);
			break;
		case FillType::TOP:
			_leftBottom = new Tile(_x, _z, TexType::EMPTY, EmptyTile::LEFT_BOTTOM);
			_leftTop = new Tile(_x, _z + tileSize, texType);
			_rightTop = new Tile(_x + tileSize, _z + tileSize, texType);
			_rightBottom = new Tile(_x + tileSize, _z, TexType::EMPTY, EmptyTile::RIGHT_BOTTOM);
			break;
		}
	}
}

void Block::Remove()
{
	_leftBottom = nullptr;
	_leftTop = nullptr;
	_rightTop = nullptr;
	_rightBottom = nullptr;
}

void Block::SetBlock(TexType texType, FillType fillType)
{
	if (_type == TexType::EMPTY)
	{
		//���������� �����
		createBlock(texType, fillType);

		if (_leftBottom != nullptr)	addChild(_leftBottom);
		if (_leftTop != nullptr) addChild(_leftTop);
		if (_rightTop != nullptr) addChild(_rightTop);
		if (_rightBottom != nullptr) addChild(_rightBottom);
	}
	if ((_type != texType) || (_fType != fillType))		//���� ���� ����� ����� ��, ������ �� ��������
	{													//����� ���������� ������
		//������ �����
		removeChild(_leftBottom);
		removeChild(_leftTop);
		removeChild(_rightTop);
		removeChild(_rightBottom);

		createBlock(texType, fillType);
		
		if (_leftBottom != nullptr)	addChild(_leftBottom);
		if (_leftTop != nullptr) addChild(_leftTop);
		if (_rightTop != nullptr) addChild(_rightTop);
		if (_rightBottom != nullptr) addChild(_rightBottom);
	}
}
