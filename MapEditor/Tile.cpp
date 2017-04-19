#include "Tile.h"
#include <osg/Texture2D>
#include <osgDB/ReadFile>

Tile::Tile() :
_x(0), _z(0),
_type(TexType::BORDER)
{
}

Tile::Tile(unsigned int x, unsigned int z, TexType type) :
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
		osg::Vec3(_x + _size, 0., _z),
		osg::Vec3(_x, 0., _z + _size));
	
	calculateNormals(osg::Vec3(_x, 0., _z + _size),
		osg::Vec3(_x + _size, 0., _z),
		osg::Vec3(_x + _size, 0., _z + _size));

	setNormalArray(_normals);

	setTexture();
}

Tile::Tile(unsigned int x, unsigned int z, TexType type, EmptyTile empty) :
_x(x), _z(z),
_type(type)
{
	//построение полигона
	_vertices->push_back(osg::Vec3(_x, 0., _z));
	_vertices->push_back(osg::Vec3(_x, 0., _z + _size));
	_vertices->push_back(osg::Vec3(_x + _size, 0., _z));
	_vertices->push_back(osg::Vec3(_x + _size, 0., _z + _size));

	setVertexArray(_vertices);
	addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, _vertices->size()));

	//нормали
	_normals->setBinding(osg::Array::BIND_PER_VERTEX);

	calculateNormals(osg::Vec3(_x, 0., _z),
		osg::Vec3(_x + _size, 0., _z),
		osg::Vec3(_x, 0., _z + _size));

	calculateNormals(osg::Vec3(_x, 0., _z + _size),
		osg::Vec3(_x + _size, 0., _z),
		osg::Vec3(_x + _size, 0., _z + _size));

	setNormalArray(_normals);

	setEmptyTexture(empty);
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

void Tile::SetType(TexType type)
{
	_type = type;
	if (_type != TexType::EMPTY)
		setTexture();
	//else if (_type == TexType::EMPTY)
		//setEmptyTexture();
	//else remove
}

void Tile::setTexture()
{
	//нат€гивание текстуры на тайл
	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
	texcoords->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords->push_back(osg::Vec2(1.0f, 0.0f));
	texcoords->push_back(osg::Vec2(1.0f, 1.0f));
	setTexCoordArray(0, texcoords);

	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;

	osg::ref_ptr<osg::Image> image;
	
	std::string texFilename = "Resources/tiles/";

	switch (_type)
	{
	case TexType::ARMOR:
		texFilename += "ARMOR.png";
		break;
	case TexType::BORDER:
		texFilename += "BORDER.png";
		break;
	case TexType::BRICK:
		texFilename += "BRICK.png";
		break;
	case TexType::BUSHES:
		texFilename += "BUSHES.png";
		break;
	case TexType::ICE:
		texFilename += "ICE.png";
		break;
	case TexType::WATER:
		texFilename += "WATER.png";
		break;
	case TexType::EMPTY:

		break;
	}

	image = osgDB::readImageFile(texFilename);

	if (!image)
	{
		// ошибка
	}

	texture->setImage(image);

	osg::ref_ptr<osg::StateSet> stateTile = new osg::StateSet;
	stateTile->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
	setStateSet(stateTile);
}

void Tile::setEmptyTexture(EmptyTile empty)
{
	//нат€гивание текстуры на тайл
	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
	texcoords->push_back(osg::Vec2(0.0f, 0.0f));
	texcoords->push_back(osg::Vec2(0.0f, 1.0f));
	texcoords->push_back(osg::Vec2(1.0f, 0.0f));
	texcoords->push_back(osg::Vec2(1.0f, 1.0f));
	setTexCoordArray(0, texcoords);

	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;

	osg::ref_ptr<osg::Image> image;

	std::string texFilename = "Resources/tiles/";

	switch (empty)
	{
	case EmptyTile::LEFT_BOTTOM:
		texFilename += "empty_leftBottom.png";
		break;
	case EmptyTile::LEFT_TOP:
		texFilename += "empty_leftTop.png";
		break;
	case EmptyTile::RIGHT_TOP:
		texFilename += "empty_rightTop.png";
		break;
	case EmptyTile::RIGHT_BOTTOM:
		texFilename += "empty_rightBottom.png";
		break;
	}

	image = osgDB::readImageFile(texFilename);

	if (!image)
	{
		// ошибка
	}

	texture->setImage(image);

	osg::ref_ptr<osg::StateSet> stateTile = new osg::StateSet;
	stateTile->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
	stateTile->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	stateTile->setMode(GL_BLEND, osg::StateAttribute::ON);
	setStateSet(stateTile);
}

QString Tile::GetType_str()
{
	QString texType;

	switch (_type)
	{
	case TexType::ARMOR:
		texType = "ARMOR";
		break;
	case TexType::BORDER:
		texType = "BORDER";
		break;
	case TexType::BRICK:
		texType = "BRICK";
		break;
	case TexType::BUSHES:
		texType = "BUSHES";
		break;
	case TexType::EMPTY:
		//не писать в файл
		texType = "EMPTY";
		break;
	case TexType::WATER:
		texType = "WATER";
		break;
	case TexType::ICE:
		texType = "ICE";
		break;
	}

	return texType;
}