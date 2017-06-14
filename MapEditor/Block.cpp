#include "Block.h"


Block::Block()
{
}

//принимает координаты, тип блока
//Block::Block(int x, int z, TexType type, FillType fillType) :
Block::Block(int x, int z, std::string typeName, std::string texPath, FillType fillType) :
_x(x), _z(z),
_typeName(typeName),
_texPath(texPath),
_fType(fillType)
{
  int tileSize = Tile::Size();

  //createFromTiles(type, fillType);
  createFromTiles(_typeName, _texPath, _fType);

  if (_leftBottom != nullptr) addChild(_leftBottom);
  if (_leftTop != nullptr) addChild(_leftTop);
  if (_rightTop != nullptr) addChild(_rightTop);
  if (_rightBottom != nullptr) addChild(_rightBottom);
}

Block::~Block()
{
}

void Block::createFromTiles(std::string typeName, std::string texPath, FillType fillType)
{
  int tileSize = Tile::Size();

  //_type = texType;
  //_texPath = texPath;
  //_fType = fillType;

  //if (texType == TexType::EMPTY)
  if (typeName == "EMPTY")
  {
    _leftBottom = new Tile(_x, _z, typeName, EmptyTile::LEFT_BOTTOM);
    _leftTop = new Tile(_x, _z + tileSize, typeName, EmptyTile::LEFT_TOP);
    _rightTop = new Tile(_x + tileSize, _z + tileSize,
      typeName, EmptyTile::RIGHT_TOP);
    _rightBottom = new Tile(_x + tileSize, _z, typeName, EmptyTile::RIGHT_BOTTOM);
  }
  else
  {
    switch (fillType)
    {
    case FillType::FULL:
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, typeName, texPath);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
      break;
    case FillType::BOTTOM:
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, "EMPTY", EmptyTile::LEFT_TOP);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, 
      "EMPTY", EmptyTile::RIGHT_TOP);

      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
      break;
    case FillType::LEFT:
      _leftBottom = new Tile(_x, _z, typeName, texPath);
      _leftTop = new Tile(_x, _z + tileSize, typeName, texPath);
      _rightTop = new Tile(_x + tileSize, _z + tileSize,
        "EMPTY", EmptyTile::RIGHT_TOP);
      _rightBottom = new Tile(_x + tileSize, _z, 
        "EMPTY", EmptyTile::RIGHT_BOTTOM);
      break;
    case FillType::RIGHT:
      _leftBottom = new Tile(_x, _z, "EMPTY", EmptyTile::LEFT_BOTTOM);
      _leftTop = new Tile(_x, _z + tileSize, "EMPTY", EmptyTile::LEFT_TOP);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, _z, typeName, texPath);
      break;
    case FillType::TOP:
      _leftBottom = new Tile(_x, _z, "EMPTY", EmptyTile::LEFT_BOTTOM);
      _leftTop = new Tile(_x, _z + tileSize, typeName, texPath);
      _rightTop = new Tile(_x + tileSize, _z + tileSize, typeName, texPath);
      _rightBottom = new Tile(_x + tileSize, _z, 
        "EMPTY", EmptyTile::RIGHT_BOTTOM);
      break;
    }
  }
}

void Block::SetType(std::string typeName, std::string texPath, FillType fillType)
{
  if ((_typeName != typeName) || (_fType != fillType))	//если блок точно такой же, ничего не меняется
  {													//иначе происходит замена
    osg::ref_ptr<Tile> oldLB = _leftBottom;
    osg::ref_ptr<Tile> oldLT = _leftTop;
    osg::ref_ptr<Tile> oldRT = _rightTop;
    osg::ref_ptr<Tile> oldRB = _rightBottom;

    //замена блока
    _typeName = typeName;
    _texPath = texPath;
    _fType = fillType;

    createFromTiles(typeName, texPath, fillType);

    replaceChild(oldLB, _leftBottom);
    replaceChild(oldLT, _leftTop);
    replaceChild(oldRT, _rightTop);
    replaceChild(oldRB, _rightBottom);
  }
}

std::pair<QString, QString> Block::GetType_str()
{
  QString texType;
  QString fillType;
  
  //проверка на empty?
  /*
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
    return std::make_pair("EMPTY", "EMPTY");
  case TexType::WATER:
    texType = "WATER";
    break;
  case TexType::ICE:
    texType = "ICE";
    break;
  }
  */

  switch (_fType)
  {
  case FillType::BOTTOM:
    fillType = "BOTTOM";
    break;
  case FillType::FULL:
    fillType = "FULL";
    break;
  case FillType::LEFT:
    fillType = "LEFT";
    break;
  case FillType::RIGHT:
    fillType = "RIGHT";
    break;
  case FillType::TOP:
    fillType = "TOP";
    break;
  }

  return std::make_pair(texType, fillType);
}
