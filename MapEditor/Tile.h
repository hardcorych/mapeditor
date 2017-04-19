#pragma once

#include <osg/Geode>
#include <osgDB/ReadFile>
#include <qstring.h>

enum class TexType
{
	BORDER,		//граница игровой области
	BRICK,		//кирпич
	ARMOR,		//брон€
	WATER,		//вода
	BUSHES,		//зелень
	ICE,		//лед
	EMPTY		//свободный тайл
};

enum class EmptyTile
{
	LEFT_BOTTOM,
	LEFT_TOP,
	RIGHT_TOP,
	RIGHT_BOTTOM
};

//тайл полигон, на который нат€гиваетс€ текстура

class Tile : public osg::Geometry		
{
public:
	Tile();
	Tile(unsigned int x, unsigned int z, TexType type);
	Tile(unsigned int x, unsigned int z, TexType type, EmptyTile empty);	//дл€ пустых тайлов
	~Tile();

	void SetXZ(unsigned int x, unsigned int z) { _x = x; _z = z; }
	//перегрузить оператор= дл€ установки типа тайла?
	void SetType(TexType type);

	QString GetX_str()	{ return QString::number(_x); }
	QString GetZ_str()	{ return QString::number(_z); }
	
	TexType GetType() { return _type; }
	
	QString GetType_str();

	static const int Size() { return _size; }

private:
	int _x;		//координаты тайла
	int _z;
	static const int _size = 8;		//размер тайла 8х8
	TexType _type;

	osg::ref_ptr<osg::Vec3Array> _vertices = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> _normals = new osg::Vec3Array;

	void calculateNormals(osg::Vec3 edge1, osg::Vec3 edge2, osg::Vec3 edge3);
	void setTexture();
	void setEmptyTexture(EmptyTile empty);
};

