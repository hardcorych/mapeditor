#include "Tile.h"
#include <osg/Texture2D>
#include <osgDB/ReadFile>

Tile::Tile() :
_x(0), _z(0),
_type(TileType::BORDER)
{
	//построение полигона
	_vertices->push_back(osg::Vec3(_x, 0., _z));
	_vertices->push_back(osg::Vec3(_x, 0., _z + _size));
	_vertices->push_back(osg::Vec3(_x + _size, 0., _z));
	_vertices->push_back(osg::Vec3(_x + _size, 0., _z + _size));

	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;    //цвет
	colors->push_back(osg::Vec4(105 / 255.f, 105 / 255.f, 105 / 255.f, 0.0f));
	setColorArray(colors.get(), osg::Array::BIND_OVERALL);

	setVertexArray(_vertices);

	addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, _vertices->size()));

	//нормали
	_normals->setBinding(osg::Array::BIND_PER_VERTEX);

	calculateNormals(osg::Vec3(_x, 0., _z),
		osg::Vec3(_x, 0., _z + _size),
		osg::Vec3(_x + _size, 0., _z));

	calculateNormals(osg::Vec3(_x, 0., _z + _size),
		osg::Vec3(_x + _size, 0., _z),
		osg::Vec3(_x + _size, 0., _z + _size));

	setNormalArray(_normals);

	//нат€гивание текстуры
	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
	texcoords->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords->push_back(osg::Vec2(1.0f, 0.0f));
	texcoords->push_back(osg::Vec2(1.0f, 1.0f));
	setTexCoordArray(0, texcoords);

	setTexture();
}

Tile::Tile(unsigned int x, unsigned int z, TileType type) :
_x(x), _z(z),
_type(type)
{
	//построение полигона
	_vertices->push_back(osg::Vec3(_x, 0., _z));
	_vertices->push_back(osg::Vec3(_x, 0., _z + _size));
	_vertices->push_back(osg::Vec3(_x + _size, 0., _z));
	_vertices->push_back(osg::Vec3(_x + _size, 0., _z + _size));

	//osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;    //цвет
	//colors->push_back(osg::Vec4(105 / 255.f, 105 / 255.f, 105 / 255.f, 0.0f));
	//colors->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));
	//setColorArray(colors.get(), osg::Array::BIND_OVERALL);

	setVertexArray(_vertices);
	addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, _vertices->size()));

	//нормали
	_normals->setBinding(osg::Array::BIND_PER_VERTEX);

	calculateNormals(osg::Vec3(_x, 0., _z), 
		osg::Vec3(_x, 0., _z + _size),
		osg::Vec3(_x + _size, 0., _z));
	
	calculateNormals(osg::Vec3(_x, 0., _z + _size),
		osg::Vec3(_x + _size, 0., _z),
		osg::Vec3(_x + _size, 0., _z + _size));

	setNormalArray(_normals);

	//нат€гивание текстуры
	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
	texcoords->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords->push_back(osg::Vec2(1.0f, 0.0f));
	texcoords->push_back(osg::Vec2(1.0f, 1.0f));
	setTexCoordArray(0, texcoords);

	setTexture();
}


Tile::~Tile()
{
}

void Tile::calculateNormals(osg::Vec3 edge1, osg::Vec3 edge2, osg::Vec3 edge3)
{
	osg::Vec3 crossResult;

	(crossResult = (edge2 - edge1) ^ (edge3 - edge1)).normalize();

	_normals->push_back(crossResult);
	_normals->push_back(crossResult);
}

void Tile::SetType(TileType type)
{
	_type = type;
	if (_type != TileType::EMPTY)
		setTexture();
	//else remove
}

void Tile::setTexture()
{
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;

	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Resources/blocks/ARMOR.png");

	if (!image)
	{
		// ошибка
		bool c = true;
	}

	texture->setImage(image);

	osg::ref_ptr<osg::StateSet> stateTile = new osg::StateSet;
	stateTile->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
	setStateSet(stateTile);

	/*
	switch (_type)
	{
	case TileType::BRICK:

		break;
	}
	*/
}