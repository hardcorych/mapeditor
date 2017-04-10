#include "Tile.h"


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
	colors->push_back(osg::Vec4(235 / 255.f, 211 / 255.f, 183 / 255.f, 0.0f));
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

	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;    //цвет
	colors->push_back(osg::Vec4(235 / 255.f, 211 / 255.f, 183 / 255.f, 0.0f));
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