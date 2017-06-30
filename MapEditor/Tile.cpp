#include "Tile.h"

#include <osg/Texture2D>
#include <osgDB/ReadFile>

Tile::Tile(unsigned int x, unsigned int z, std::string typeName,
  std::string texPath) :
_x(x), _z(z),
_typeName(typeName),
_texPath(texPath)
{
  //polygon drawing
  _vertices->push_back(osg::Vec3(_x, 0., _z));
  _vertices->push_back(osg::Vec3(_x, 0., _z + _size));
  _vertices->push_back(osg::Vec3(_x + _size, 0., _z));
  _vertices->push_back(osg::Vec3(_x + _size, 0., _z + _size));

  setVertexArray(_vertices);
  addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,
    0, _vertices->size()));

  //normals
  _normals->setBinding(osg::Array::BIND_PER_VERTEX);

  calculateNormals(osg::Vec3(_x, 0., _z),
    osg::Vec3(_x + _size, 0., _z),
    osg::Vec3(_x, 0., _z + _size));

  calculateNormals(osg::Vec3(_x, 0., _z + _size),
    osg::Vec3(_x + _size, 0., _z),
    osg::Vec3(_x + _size, 0., _z + _size));

  setNormalArray(_normals);

  setTexture(_texPath);
}


Tile::Tile(unsigned int x, unsigned int z, std::string typeName, EmptyTile empty) :
_x(x), _z(z),
_typeName(typeName)
{
  //polygon drawing
  _vertices->push_back(osg::Vec3(_x, 0., _z));
  _vertices->push_back(osg::Vec3(_x, 0., _z + _size));
  _vertices->push_back(osg::Vec3(_x + _size, 0., _z));
  _vertices->push_back(osg::Vec3(_x + _size, 0., _z + _size));

  setVertexArray(_vertices);
  addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,
    0, _vertices->size()));

  //normals
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

void Tile::setTexture(std::string texPath)
{
  //putting texture on tile
  osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array;
  texCoords->push_back(osg::Vec2(0.0f, 0.0f));
  texCoords->push_back(osg::Vec2(0.0f, 1.0f));
  texCoords->push_back(osg::Vec2(1.0f, 0.0f));
  texCoords->push_back(osg::Vec2(1.0f, 1.0f));
  setTexCoordArray(0, texCoords);

  osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;

  osg::ref_ptr<osg::Image> image;

  //image->s();   //_s,_t атрибуты размера изображения
  image = osgDB::readImageFile(texPath);
  /*
  if (!image)
  {
    
  }
  */

  texture->setImage(image);

  osg::ref_ptr<osg::StateSet> stateTile = new osg::StateSet;
  stateTile->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
  setStateSet(stateTile);
}

void Tile::setEmptyTexture(EmptyTile empty)
{
  //put texture on tile
  osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array;
  texCoords->push_back(osg::Vec2(0.0f, 0.0f));
  texCoords->push_back(osg::Vec2(0.0f, 1.0f));
  texCoords->push_back(osg::Vec2(1.0f, 0.0f));
  texCoords->push_back(osg::Vec2(1.0f, 1.0f));
  setTexCoordArray(0, texCoords);

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

  /*
  if (!image)
  {

  }
  */

  texture->setImage(image);

  osg::ref_ptr<osg::StateSet> stateTile = new osg::StateSet;
  stateTile->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
  stateTile->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
  stateTile->setMode(GL_BLEND, osg::StateAttribute::ON);
  setStateSet(stateTile);
}

QString Tile::GetType_str()
{
  return QString::fromStdString(_typeName);
}