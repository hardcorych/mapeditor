#pragma once

#include <osg/Group>
#include <Tile.h>
#include <qstring.h>

enum class FillType		//заполненность блока
{
	FULL,		//4 тайла
	RIGHT,		//по 2 тайла
	BOTTOM,
	LEFT,
	TOP
};

class Block : public osg::Group		//блока из 4 тайлов, общим размером 16х16
{
public:
	Block();
	Block(int x, int z, TexType type, FillType fillType);
	~Block();

	TexType GetType() { return _type; }
	FillType GetFillType()	{ return _fType; }

	std::pair<QString, QString> GetType_str();
	
	int GetX()	{ return _x; }
	int GetZ()	{ return _z; }

	//для записи в файл
	QString GetX_str()	{ return QString::number(_x+16); }	//+16 для согласования
	QString GetZ_str()	{ return QString::number(_z+16); }

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

